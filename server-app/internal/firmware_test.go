package main

import (
	"bytes"
	"context"
	"crypto/sha256"
	"encoding/binary"
	"encoding/json"
	"errors"
	"fmt"
	"io"
	"log/slog"
	"mime/multipart"
	"net/http"
	"net/http/httptest"
	"os"
	"strings"
	"sync"
	"testing"
	"time"
)

// testFirmware 返回仅供离线测试的合法向量和占位数据。
func testFirmware() []byte {
	image := make([]byte, 32)
	binary.LittleEndian.PutUint32(image, 0x20018000)
	binary.LittleEndian.PutUint32(image[4:], firmwareBase+9)
	return image
}

// TestFirmwareValidation 覆盖容量、栈对齐、Thumb 位及写入地址限制。
func TestFirmwareValidation(t *testing.T) {
	for _, tc := range []struct {
		name    string
		image   []byte
		invalid bool
	}{
		{"valid", testFirmware(), false}, {"short", make([]byte, 7), true}, {"oversize", make([]byte, firmwareMaxSize+1), true},
	} {
		if err := validateFirmware(tc.image); (err != nil) != tc.invalid {
			t.Errorf("%s: %v", tc.name, err)
		}
	}
	for _, vectors := range [][2]uint32{{0x20000000, firmwareBase + 9}, {0x20018008, firmwareBase + 9}, {0x20017fff, firmwareBase + 9}, {0x20018000, firmwareBase + 8}, {0x20018000, 0x08000009}, {0x20018000, firmwareBase + 33}} {
		image := testFirmware()
		binary.LittleEndian.PutUint32(image, vectors[0])
		binary.LittleEndian.PutUint32(image[4:], vectors[1])
		if validateFirmware(image) == nil {
			t.Fatalf("accepted invalid vectors %x", vectors)
		}
	}
}

// TestFirmwarePackage 与现有 Python DFU 工具生成的完整文件摘要交叉验证。
func TestFirmwarePackage(t *testing.T) {
	got := fmt.Sprintf("%x", sha256.Sum256(firmwarePackage(testFirmware())))
	if got != "085f7a2cf625aa0d2584078d15bd726e0c11315f963d967528e45ffd36ba36fc" {
		t.Fatal(got)
	}
}

// TestBootloaderCommand 验证只有无附加数据的设置命令能够进入升级模式。
func TestBootloaderCommand(t *testing.T) {
	frame, err := EncodeResponse(42, Response{Type: ResponseSetting, Setting: SettingBootloader})
	if err != nil {
		t.Fatal(err)
	}
	if frame[0] != 1 || binary.LittleEndian.Uint32(frame[3:]) != 42 || binary.LittleEndian.Uint16(frame[7:]) != ResponsePrefix || frame[10] != 1 || frame[12] != 1 || CRC8(frame[10:10+ResponsePrefix]) != frame[9] {
		t.Fatalf("invalid frame %x", frame[:10+ResponsePrefix])
	}
	if _, err := EncodeResponse(42, Response{Type: ResponseSetting, Setting: SettingBootloader, SettingData: []byte{1}}); err == nil {
		t.Fatal("accepted extra data")
	}
}

// TestSelectDFUTarget 拒绝多设备歧义、重复序列号和其他面板。
func TestSelectDFUTarget(t *testing.T) {
	for _, tc := range []struct {
		devices     []string
		wanted      string
		found, fail bool
	}{
		{[]string{"A"}, "", true, false}, {[]string{"A", "B"}, "", false, true},
		{[]string{"B"}, "A", false, false}, {[]string{"A", "A"}, "A", false, true},
		{nil, "A", false, false}, {[]string{"A", "B"}, "A", true, false},
	} {
		_, found, err := selectDFUTarget(tc.devices, tc.wanted)
		if found != tc.found || (err != nil) != tc.fail {
			t.Fatalf("%+v: %v %v", tc, found, err)
		}
	}
}

type fakeFirmwarePanel struct {
	mu        sync.Mutex
	connected bool
	suspended bool
	resumed   bool
	boot      bool
	seen      time.Time
}

