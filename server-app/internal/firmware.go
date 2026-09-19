package main

import (
	"context"
	"errors"
	"fmt"
	"io"
	"os"
	"os/exec"
	"path/filepath"
	"regexp"
	"strconv"
	"strings"
	"sync"
	"time"
)

type firmwarePanel interface {
	Status() Status
	configuredSerial() string
	suspendFirmware(context.Context, bool, string) error
	resumeFirmware()
}

// FirmwareStatus 保存升级状态，刷新网页后仍可继续观察同一次任务。
type FirmwareStatus struct {
	Available bool   `json:"available"`
	Busy      bool   `json:"busy"`
	Stage     string `json:"stage"`
	Progress  int    `json:"progress"`
	Filename  string `json:"filename,omitempty"`
	Serial    string `json:"serial,omitempty"`
	Error     string `json:"error,omitempty"`
	Log       string `json:"log,omitempty"`
}

// FirmwareUpdater 串行运行 DFU 任务，不依赖上传请求的生命周期。
type FirmwareUpdater struct {
	mu     sync.Mutex
	state  FirmwareStatus
	panel  firmwarePanel
	ctx    context.Context
	cancel context.CancelFunc
	wg     sync.WaitGroup
	lookup func(string) (string, error)
	run    func(context.Context, string, []string, io.Writer) error
}

// NewFirmwareUpdater 创建独立于 HTTP 请求的升级管理器。
func NewFirmwareUpdater(panel firmwarePanel) *FirmwareUpdater {
	ctx, cancel := context.WithCancel(context.Background())
	return &FirmwareUpdater{panel: panel, ctx: ctx, cancel: cancel, lookup: exec.LookPath, run: runDFUCommand, state: FirmwareStatus{Stage: "idle"}}
}

// Close 取消并等待升级任务，避免服务退出后子进程继续写入。
func (u *FirmwareUpdater) Close() {
	u.mu.Lock()
	u.cancel()
	u.mu.Unlock()
	u.wg.Wait()
}

// Status 返回状态副本和服务器上的 DFU 工具可用性。
func (u *FirmwareUpdater) Status() FirmwareStatus {
	u.mu.Lock()
	result := u.state
	u.mu.Unlock()
	_, err := u.lookup("dfu-util")
	result.Available = err == nil
	return result
}

var errFirmwareBusy = errors.New("a firmware update is already running")
var errDFUMissing = errors.New("install dfu-util on the server and add it to PATH")

// Start 先验证文件与依赖，再启动唯一的后台升级任务。
func (u *FirmwareUpdater) Start(filename string, image []byte) error {
	if strings.EqualFold(filepath.Ext(filename), ".bin") == false {
		return errors.New("select an APP .bin file")
	}
	if err := validateFirmware(image); err != nil {
		return err
	}
	executable, err := u.lookup("dfu-util")
	if err != nil {
		return errDFUMissing
	}
	u.mu.Lock()
	defer u.mu.Unlock()
	if u.ctx.Err() != nil {
		return errors.New("server is shutting down")
	}
	if u.state.Busy {
		return errFirmwareBusy
	}
	u.state = FirmwareStatus{Busy: true, Available: true, Stage: "preparing", Filename: filepath.Base(filename)}
	image = append([]byte(nil), image...)
	u.wg.Add(1)
	go func() {
		defer u.wg.Done()
		ctx, cancel := context.WithTimeout(u.ctx, 5*time.Minute)
		defer cancel()
		err := u.update(ctx, executable, image)
		u.mu.Lock()
		defer u.mu.Unlock()
		u.state.Busy = false
		if err != nil {
			u.state.Stage = "failed"
			u.state.Error = err.Error()
			return
		}
		u.state.Stage = "complete"
		u.state.Progress = 100
	}()
	return nil
}

// stage 切换阶段并重置当前阶段进度。
func (u *FirmwareUpdater) stage(stage string) {
	u.mu.Lock()
	u.state.Stage = stage
	u.state.Progress = 0
	u.mu.Unlock()
}

// update 执行下载及 manifest；同一设备恢复有效 HID 交换后才报告成功。
func (u *FirmwareUpdater) update(ctx context.Context, executable string, image []byte) error {
	directory, err := os.MkdirTemp("", "nas-panel-dfu-")
	if err != nil {
		return err
	}
	defer os.RemoveAll(directory)
	packagePath := filepath.Join(directory, "image.dfu")
	manifestPath := filepath.Join(directory, "manifest.bin")
	if err := os.WriteFile(packagePath, firmwarePackage(image), 0o600); err != nil {
		return err
	}
	if err := os.WriteFile(manifestPath, nil, 0o600); err != nil {
		return err
	}

	status := u.panel.Status()
	serial := u.panel.configuredSerial()
	if status.Connected {
		serial = status.Serial
	}
	devices, err := u.devices(ctx, executable)
	if err != nil {
		return err
	}
	serial, inDFU, err := selectDFUTarget(devices, serial)
	if err != nil {
		return err
	}
	if inDFU == false && status.Connected == false {
		return errors.New("panel not connected; enter bootloader mode and retry")
	}
	if serial == "" || strings.ContainsAny(serial, ",\r\n") {
		return errors.New("cannot identify the panel serial number")
	}
	u.mu.Lock()
	u.state.Serial = serial
	u.mu.Unlock()
	u.stage("entering")
	defer u.panel.resumeFirmware()
	pauseCtx, pauseCancel := context.WithTimeout(ctx, 12*time.Second)
	err = u.panel.suspendFirmware(pauseCtx, inDFU == false, serial)
	pauseCancel()
	if err != nil {
		return err
	}
	u.stage("waiting_dfu")
	discoveryCtx, discoveryCancel := context.WithTimeout(ctx, 20*time.Second)
	defer discoveryCancel()
	for {
		devices, err = u.devices(discoveryCtx, executable)
		if err != nil {
			return err
		}
		_, found, selectErr := selectDFUTarget(devices, serial)
		if selectErr != nil {
			return selectErr
		}
		if found {
			break
		}
		if wait(discoveryCtx, 500*time.Millisecond) == false {
			return errors.New("DFU device did not appear; older APP firmware may require manual bootloader entry")
		}
	}
	args := []string{"-d", ",3939:3927", "-a", "0", "-S", "," + serial}
	u.stage("programming")
	output := &firmwareOutput{updater: u, progress: true}
	if err := u.run(ctx, executable, append(append([]string{}, args...), "-D", packagePath), output); err != nil {
		return fmt.Errorf("DFU download failed: %w", err)
	}
	u.stage("verifying")
	output.progress = false
	reconnectAfter := time.Now()
	err = u.run(ctx, executable, append(append([]string{}, args...), "-s", "0x08008000:leave:force", "-D", manifestPath), output)
	var exitError *exec.ExitError
	if err != nil && (errors.As(err, &exitError) == false || exitError.ExitCode() != 74) {
		return fmt.Errorf("DFU verification failed: %w", err)
	}
	u.stage("reconnecting")
	u.panel.resumeFirmware()
	reconnectCtx, reconnectCancel := context.WithTimeout(ctx, 30*time.Second)
	defer reconnectCancel()
	return waitForFirmwareHID(reconnectCtx, u.panel, serial, reconnectAfter)
}

