package main

import (
	"bytes"
	"encoding/json"
	"net/http/httptest"
	"os"
	"path/filepath"
	"testing"
	"time"
)

// TestDiskLEDMapping 验证健康映射、设备改名、离线和无 SMART 时关闭。
func TestDiskLEDMapping(t *testing.T) {
	cfg := defaultLEDConfig()
	cfg.Bindings[0] = LEDBinding{Path: "/dev/sdb", UUID: "wwn-A", UseUUID: true, States: [3]uint8{2, 3, 1}}
	for status, want := range []uint8{2, 3, 1} {
		disks := []Disk{{Path: "/dev/sdz", UUID: "wwn-A", Status: uint8(status), SMARTAvailable: true}}
		if got := diskLEDStates(cfg, disks); got != [4]uint8{want, 0, 0, 0} {
			t.Fatalf("status %d: %v", status, got)
		}
	}
	for _, disks := range [][]Disk{nil, {{Path: "/dev/sdb", UUID: "wwn-B", SMARTAvailable: true}}, {{Path: "/dev/sdz", UUID: "wwn-A"}}} {
		if got := diskLEDStates(cfg, disks); got != [4]uint8{} {
			t.Fatalf("expected off: %v", got)
		}
	}
	cfg.Bindings[0].UseUUID = false
	if got := diskLEDStates(cfg, []Disk{{Path: "/dev/sdb", SMARTAvailable: true, Status: 1}}); got[0] != 3 {
		t.Fatal(got)
	}
}

// TestLEDValidation 验证重复硬盘、通道颜色和状态组合的约束。
func TestLEDValidation(t *testing.T) {
	base := defaultLEDConfig()
	base.Bindings[0] = LEDBinding{Path: "/dev/sdb", UUID: "wwn-A", UseUUID: true, States: [3]uint8{2, 3, 1}}
	if err := validateLEDConfig(base); err != nil {
		t.Fatal(err)
	}
	for _, change := range []func(*LEDConfig){
		func(c *LEDConfig) { c.Bindings[1] = c.Bindings[0] },
		func(c *LEDConfig) { c.Bindings[1] = c.Bindings[0]; c.Bindings[1].Path = "/dev/sdz" },
		func(c *LEDConfig) { c.Bindings[0].States = [3]uint8{1, 1, 2} },
		func(c *LEDConfig) { c.Bindings[0].UUID = "" },
		func(c *LEDConfig) { c.Colors[0].Color1 = c.Colors[0].Color0 },
	} {
		cfg := base
		change(&cfg)
		if validateLEDConfig(cfg) == nil {
			t.Fatalf("accepted invalid %+v", cfg)
		}
	}
}

// TestLEDTestTimeout 验证测试覆盖、超时恢复、断连拒绝和陈旧采集熄灯。
func TestLEDTestTimeout(t *testing.T) {
	cfg := defaultLEDConfig()
	cfg.Bindings[0] = LEDBinding{Path: "/dev/sdb", States: [3]uint8{2, 3, 1}}
	now := time.Now()
	snapshot := Snapshot{UpdatedAt: now, Disks: []Disk{{Path: "/dev/sdb", SMARTAvailable: true}}}
	s := &Service{}
	if s.TestLED(0, 1, now) == nil {
		t.Fatal("accepted disconnected test")
	}
	s.status.Connected = true
	if err := s.TestLED(0, 1, now); err != nil {
		t.Fatal(err)
	}
	if got := s.responseLEDState(cfg, snapshot, now); got != 1 {
		t.Fatal(got)
	}
	if got := s.responseLEDState(cfg, snapshot, now.Add(6*time.Second)); got != 2 {
		t.Fatal(got)
	}
	if got := s.responseLEDState(cfg, snapshot, now.Add(time.Minute)); got != 0 {
		t.Fatal(got)
	}
	if err := s.TestLED(3, 2, now); err != nil {
		t.Fatal(err)
	}
	if got := s.responseLEDState(cfg, snapshot, now); got != 130 {
		t.Fatal(got)
	}
	if err := s.TestLED(0, 0, now); err != nil {
		t.Fatal(err)
	}
	if got := s.responseLEDState(cfg, snapshot, now); got != 2 {
		t.Fatal(got)
	}
}

// TestLEDConfigAPI 验证独立保存、颜色跟随、持久化及重复实际硬盘拒绝。
func TestLEDConfigAPI(t *testing.T) {
	store, err := Load(filepath.Join(t.TempDir(), "config.json"))
	if err != nil {
		t.Fatal(err)
	}
	cfg := store.Get()
	cfg.WebPort = 9090
	if err = store.Save(cfg); err != nil {
		t.Fatal(err)
	}
	server := &Server{config: store, collector: &Collector{snapshot: Snapshot{Disks: []Disk{{Path: "/dev/sdb", UUID: "wwn-A"}}}}}
	led := defaultLEDConfig()
	led.Colors[0] = LEDColors{"green", "orange"}
	body, _ := json.Marshal(led)
	w := httptest.NewRecorder()
	server.putLEDConfig(w, httptest.NewRequest("PUT", "/api/v1/led", bytes.NewReader(body)))
	if w.Code != 200 {
		t.Fatal(w.Code, w.Body.String())
	}
	saved, err := Load(store.path)
	if err != nil {
		t.Fatal(err)
	}
	if saved.Get().WebPort != 9090 || saved.Get().LED.Colors[3] != led.Colors[0] {
		t.Fatal("save lost settings")
	}
	led.Bindings[0] = LEDBinding{Path: "/dev/sdz", UUID: "wwn-A", UseUUID: true, States: [3]uint8{2, 3, 1}}
	led.Bindings[1] = LEDBinding{Path: "/dev/sdb", States: [3]uint8{2, 3, 1}}
	body, _ = json.Marshal(led)
	w = httptest.NewRecorder()
	server.putLEDConfig(w, httptest.NewRequest("PUT", "/api/v1/led", bytes.NewReader(body)))
	if w.Code != 409 {
		t.Fatal(w.Code, w.Body.String())
	}
}

// TestStableDiskIDs 验证整盘稳定标识优先级及设备号变化，不读取真实硬盘。
func TestStableDiskIDs(t *testing.T) {
	root, err := filepath.EvalSymlinks(t.TempDir())
	if err != nil {
		t.Fatal(err)
	}
	device := filepath.Join(root, "sdb")
	ids := filepath.Join(root, "by-id")
	if err := os.Mkdir(ids, 0755); err != nil {
		t.Fatal(err)
	}
	if err := os.WriteFile(device, nil, 0600); err != nil {
		t.Fatal(err)
	}
	for _, name := range []string{"ata-SERIAL", "wwn-ABC", "wwn-ABC-part1"} {
		if err := os.Symlink(device, filepath.Join(ids, name)); err != nil {
			t.Fatal(err)
		}
	}
	if got := diskStableIDs(ids)[device]; got != "wwn-ABC" {
		t.Fatal(got)
	}
	renamed := filepath.Join(root, "sdz")
	if err := os.Rename(device, renamed); err != nil {
		t.Fatal(err)
	}
	if err := os.Remove(filepath.Join(ids, "wwn-ABC")); err != nil {
		t.Fatal(err)
	}
	if err := os.Symlink(renamed, filepath.Join(ids, "wwn-ABC")); err != nil {
		t.Fatal(err)
	}
	if got := diskStableIDs(ids)[renamed]; got != "wwn-ABC" {
		t.Fatal(got)
	}
}