// Status 返回模拟面板的线程安全状态。
func (p *fakeFirmwarePanel) Status() Status {
	p.mu.Lock()
	defer p.mu.Unlock()
	return Status{Connected: p.connected, Serial: "A", LastSeen: p.seen}
}

// configuredSerial 为测试固定选择目标面板。
func (p *fakeFirmwarePanel) configuredSerial() string { return "A" }

// suspendFirmware 模拟 APP 到 DFU 的转换。
func (p *fakeFirmwarePanel) suspendFirmware(_ context.Context, boot bool, _ string) error {
	p.mu.Lock()
	defer p.mu.Unlock()
	p.suspended = true
	p.connected = false
	p.boot = boot
	return nil
}

// resumeFirmware 模拟有效 HID 通信恢复。
func (p *fakeFirmwarePanel) resumeFirmware() {
	p.mu.Lock()
	defer p.mu.Unlock()
	p.resumed = true
	p.connected = true
	p.seen = time.Now()
}

// TestFirmwareWorkflow 验证两步下载、设备选择、文件清理、失败恢复与并发拒绝。
func TestFirmwareWorkflow(t *testing.T) {
	for _, fail := range []bool{false, true} {
		p := &fakeFirmwarePanel{connected: true}
		u := NewFirmwareUpdater(p)
		u.lookup = func(string) (string, error) { return "fake-dfu-util", nil }
		started := make(chan struct{})
		release := make(chan struct{})
		downloads := 0
		var packagePath string
		u.run = func(_ context.Context, _ string, args []string, out io.Writer) error {
			joined := strings.Join(args, " ")
			if strings.Contains(joined, "-l") {
				p.mu.Lock()
				dfu := p.suspended
				p.mu.Unlock()
				if dfu {
					fmt.Fprintln(out, `Found DFU: [3939:3927] devnum=1, cfg=1, intf=0, path="1-1", alt=0, name="Flash", serial="A"`)
				}
				return nil
			}
			downloads++
			if strings.Contains(joined, "-S ,A") == false || strings.Contains(joined, "-d ,3939:3927") == false {
				return errors.New("wrong device")
			}
			if downloads == 1 {
				packagePath = args[len(args)-1]
				data, err := os.ReadFile(packagePath)
				if err != nil {
					return err
				}
				if bytes.Equal(data, firmwarePackage(testFirmware())) == false {
					return errors.New("bad package")
				}
				close(started)
				<-release
				if fail {
					return errors.New("simulated disconnect")
				}
				fmt.Fprint(out, "Erase [====] 100%\rDownload [====] 100%\r")
			} else {
				if strings.Contains(joined, "0x08008000:leave:force") == false {
					return errors.New("missing manifest")
				}
				data, err := os.ReadFile(args[len(args)-1])
				if err != nil {
					return err
				}
				if len(data) != 0 {
					return errors.New("manifest must be empty")
				}
			}
			return nil
		}
		if err := u.Start("test.bin", testFirmware()); err != nil {
			t.Fatal(err)
		}
		select {
		case <-started:
		case <-time.After(time.Second):
			t.Fatal("download did not start")
		}
		if err := u.Start("test.bin", testFirmware()); errors.Is(err, errFirmwareBusy) == false {
			t.Fatal("concurrent upgrade accepted")
		}
		close(release)
		u.wg.Wait()
		result := u.Status()
		u.Close()
		expected := "complete"
		if fail {
			expected = "failed"
		}
		if result.Stage != expected || result.Busy {
			t.Fatalf("%+v", result)
		}
		if p.resumed == false || p.boot == false {
			t.Fatal("HID lifecycle not handled")
		}
		if fail && downloads != 1 {
			t.Fatal("manifest ran after download failure")
		}
		if _, err := os.Stat(packagePath); os.IsNotExist(err) == false {
			t.Fatal("temporary firmware not removed")
		}
	}
}

