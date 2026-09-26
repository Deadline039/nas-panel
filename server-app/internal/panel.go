package main

import (
	"context"
	"errors"
	"fmt"
	"log/slog"
	"strings"
	"sync"
	"time"

	"github.com/sstallion/go-hid"
)

const (
	vendorID  = 0x3939
	productID = 0x0831
)

// Status describes the current panel connection and latest exchange.
type Status struct {
	Connected       bool      `json:"connected"`
	Serial          string    `json:"serial"`
	Product         string    `json:"product"`
	LastSeen        time.Time `json:"lastSeen,omitempty"`
	LastError       string    `json:"lastError,omitempty"`
	Responses       uint64    `json:"responses"`
	LatestReport    *Request  `json:"latestReport,omitempty"`
	FanCurvePending bool      `json:"fanCurvePending"`
}

// Service reconnects to the panel and answers every valid request.
type Service struct {
	mu               sync.RWMutex
	status           Status
	config           *Store
	collector        *Collector
	energy           *EnergyMeter
	build            BuildInfo
	logger           *slog.Logger
	pendingFanCurves []byte
	fanCurveRevision uint64
	fanCurveSequence uint32
	fanCurveSent     bool
	maintenance      bool
	bootRequested    bool
	hidOpen          bool
	firmwareSerial   string
	ledState         uint8
}

// SetLEDs 设置四个双色灯：0=关闭、1=红色、2=蓝色、3=红蓝同时亮。
// 状态在服务端编码成 74HC595 原始字节；暂不接入业务调用。
func (s *Service) SetLEDs(states [4]uint8) error {
	var encoded uint8
	for index, state := range states {
		if state > 3 {
			return fmt.Errorf("LED %d state %d must be between 0 and 3", index, state)
		}
		encoded |= state << (2 * index)
	}
	s.mu.Lock()
	s.ledState = encoded
	s.mu.Unlock()
	return nil
}

// NewService creates a panel service with shared configuration and metrics.
func NewService(store *Store, collector *Collector, energy *EnergyMeter, build BuildInfo, logger *slog.Logger) *Service {
	service := &Service{config: store, collector: collector, energy: energy, build: build, logger: logger}
	service.QueueFanCurves(store.Get().FanCurves)
	return service
}

// QueueFanCurves schedules both raw 20-byte curves for the next panel exchange.
func (s *Service) QueueFanCurves(curves FanCurves) {
	data := make([]byte, 0, FanCurvePayloadSize)
	data = append(data, curves.CPU[:]...)
	data = append(data, curves.HDD[:]...)
	s.mu.Lock()
	s.pendingFanCurves = data
	s.fanCurveRevision++
	s.fanCurveSent = false
	s.status.FanCurvePending = true
	s.mu.Unlock()
}

// Status returns an independent copy of the current panel state.
func (s *Service) Status() Status {
	s.mu.RLock()
	defer s.mu.RUnlock()
	status := s.status
	if s.status.LatestReport != nil {
		report := *s.status.LatestReport
		status.LatestReport = &report
	}
	return status
}

// Run keeps serving the configured panel until the context is canceled.
func (s *Service) Run(ctx context.Context) {
	for ctx.Err() == nil {
		s.mu.Lock()
		if s.maintenance {
			s.mu.Unlock()
			if wait(ctx, 100*time.Millisecond) == false {
				return
			}
			continue
		}
		s.hidOpen = true
		s.mu.Unlock()
		device, info, err := s.open()
		if err != nil {
			s.releaseHID(err)
			if wait(ctx, 2*time.Second) == false {
				return
			}
			continue
		}
		s.setConnected(info)
		s.logger.Info("panel connected", "serial", info.SerialNbr, "product", info.ProductStr)
		err = s.serve(ctx, device)
		_ = device.Close()
		s.releaseHID(err)
		if ctx.Err() != nil {
			return
		}
		if errors.Is(err, errFirmwareMaintenance) {
			continue
		}
		s.logger.Warn("panel disconnected", "error", err)
		if wait(ctx, time.Second) == false {
			return
		}
	}
}

func (s *Service) open() (*hid.Device, *hid.DeviceInfo, error) {
	cfg := s.config.Get()
	var device *hid.Device
	var err error
	if cfg.PanelSerial == "" {
		device, err = hid.OpenFirst(vendorID, productID)
	} else {
		device, err = hid.Open(vendorID, productID, cfg.PanelSerial)
	}
	if err != nil {
		return nil, nil, fmt.Errorf("open %04x:%04x: %w", vendorID, productID, err)
	}
	info, err := device.GetDeviceInfo()
	if err != nil {
		_ = device.Close()
		return nil, nil, fmt.Errorf("read panel identity: %w", err)
	}
	return device, info, nil
}

