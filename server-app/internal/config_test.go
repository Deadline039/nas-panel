package main

import (
	"encoding/json"
	"path/filepath"
	"strings"
	"testing"
)

// TestWebPortRoundTrip 验证统一端口持久化后用于生成面板二维码。
func TestWebPortRoundTrip(t *testing.T) {
	path := filepath.Join(t.TempDir(), "config.json")
	store, err := Load(path)
	if err != nil {
		t.Fatal(err)
	}
	cfg := store.Get()
	if cfg.WebPort != 8080 {
		t.Fatalf("default web port: %d", cfg.WebPort)
	}
	cfg.WebPort = 9090
	if err := store.Save(cfg); err != nil {
		t.Fatal(err)
	}
	reloaded, err := Load(path)
	if err != nil {
		t.Fatal(err)
	}
	cfg = reloaded.Get()
	links := aboutLinks(Snapshot{Networks: []Network{
		{Name: "eth0", Status: 2, IPAddress: "192.168.1.10"},
	}}, cfg)
	if cfg.WebPort != 9090 || len(links) != 1 || links[0].URL != "http://192.168.1.10:9090" {
		t.Fatalf("port %d, links %+v", cfg.WebPort, links)
	}
	data, err := json.Marshal(cfg)
	if err != nil {
		t.Fatal(err)
	}
	if strings.Contains(string(data), `"webPort":9090`) == false ||
		strings.Contains(string(data), `"listen"`) || strings.Contains(string(data), `"publicPort"`) {
		t.Fatalf("unexpected config fields: %s", data)
	}
}

// TestWebPortValidation 验证零值、越界值、小数和字符串端口不会被接受。
func TestWebPortValidation(t *testing.T) {
	for _, value := range []string{"0", "-1", "65536", "8080.5", `"8080"`} {
		cfg := Default()
		err := json.Unmarshal([]byte(`{"webPort":`+value+`}`), &cfg)
		if err == nil {
			err = Validate(cfg)
		}
		if err == nil {
			t.Fatalf("accepted invalid port %s", value)
		}
	}
	for _, port := range []uint16{1, 8080, 65535} {
		cfg := Default()
		cfg.WebPort = port
		if err := Validate(cfg); err != nil {
			t.Fatalf("rejected port %d: %v", port, err)
		}
	}
}