// TestFirmwareProgress 验证拆分的进度输出及日志上限。
func TestFirmwareProgress(t *testing.T) {
	u := NewFirmwareUpdater(nil)
	defer u.Close()
	w := &firmwareOutput{updater: u, progress: true}
	w.Write([]byte("Erase [====] 4"))
	w.Write([]byte("2%\r"))
	if u.state.Stage != "erasing" || u.state.Progress != 42 {
		t.Fatal(u.state)
	}
	w.Write([]byte(strings.Repeat("x", 20000)))
	if len(u.state.Log) > 8192 {
		t.Fatal("unbounded log")
	}
}

// TestFirmwareOutputCarriageReturn 保留进度行的最新内容，不将终端刷新写成多行日志。
func TestFirmwareOutputCarriageReturn(t *testing.T) {
	u := NewFirmwareUpdater(nil)
	defer u.Close()
	w := &firmwareOutput{updater: u}
	_, _ = w.Write([]byte("Erase [ ] 0%\rErase [=] 4%\rErase [==] 8%\r"))
	if strings.Contains(u.state.Log, "0%") || strings.Contains(u.state.Log, "4%") || strings.Contains(u.state.Log, "8%") == false {
		t.Fatal(u.state.Log)
	}
	_, _ = w.Write([]byte("Erase done.\nDownload [ ] 0%\rDownload [=] 5%\r"))
	if strings.Contains(u.state.Log, "Erase done.") == false || strings.Contains(u.state.Log, "Download [=] 5%") == false || strings.Contains(u.state.Log, "Download [ ] 0%") {
		t.Fatal(u.state.Log)
	}
}

// TestFirmwareUploadAPI 验证反代路由、缺依赖、非法文件及跨站请求不会启动升级。
func TestFirmwareUploadAPI(t *testing.T) {
	cfg := Default()
	cfg.BasePath = "/panel"
	server := NewServer(&Store{cfg: cfg}, nil, nil, nil, BuildInfo{}, t.TempDir(), slog.New(slog.NewTextHandler(io.Discard, nil)))
	defer server.firmware.Close()
	server.firmware.lookup = func(string) (string, error) { return "", errors.New("not installed") }
	for _, tc := range []struct {
		name   string
		image  []byte
		origin string
		code   int
	}{
		{"valid.bin", testFirmware(), "", 503}, {"bad.bin", []byte("bad"), "", 400}, {"bad.txt", testFirmware(), "", 400}, {"valid.bin", testFirmware(), "https://evil.example", 403},
	} {
		var body bytes.Buffer
		form := multipart.NewWriter(&body)
		part, _ := form.CreateFormFile("file", tc.name)
		part.Write(tc.image)
		form.Close()
		request := httptest.NewRequest("POST", "http://localhost/panel/api/v1/firmware", &body)
		request.Header.Set("Content-Type", form.FormDataContentType())
		request.Header.Set("Origin", tc.origin)
		result := httptest.NewRecorder()
		server.Handler().ServeHTTP(result, request)
		if result.Code != tc.code {
			t.Fatalf("%s: %d %s", tc.name, result.Code, result.Body.String())
		}
	}
	result := httptest.NewRecorder()
	server.Handler().ServeHTTP(result, httptest.NewRequest("GET", "/panel/api/v1/firmware", nil))
	var state FirmwareStatus
	if result.Code != http.StatusOK || json.Unmarshal(result.Body.Bytes(), &state) != nil || state.Available {
		t.Fatal(result.Body.String())
	}
}

// TestFirmwareReconnect 不接受其他设备、旧回复或未连接状态。
func TestFirmwareReconnect(t *testing.T) {
	now := time.Now()
	for _, tc := range []struct {
		connected bool
		seen      time.Time
		serial    string
		fail      bool
	}{
		{true, now.Add(time.Second), "A", false},
		{true, now.Add(-time.Second), "A", true},
		{true, now.Add(time.Second), "B", true},
		{false, now.Add(time.Second), "A", true},
	} {
		panel := &fakeFirmwarePanel{connected: tc.connected, seen: tc.seen}
		ctx, cancel := context.WithTimeout(context.Background(), time.Millisecond)
		err := waitForFirmwareHID(ctx, panel, tc.serial, now)
		cancel()
		if (err != nil) != tc.fail {
			t.Fatalf("%+v: %v", tc, err)
		}
	}
}