func (s *Service) serve(ctx context.Context, device *hid.Device) error {
	input := make([]byte, FrameSize)
	writeFailures := 0
	for ctx.Err() == nil {
		maintenance, boot := s.firmwareMode()
		if maintenance && boot == false {
			return errFirmwareMaintenance
		}
		n, err := device.ReadWithTimeout(input, time.Second)
		if errors.Is(err, hid.ErrTimeout) {
			continue
		}
		if err != nil {
			return fmt.Errorf("read report: %w", err)
		}
		if n != FrameSize {
			s.setProtocolError(fmt.Errorf("input report size %d", n))
			continue
		}
		request, err := DecodeRequest(input[:n])
		if err != nil {
			s.setProtocolError(err)
			continue
		}
		s.energy.Observe(request.Voltage, request.Current, time.Now())
		s.confirmSetting(request.Sequence)
		snapshot := s.collector.Current()
		response := responseFor(request, snapshot, s.config.Get(), s.build)
		settingRevision := uint64(0)
		if settingData, revision, pending := s.pendingSetting(); pending {
			response = Response{
				Type:           ResponseSetting,
				Setting:        SettingFanCurves,
				SettingData:    settingData,
				CPUTemperature: snapshot.CPUTemperature,
				HDDTemperature: snapshot.HDDTemperature,
			}
			settingRevision = revision
		}
		maintenance, boot = s.firmwareMode()
		if maintenance {
			if boot == false {
				return errFirmwareMaintenance
			}
			response = Response{Type: ResponseSetting, Setting: SettingBootloader}
			settingRevision = 0
		}
		s.mu.RLock()
		response.LEDState = s.ledState
		s.mu.RUnlock()
		frame, err := EncodeResponse(request.Sequence, response)
		if err != nil {
			s.setProtocolError(err)
			continue
		}
		output := make([]byte, FrameSize+1)
		copy(output[1:], frame[:])
		n, err = device.Write(output)
		if err != nil {
			writeFailures++
			writeErr := fmt.Errorf("write report: %w", err)
			s.setProtocolError(writeErr)
			if writeFailures >= 3 {
				return writeErr
			}
			continue
		}
		if n != len(output) {
			writeFailures++
			writeErr := fmt.Errorf("output report size %d, want %d", n, len(output))
			s.setProtocolError(writeErr)
			if writeFailures >= 3 {
				return writeErr
			}
			continue
		}
		if boot {
			return errFirmwareMaintenance
		}
		writeFailures = 0
		if settingRevision != 0 {
			s.markSettingWritten(settingRevision, request.Sequence)
		}
		s.setExchange(request)
	}
	return ctx.Err()
}

func (s *Service) pendingSetting() ([]byte, uint64, bool) {
	s.mu.RLock()
	defer s.mu.RUnlock()
	if len(s.pendingFanCurves) == 0 {
		return nil, 0, false
	}
	return append([]byte{}, s.pendingFanCurves...), s.fanCurveRevision, true
}

func (s *Service) markSettingWritten(revision uint64, sequence uint32) {
	s.mu.Lock()
	if s.fanCurveRevision == revision {
		s.fanCurveSequence = sequence
		s.fanCurveSent = true
	}
	s.mu.Unlock()
}

func (s *Service) confirmSetting(sequence uint32) {
	s.mu.Lock()
	if s.fanCurveSent && sequence != s.fanCurveSequence {
		s.pendingFanCurves = nil
		s.fanCurveSent = false
		s.status.FanCurvePending = false
	}
	s.mu.Unlock()
}

func responseFor(request Request, snapshot Snapshot, cfg Config, build BuildInfo) Response {
	response := Response{
		Page:           request.Page,
		CPUTemperature: snapshot.CPUTemperature,
		HDDTemperature: snapshot.HDDTemperature,
	}
	switch request.Page {
	case PageOverview:
		response.Overview = OverviewPayload{
			RunningMinutes: snapshot.RunningMinutes,
			CPULoad:        snapshot.CPULoad,
			MemoryLoad:     snapshot.MemoryLoad,
			Hostname:       snapshot.Hostname,
		}
	case PageNetwork:
		total := lengthByte(len(snapshot.Networks))
		response.Network.Index = request.ItemIndex
		response.Network.Total = total
		if int(request.ItemIndex) < len(snapshot.Networks) {
			network := snapshot.Networks[request.ItemIndex]
			response.Network = NetworkPayload{
				Index:        request.ItemIndex,
				Total:        total,
				Status:       network.Status,
				Name:         network.Name,
				UploadRate:   network.UploadRateKB,
				UploadKB:     network.UploadTotalKB,
				DownloadRate: network.DownloadRateKB,
				DownloadKB:   network.DownloadTotalKB,
				IPAddress:    network.IPAddress,
				Netmask:      network.Netmask,
				Gateway:      network.Gateway,
			}
		}
	case PageStorage:
		total := lengthByte(len(snapshot.Disks))
		response.Storage.Index = request.ItemIndex
		response.Storage.Total = total
		if int(request.ItemIndex) < len(snapshot.Disks) {
			storage := snapshot.Disks[request.ItemIndex]
			response.Storage = StoragePayload{
				Index:        request.ItemIndex,
				Total:        total,
				Path:         storage.Path,
				Capacity:     storage.Capacity,
				UsedPercent:  storage.UsedPercent,
				Status:       storage.Status,
				Temperature:  storage.Temperature,
				PowerOnHours: storage.PowerOnHours,
				Cycles:       storage.Cycles,
			}
		}
	case PageSystem:
		response.System = SystemPayload{
			Name:       snapshot.Hostname,
			OSName:     snapshot.OSName,
			CPUName:    snapshot.CPUName,
			MemoryName: snapshot.MemoryName,
		}
	case PageAbout:
		links := aboutLinks(snapshot, cfg)
		total := lengthByte(len(links))
		response.About.Index = request.ItemIndex
		response.About.Total = total
		response.About.ServerVersion = panelServerVersion(cfg.ServerVersion, build.Commit)
		if int(request.ItemIndex) < len(links) {
			response.About.URL = links[request.ItemIndex].URL
		}
	}
	return response
}