// waitForFirmwareHID 要求目标面板产生新的有效 HID 回复，不能将旧连接状态当作升级成功。
func waitForFirmwareHID(ctx context.Context, panel firmwarePanel, serial string, after time.Time) error {
	for ctx.Err() == nil {
		status := panel.Status()
		if status.Connected && status.Serial == serial && status.LastSeen.After(after) {
			return nil
		}
		if wait(ctx, 250*time.Millisecond) == false {
			break
		}
	}
	return errors.New("no valid HID response after DFU; firmware verification or restart may have failed")
}

var dfuSerialPattern = regexp.MustCompile(`serial="([^"]*)"`)

// devices 只列出本项目的 DFU target，不选择其他厂商或运行模式设备。
func (u *FirmwareUpdater) devices(ctx context.Context, executable string) ([]string, error) {
	ctx, cancel := context.WithTimeout(ctx, 4*time.Second)
	defer cancel()
	output := &limitedOutput{}
	if err := u.run(ctx, executable, []string{"-d", ",3939:3927", "-a", "0", "-l"}, output); err != nil {
		return nil, fmt.Errorf("list DFU devices: %w; %s", err, output.text)
	}
	var serials []string
	for _, line := range strings.Split(output.text, "\n") {
		if strings.Contains(line, "Found DFU: [3939:3927]") == false || strings.Contains(line, "alt=0,") == false {
			continue
		}
		match := dfuSerialPattern.FindStringSubmatch(line)
		if match == nil || match[1] == "" {
			return nil, errors.New("DFU device has no readable serial; check USB permissions")
		}
		serials = append(serials, match[1])
	}
	return serials, nil
}

// selectDFUTarget 严格按序列号选设备；恢复模式未指定设备时只接受唯一设备。
func selectDFUTarget(devices []string, wanted string) (string, bool, error) {
	if wanted == "" {
		if len(devices) != 1 {
			return "", false, errors.New("connect one panel or configure panelSerial before upgrading")
		}
		return devices[0], true, nil
	}
	matches := 0
	for _, serial := range devices {
		if serial == wanted {
			matches++
		}
	}
	if matches > 1 {
		return wanted, false, errors.New("multiple DFU devices share the selected serial")
	}
	return wanted, matches == 1, nil
}

// runDFUCommand 不经 shell 执行固定参数，并在取消或超时时结束子进程。
func runDFUCommand(ctx context.Context, executable string, args []string, output io.Writer) error {
	command := exec.CommandContext(ctx, executable, args...)
	command.Stdout = output
	command.Stderr = output
	command.WaitDelay = 2 * time.Second
	return command.Run()
}

type limitedOutput struct{ text string }

// Write 只保留末尾日志，避免子进程输出无限占用内存。
func (w *limitedOutput) Write(data []byte) (int, error) {
	w.text += string(data)
	if len(w.text) > 8192 {
		w.text = w.text[len(w.text)-8192:]
	}
	return len(data), nil
}

type firmwareOutput struct {
	updater  *FirmwareUpdater
	progress bool
	pending  string
}

var dfuProgressPattern = regexp.MustCompile(`(Erase|Download)\s*\[[^\]]*\]\s*([0-9]+)%`)

// Write 收集日志并解析 dfu-util 的擦除或下载百分比，兼容分块输出及回车刷新。
func (w *firmwareOutput) Write(data []byte) (int, error) {
	u := w.updater
	u.mu.Lock()
	defer u.mu.Unlock()
	u.state.Log += string(data)
	if len(u.state.Log) > 8192 {
		u.state.Log = u.state.Log[len(u.state.Log)-8192:]
	}
	if w.progress {
		w.pending += string(data)
		matches := dfuProgressPattern.FindAllStringSubmatch(w.pending, -1)
		if len(matches) > 0 {
			match := matches[len(matches)-1]
			u.state.Stage = "programming"
			if match[1] == "Erase" {
				u.state.Stage = "erasing"
			}
			value, _ := strconv.Atoi(match[2])
			u.state.Progress = min(value, 100)
		}
		if len(w.pending) > 1024 {
			w.pending = w.pending[len(w.pending)-1024:]
		}
	}
	return len(data), nil
}