func panelServerVersion(version string, commit string) string {
	if strings.HasPrefix(version, "v") == false {
		version = "v" + version
	}
	return fmt.Sprintf("%s(%s)", version, commit)
}

func aboutLinks(snapshot Snapshot, cfg Config) []Link {
	links := make([]Link, 0, len(snapshot.Networks)+len(cfg.Links))
	seen := make(map[string]struct{})
	for _, network := range snapshot.Networks {
		if network.Status != 2 || network.IPAddress == "" {
			continue
		}
		address := fmt.Sprintf("%s://%s:%d", cfg.PublicScheme, network.IPAddress, cfg.WebPort)
		if cfg.BasePath != "" {
			address += cfg.BasePath + "/"
		}
		if len([]byte(address)) > 49 {
			continue
		}
		links = append(links, Link{Name: network.Name, URL: address})
		seen[address] = struct{}{}
	}
	for _, link := range cfg.Links {
		if _, exists := seen[link.URL]; exists {
			continue
		}
		links = append(links, link)
		seen[link.URL] = struct{}{}
	}
	return links
}

func (s *Service) setConnected(info *hid.DeviceInfo) {
	s.mu.Lock()
	s.status.Connected = true
	s.status.Serial = info.SerialNbr
	s.status.Product = info.ProductStr
	s.status.LastError = ""
	s.mu.Unlock()
}

func (s *Service) setDisconnected(err error) {
	s.mu.Lock()
	s.status.Connected = false
	s.fanCurveSent = false
	if err != nil {
		s.status.LastError = err.Error()
	}
	s.mu.Unlock()
}

func (s *Service) setProtocolError(err error) {
	s.mu.Lock()
	s.status.LastError = err.Error()
	s.mu.Unlock()
}

func (s *Service) setExchange(request Request) {
	s.mu.Lock()
	s.status.Connected = true
	s.status.LastSeen = time.Now()
	s.status.LastError = ""
	s.status.Responses++
	s.status.LatestReport = &request
	s.mu.Unlock()
}

func lengthByte(length int) uint8 {
	if length > 255 {
		return 255
	}
	return uint8(length)
}

func wait(ctx context.Context, duration time.Duration) bool {
	timer := time.NewTimer(duration)
	defer timer.Stop()
	select {
	case <-ctx.Done():
		return false
	case <-timer.C:
		return true
	}
}

var errFirmwareMaintenance = errors.New("HID paused for firmware update")

// configuredSerial 返回用户选择的面板，供 DFU 恢复模式筛选使用。
func (s *Service) configuredSerial() string { return s.config.Get().PanelSerial }

// firmwareMode 返回升级控制状态；只向选中的面板发送重启命令。
func (s *Service) firmwareMode() (bool, bool) {
	s.mu.RLock()
	defer s.mu.RUnlock()
	return s.maintenance, s.bootRequested && s.status.Serial == s.firmwareSerial
}

// suspendFirmware 停止 HID 重连，必要时让当前设备通过设置回复进入 bootloader。
func (s *Service) suspendFirmware(ctx context.Context, boot bool, serial string) error {
	s.mu.Lock()
	s.maintenance = true
	s.bootRequested = boot
	s.firmwareSerial = serial
	s.mu.Unlock()
	for {
		s.mu.RLock()
		opened := s.hidOpen
		s.mu.RUnlock()
		if opened == false {
			return nil
		}
		if wait(ctx, 100*time.Millisecond) == false {
			return fmt.Errorf("waiting for HID to stop: %w", ctx.Err())
		}
	}
}

// resumeFirmware 恢复正常 HID 连接和数据交换。
func (s *Service) resumeFirmware() {
	s.mu.Lock()
	s.bootRequested = false
	s.maintenance = false
	s.firmwareSerial = ""
	s.mu.Unlock()
}

// releaseHID 在句柄关闭后发布状态，避免 DFU 与 HID 同时操作设备。
func (s *Service) releaseHID(err error) {
	s.setDisconnected(err)
	s.mu.Lock()
	s.hidOpen = false
	s.mu.Unlock()
}
