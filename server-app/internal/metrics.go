package main

import (
	"bufio"
	"bytes"
	"context"
	"encoding/json"
	"errors"
	"fmt"
	"log/slog"
	"math"
	"os"
	"os/exec"
	"path/filepath"
	"runtime"
	"sort"
	"strconv"
	"strings"
	"sync"
	"time"

	"github.com/shirou/gopsutil/v4/cpu"
	"github.com/shirou/gopsutil/v4/disk"
	"github.com/shirou/gopsutil/v4/host"
	"github.com/shirou/gopsutil/v4/mem"
	netstat "github.com/shirou/gopsutil/v4/net"
	"github.com/shirou/gopsutil/v4/sensors"
)

// Network describes one interface displayed by the panel and web UI.
type Network struct {
	Name            string  `json:"name"`
	Status          uint8   `json:"status"`
	IPAddress       string  `json:"ipAddress"`
	Netmask         string  `json:"netmask"`
	Gateway         string  `json:"gateway"`
	UploadRateKB    float32 `json:"uploadRateKB"`
	DownloadRateKB  float32 `json:"downloadRateKB"`
	UploadTotalKB   float32 `json:"uploadTotalKB"`
	DownloadTotalKB float32 `json:"downloadTotalKB"`
}

// Disk describes one physical storage device.
type Disk struct {
	UUID           string `json:"uuid"`
	SMARTAvailable bool   `json:"smartAvailable"`
	Path           string `json:"path"`
	Mountpoint     string `json:"mountpoint"`
	Capacity       uint64 `json:"capacity"`
	UsedPercent    uint8  `json:"usedPercent"`
	Status         uint8  `json:"status"`
	Temperature    uint8  `json:"temperature"`
	PowerOnHours   uint32 `json:"powerOnHours"`
	Cycles         uint32 `json:"cycles"`
}

// Snapshot is the latest system state used by both transports.
type Snapshot struct {
	UpdatedAt      time.Time `json:"updatedAt"`
	Hostname       string    `json:"hostname"`
	OSName         string    `json:"osName"`
	CPUName        string    `json:"cpuName"`
	MemoryName     string    `json:"memoryName"`
	RunningMinutes uint32    `json:"runningMinutes"`
	CPULoad        uint8     `json:"cpuLoad"`
	MemoryLoad     uint8     `json:"memoryLoad"`
	CPUTemperature uint8     `json:"cpuTemperature"`
	HDDTemperature uint8     `json:"hddTemperature"`
	Networks       []Network `json:"networks"`
	Disks          []Disk    `json:"disks"`
}

type networkSample struct {
	sent     uint64
	received uint64
	at       time.Time
}

type smartResult struct {
	healthKnown bool
	temperature uint8
	status      uint8
	hours       uint32
	cycles      uint32
}

var errSMARTStandby = errors.New("SMART check skipped: disk is in standby or sleep mode")

type physicalBlockDevice struct {
	name     string
	path     string
	capacity uint64
}

type diskUsageAggregate struct {
	used        uint64
	total       uint64
	mountpoints []string
}

// Collector periodically samples host metrics and keeps a synchronized snapshot.
type Collector struct {
	mu          sync.RWMutex
	snapshot    Snapshot
	previousNet map[string]networkSample
	physicalNet map[string]struct{}
	lastNetScan time.Time
	smart       map[string]smartResult
	lastSMART   time.Time
	diskIDs     map[string]string
	logger      *slog.Logger
}

// NewCollector creates an empty system collector.
func NewCollector(logger *slog.Logger) *Collector {
	return &Collector{
		previousNet: make(map[string]networkSample),
		physicalNet: make(map[string]struct{}),
		smart:       make(map[string]smartResult),
		logger:      logger,
	}
}

// Run samples immediately and then every two seconds until cancellation.
func (c *Collector) Run(ctx context.Context) {
	c.sample(ctx)
	ticker := time.NewTicker(2 * time.Second)
	defer ticker.Stop()
	for {
		select {
		case <-ctx.Done():
			return
		case <-ticker.C:
			c.sample(ctx)
		}
	}
}

// Current returns an independent copy of the latest system snapshot.
func (c *Collector) Current() Snapshot {
	c.mu.RLock()
	defer c.mu.RUnlock()
	snapshot := c.snapshot
	snapshot.Networks = append([]Network(nil), c.snapshot.Networks...)
	snapshot.Disks = append([]Disk(nil), c.snapshot.Disks...)
	return snapshot
}

func (c *Collector) sample(ctx context.Context) {
	now := time.Now()
	snapshot := Snapshot{UpdatedAt: now}
	info, err := host.InfoWithContext(ctx)
	if err == nil {
		snapshot.Hostname = info.Hostname
		snapshot.OSName = strings.TrimSpace(info.Platform + " " + info.PlatformVersion)
		snapshot.RunningMinutes = clampUint32(info.Uptime / 60)
	} else {
		snapshot.Hostname, _ = os.Hostname()
		snapshot.OSName = runtime.GOOS
	}
	if cpuInfo, cpuErr := cpu.InfoWithContext(ctx); cpuErr == nil && len(cpuInfo) != 0 {
		snapshot.CPUName = cpuInfo[0].ModelName
	}
	if loads, cpuErr := cpu.PercentWithContext(ctx, 0, false); cpuErr == nil && len(loads) != 0 {
		snapshot.CPULoad = percent(loads[0])
	}
	if memory, memoryErr := mem.VirtualMemoryWithContext(ctx); memoryErr == nil {
		snapshot.MemoryLoad = percent(memory.UsedPercent)
		snapshot.MemoryName = formatBytes(memory.Total)
	}
	snapshot.CPUTemperature, snapshot.HDDTemperature = temperatures(ctx)
	snapshot.Networks = c.networks(ctx, now)
	snapshot.Disks = c.disks(ctx, now, snapshot.HDDTemperature)
	for _, storage := range snapshot.Disks {
		if storage.Temperature > snapshot.HDDTemperature {
			snapshot.HDDTemperature = storage.Temperature
		}
	}
	c.mu.Lock()
	c.snapshot = snapshot
	c.mu.Unlock()
}

func (c *Collector) networks(ctx context.Context, now time.Time) []Network {
	if now.Sub(c.lastNetScan) >= 30*time.Second {
		c.physicalNet = physicalNetworkNames(ctx)
		c.lastNetScan = now
	}
	interfaces, _ := netstat.InterfacesWithContext(ctx)
	counters, _ := netstat.IOCountersWithContext(ctx, true)
	byName := make(map[string]netstat.IOCountersStat, len(counters))
	for _, counter := range counters {
		byName[counter.Name] = counter
	}
	gatewayName, gateway := defaultGateway(ctx)
	result := make([]Network, 0, len(interfaces))
	for _, iface := range interfaces {
		if c.shouldIncludeNetwork(iface) == false {
			continue
		}
		network := Network{Name: iface.Name}
		linkUp := networkLinkUp(ctx, iface)
		if linkUp {
			network.Status = 1
		}
		for _, address := range iface.Addrs {
			ip, prefix, found := parseIPv4(address.Addr)
			if found {
				network.IPAddress = ip
				network.Netmask = prefix
				if linkUp {
					network.Status = 2
				}
				break
			}
		}
		if iface.Name == gatewayName {
			network.Gateway = gateway
		}
		if counter, found := byName[iface.Name]; found {
			network.UploadTotalKB = float32(counter.BytesSent) / 1024
			network.DownloadTotalKB = float32(counter.BytesRecv) / 1024
			if previous, exists := c.previousNet[iface.Name]; exists &&
				counter.BytesSent >= previous.sent && counter.BytesRecv >= previous.received {
				seconds := now.Sub(previous.at).Seconds()
				if seconds > 0 {
					network.UploadRateKB = float32(float64(counter.BytesSent-previous.sent) / seconds / 1024)
					network.DownloadRateKB = float32(float64(counter.BytesRecv-previous.received) / seconds / 1024)
				}
			}
			c.previousNet[iface.Name] = networkSample{sent: counter.BytesSent, received: counter.BytesRecv, at: now}
		}
		result = append(result, network)
	}
	sort.Slice(result, func(i, j int) bool { return result[i].Name < result[j].Name })
	return result
}

func (c *Collector) disks(ctx context.Context, now time.Time, fallbackTemperature uint8) []Disk {
	partitions, _ := disk.PartitionsWithContext(ctx, false)
	if runtime.GOOS == "linux" {
		return c.linuxPhysicalDisks(ctx, now, partitions, fallbackTemperature)
	}
	return c.mountedDisks(ctx, now, partitions, fallbackTemperature)
}

func (c *Collector) linuxPhysicalDisks(
	ctx context.Context,
	now time.Time,
	partitions []disk.PartitionStat,
	fallbackTemperature uint8,
) []Disk {
	devices := physicalBlockDevices()
	stableIDs := diskStableIDs("/dev/disk/by-id")
	// 设备号复用时丢弃旧盘缓存；设备增减后立即刷新。
	currentIDs := make(map[string]string, len(devices))
	for _, device := range devices {
		currentIDs[device.path] = stableIDs[device.path]
		previousID, existed := c.diskIDs[device.path]
		if !existed || previousID != currentIDs[device.path] {
			delete(c.smart, device.path)
			c.lastSMART = time.Time{}
		}
	}
	for path := range c.diskIDs {
		if _, exists := currentIDs[path]; !exists {
			delete(c.smart, path)
		}
	}
	c.diskIDs = currentIDs
	devicePaths := make([]string, 0, len(devices))
	physicalByName := make(map[string]physicalBlockDevice, len(devices))
	for _, device := range devices {
		devicePaths = append(devicePaths, device.path)
		physicalByName[device.name] = device
	}
	c.refreshSMART(ctx, now, devicePaths)

	usageByDevice := make(map[string]*diskUsageAggregate, len(devices))
	seenMounts := make(map[string]struct{})
	for _, partition := range partitions {
		if strings.HasPrefix(partition.Device, "/dev/") == false {
			continue
		}
		mountKey := partition.Device + "\x00" + partition.Mountpoint
		if _, exists := seenMounts[mountKey]; exists {
			continue
		}
		seenMounts[mountKey] = struct{}{}
		usage, err := disk.UsageWithContext(ctx, partition.Mountpoint)
		if err != nil {
			continue
		}
		blockName := linuxBlockName(partition.Device)
		parents := linuxPhysicalParents(blockName, physicalByName, make(map[string]bool))
		for _, parent := range parents {
			aggregate := usageByDevice[parent]
			if aggregate == nil {
				aggregate = &diskUsageAggregate{}
				usageByDevice[parent] = aggregate
			}
			aggregate.used += usage.Used
			aggregate.total += usage.Total
			aggregate.mountpoints = appendUnique(aggregate.mountpoints, partition.Mountpoint)
		}
	}

	result := make([]Disk, 0, len(devices))
	for _, device := range devices {
		storage := Disk{
			Path:        device.path,
			UUID:        stableIDs[device.path],
			Capacity:    device.capacity,
			Temperature: fallbackTemperature,
		}
		if usage := usageByDevice[device.name]; usage != nil {
			storage.Mountpoint = strings.Join(usage.mountpoints, ", ")
			if usage.total != 0 {
				storage.UsedPercent = percent(float64(usage.used) * 100 / float64(usage.total))
			}
		}
		applySMART(&storage, c.smart[device.path])
		result = append(result, storage)
	}
	return result
}

func (c *Collector) mountedDisks(
	ctx context.Context,
	now time.Time,
	partitions []disk.PartitionStat,
	fallbackTemperature uint8,
) []Disk {
	devicePaths := make([]string, 0, len(partitions))
	for _, partition := range partitions {
		if shouldIncludeDisk(partition) {
			devicePaths = append(devicePaths, partition.Device)
		}
	}
	c.refreshSMART(ctx, now, devicePaths)

	seen := make(map[string]struct{})
	result := make([]Disk, 0, len(partitions))
	for _, partition := range partitions {
		if shouldIncludeDisk(partition) == false {
			continue
		}
		if _, exists := seen[partition.Device]; exists {
			continue
		}
		usage, err := disk.UsageWithContext(ctx, partition.Mountpoint)
		if err != nil {
			continue
		}
		seen[partition.Device] = struct{}{}
		storage := Disk{
			Path:        partition.Device,
			Mountpoint:  partition.Mountpoint,
			Capacity:    usage.Total,
			UsedPercent: percent(usage.UsedPercent),
			Temperature: fallbackTemperature,
		}
		applySMART(&storage, c.smart[partition.Device])
		result = append(result, storage)
	}
	sort.Slice(result, func(i, j int) bool { return result[i].Path < result[j].Path })
	return result
}

// refreshSMART 定期采集，休眠时保留上次数据，并清理已移除设备的缓存。
func (c *Collector) refreshSMART(ctx context.Context, now time.Time, devices []string) {
	if now.Sub(c.lastSMART) < time.Minute {
		return
	}
	previous := c.smart
	c.smart = make(map[string]smartResult)
	for _, device := range devices {
		if _, exists := c.smart[device]; exists {
			continue
		}
		if result, err := readSMART(ctx, device); err == nil {
			c.smart[device] = result
		} else if errors.Is(err, errSMARTStandby) {
			if cached, ok := previous[device]; ok {
				c.smart[device] = cached
			}
		} else {
			c.logger.Warn("SMART data unavailable", "device", device, "error", err)
		}
	}
	c.lastSMART = now
}

// applySMART 将有效 SMART 结果及健康状态可用性应用到磁盘快照。
func applySMART(storage *Disk, smart smartResult) {
	storage.SMARTAvailable = smart.healthKnown
	storage.Status = smart.status
	storage.PowerOnHours = smart.hours
	storage.Cycles = smart.cycles
	if smart.temperature != 0 {
		storage.Temperature = smart.temperature
	}
}

func physicalBlockDevices() []physicalBlockDevice {
	entries, err := os.ReadDir("/sys/class/block")
	if err != nil {
		return nil
	}
	result := make([]physicalBlockDevice, 0, len(entries))
	for _, entry := range entries {
		classPath := filepath.Join("/sys/class/block", entry.Name())
		if _, err := os.Stat(filepath.Join(classPath, "partition")); err == nil {
			continue
		}
		resolved, err := filepath.EvalSymlinks(classPath)
		if err != nil || strings.Contains(resolved, string(filepath.Separator)+"virtual"+string(filepath.Separator)) {
			continue
		}
		if _, err := os.Stat(filepath.Join(classPath, "device")); err != nil {
			continue
		}
		// SCSI/SATA 离线设备即使仍有 sysfs 节点，也不应继续展示缓存的健康状态。
		if state, err := os.ReadFile(filepath.Join(classPath, "device", "state")); err == nil && strings.TrimSpace(string(state)) == "offline" {
			continue
		}
		data, err := os.ReadFile(filepath.Join(classPath, "size"))
		if err != nil {
			continue
		}
		sectors, err := strconv.ParseUint(strings.TrimSpace(string(data)), 10, 64)
		if err != nil || sectors == 0 || sectors > math.MaxUint64/512 {
			continue
		}
		result = append(result, physicalBlockDevice{
			name:     entry.Name(),
			path:     filepath.Join("/dev", entry.Name()),
			capacity: sectors * 512,
		})
	}
	sort.Slice(result, func(i, j int) bool { return result[i].name < result[j].name })
	return result
}

func linuxBlockName(device string) string {
	resolved, err := filepath.EvalSymlinks(device)
	if err == nil {
		return filepath.Base(resolved)
	}
	return filepath.Base(device)
}

func linuxPhysicalParents(
	name string,
	physical map[string]physicalBlockDevice,
	visited map[string]bool,
) []string {
	if name == "" || visited[name] {
		return nil
	}
	visited[name] = true
	if _, exists := physical[name]; exists {
		return []string{name}
	}

	classPath := filepath.Join("/sys/class/block", name)
	if _, err := os.Stat(filepath.Join(classPath, "partition")); err == nil {
		resolved, resolveErr := filepath.EvalSymlinks(classPath)
		if resolveErr != nil {
			return nil
		}
		return linuxPhysicalParents(filepath.Base(filepath.Dir(resolved)), physical, visited)
	}

	entries, err := os.ReadDir(filepath.Join(classPath, "slaves"))
	if err != nil {
		return nil
	}
	result := make([]string, 0, len(entries))
	for _, entry := range entries {
		for _, parent := range linuxPhysicalParents(entry.Name(), physical, visited) {
			result = appendUnique(result, parent)
		}
	}
	return result
}

func appendUnique(values []string, value string) []string {
	for _, existing := range values {
		if existing == value {
			return values
		}
	}
	return append(values, value)
}

func temperatures(ctx context.Context) (uint8, uint8) {
	readings, err := sensors.TemperaturesWithContext(ctx)
	if err != nil {
		return 0, 0
	}
	var cpuTemperature uint8
	var hddTemperature uint8
	for _, sensor := range readings {
		value := temperature(sensor.Temperature)
		name := strings.ToLower(sensor.SensorKey)
		if containsText(name, "cpu", "core", "package", "k10temp", "tctl", "soc") && value > cpuTemperature {
			cpuTemperature = value
		}
		if containsText(name, "nvme", "disk", "drive", "ata") && value > hddTemperature {
			hddTemperature = value
		}
	}
	return cpuTemperature, hddTemperature
}

// readSMART 跳过待机或睡眠磁盘的 SMART 读取，并保留实际失败的诊断信息。
func readSMART(parent context.Context, device string) (smartResult, error) {
	ctx, cancel := context.WithTimeout(parent, 3*time.Second)
	defer cancel()
	command := exec.CommandContext(ctx, "smartctl", "-n", "standby", "-a", "-j", device)
	var stderr bytes.Buffer
	command.Stderr = &stderr
	data, commandErr := command.Output()
	if ctx.Err() != nil {
		return smartResult{}, fmt.Errorf("smartctl %s: %w", device, ctx.Err())
	}
	return parseSMART(data, stderr.String(), commandErr)
}

// parseSMART 解析结果；健康告警导致的非零退出码不应丢弃已读取的数据。
func parseSMART(data []byte, stderr string, commandErr error) (smartResult, error) {
	if len(data) == 0 {
		if commandErr == nil {
			commandErr = errors.New("smartctl returned no data")
		}
		return smartResult{}, fmt.Errorf("smartctl: %w; %s", commandErr, strings.TrimSpace(stderr))
	}
	var raw struct {
		Smartctl struct {
			ExitStatus int `json:"exit_status"`
			Messages   []struct {
				String string `json:"string"`
			} `json:"messages"`
		} `json:"smartctl"`
		Temperature struct {
			Current int `json:"current"`
		} `json:"temperature"`
		PowerMode struct {
			Name string `json:"name"`
		} `json:"power_mode"`
		PowerOnTime struct {
			Hours uint64 `json:"hours"`
		} `json:"power_on_time"`
		ATAAttributes struct {
			Table []struct {
				ID  int `json:"id"`
				Raw struct {
					Value uint64 `json:"value"`
				} `json:"raw"`
			} `json:"table"`
		} `json:"ata_smart_attributes"`
		SMARTStatus struct {
			Passed *bool `json:"passed"`
		} `json:"smart_status"`
		NVMeHealth struct {
			CriticalWarning *uint8 `json:"critical_warning"`
		} `json:"nvme_smart_health_information_log"`
	}
	if err := json.Unmarshal(data, &raw); err != nil {
		return smartResult{}, fmt.Errorf("invalid smartctl JSON: %w; stderr: %s", err, strings.TrimSpace(stderr))
	}
	// 退出码 2 也可能表示权限不足，必须结合电源状态或明确的跳过消息判断。
	if raw.Smartctl.ExitStatus == 2 {
		switch raw.PowerMode.Name {
		case "STANDBY", "STANDBY_Y", "STANDBY_Z", "SLEEP":
			return smartResult{}, errSMARTStandby
		}
		for _, message := range raw.Smartctl.Messages {
			switch strings.TrimSpace(message.String) {
			case "Device is in STANDBY mode, exit(2)", "Device is in SLEEP mode, exit(2)",
				"Device is in STANDBY (OS) mode, exit(2)":
				return smartResult{}, errSMARTStandby
			}
		}
	}
	result := smartResult{
		healthKnown: raw.SMARTStatus.Passed != nil || raw.NVMeHealth.CriticalWarning != nil,
		temperature: temperature(float64(raw.Temperature.Current)),
		hours:       clampUint32(raw.PowerOnTime.Hours),
	}
	// 属性 4 的原始值表示启停次数，不能使用归一化值或通电次数替代。
	for _, attribute := range raw.ATAAttributes.Table {
		if attribute.ID == 4 {
			result.cycles = clampUint32(attribute.Raw.Value)
			break
		}
	}
	if raw.SMARTStatus.Passed != nil && *raw.SMARTStatus.Passed == false {
		result.status = 2
	} else if raw.NVMeHealth.CriticalWarning != nil && *raw.NVMeHealth.CriticalWarning != 0 {
		result.status = 1
	}
	if !result.healthKnown && result.temperature == 0 && result.hours == 0 && result.cycles == 0 {
		messages := make([]string, 0, len(raw.Smartctl.Messages)+1)
		for _, message := range raw.Smartctl.Messages {
			if message.String != "" {
				messages = append(messages, message.String)
			}
		}
		if strings.TrimSpace(stderr) != "" {
			messages = append(messages, strings.TrimSpace(stderr))
		}
		if commandErr != nil {
			messages = append(messages, commandErr.Error())
		}
		return smartResult{}, fmt.Errorf("SMART fields unavailable (exit status %d): %s", raw.Smartctl.ExitStatus, strings.Join(messages, "; "))
	}
	return result, nil
}

func defaultGateway(ctx context.Context) (string, string) {
	if runtime.GOOS == "darwin" {
		return darwinDefaultGateway(ctx)
	}
	if runtime.GOOS != "linux" {
		return "", ""
	}
	file, err := os.Open("/proc/net/route")
	if err != nil {
		return "", ""
	}
	defer file.Close()
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		fields := strings.Fields(scanner.Text())
		if len(fields) < 3 || fields[1] != "00000000" || len(fields[2]) != 8 {
			continue
		}
		value, err := strconv.ParseUint(fields[2], 16, 32)
		if err != nil {
			continue
		}
		return fields[0], fmt.Sprintf("%d.%d.%d.%d", byte(value), byte(value>>8), byte(value>>16), byte(value>>24))
	}
	return "", ""
}

func darwinDefaultGateway(ctx context.Context) (string, string) {
	data, err := exec.CommandContext(ctx, "route", "-n", "get", "default").Output()
	if err != nil {
		return "", ""
	}
	var interfaceName string
	var gateway string
	for _, line := range strings.Split(string(data), "\n") {
		fields := strings.Fields(line)
		if len(fields) < 2 {
			continue
		}
		switch strings.TrimSuffix(fields[0], ":") {
		case "interface":
			interfaceName = fields[1]
		case "gateway":
			gateway = fields[1]
		}
	}
	return interfaceName, gateway
}

func parseIPv4(address string) (string, string, bool) {
	parts := strings.SplitN(address, "/", 2)
	if len(parts) != 2 || strings.Contains(parts[0], ":") {
		return "", "", false
	}
	prefix, err := strconv.Atoi(parts[1])
	if err != nil || prefix < 0 || prefix > 32 {
		return "", "", false
	}
	mask := uint32(0)
	if prefix != 0 {
		mask = ^uint32(0) << (32 - prefix)
	}
	return parts[0], fmt.Sprintf("%d.%d.%d.%d", byte(mask>>24), byte(mask>>16), byte(mask>>8), byte(mask)), true
}

func contains(values []string, wanted string) bool {
	for _, value := range values {
		if value == wanted {
			return true
		}
	}
	return false
}

func (c *Collector) shouldIncludeNetwork(iface netstat.InterfaceStat) bool {
	if iface.Name == "lo" || contains(iface.Flags, "loopback") {
		return false
	}
	if len(c.physicalNet) != 0 {
		_, found := c.physicalNet[iface.Name]
		return found
	}
	ignoredPrefixes := []string{
		"anpi", "ap", "awdl", "docker", "gif", "llw", "p2p", "stf", "tap",
		"tun", "utun", "veth", "virbr", "br-",
	}
	for _, prefix := range ignoredPrefixes {
		if strings.HasPrefix(iface.Name, prefix) {
			return false
		}
	}
	return iface.HardwareAddr != ""
}

func physicalNetworkNames(ctx context.Context) map[string]struct{} {
	result := make(map[string]struct{})
	switch runtime.GOOS {
	case "linux":
		entries, err := os.ReadDir("/sys/class/net")
		if err != nil {
			return result
		}
		for _, entry := range entries {
			if _, err := os.Stat(filepath.Join("/sys/class/net", entry.Name(), "device")); err == nil {
				result[entry.Name()] = struct{}{}
			}
		}
	case "darwin":
		data, err := exec.CommandContext(ctx, "networksetup", "-listallhardwareports").Output()
		if err != nil {
			return result
		}
		for _, line := range strings.Split(string(data), "\n") {
			if strings.HasPrefix(line, "Device: ") {
				name := strings.TrimSpace(strings.TrimPrefix(line, "Device: "))
				if name != "" {
					result[name] = struct{}{}
				}
			}
		}
	}
	return result
}

func networkLinkUp(ctx context.Context, iface netstat.InterfaceStat) bool {
	if contains(iface.Flags, "up") == false {
		return false
	}
	switch runtime.GOOS {
	case "linux":
		data, err := os.ReadFile(filepath.Join("/sys/class/net", iface.Name, "carrier"))
		if err != nil {
			return contains(iface.Flags, "running")
		}
		return strings.TrimSpace(string(data)) == "1"
	case "darwin":
		data, err := exec.CommandContext(ctx, "ifconfig", iface.Name).Output()
		if err != nil {
			return false
		}
		return strings.Contains(string(data), "status: active")
	default:
		return true
	}
}

func shouldIncludeDisk(partition disk.PartitionStat) bool {
	if strings.HasPrefix(partition.Device, "/dev/") == false {
		return false
	}
	if runtime.GOOS != "darwin" {
		return true
	}
	return partition.Mountpoint == "/" || strings.HasPrefix(partition.Mountpoint, "/Volumes/")
}

func containsText(value string, wanted ...string) bool {
	for _, part := range wanted {
		if strings.Contains(value, part) {
			return true
		}
	}
	return false
}

func percent(value float64) uint8 {
	if math.IsNaN(value) || value <= 0 {
		return 0
	}
	if value >= 100 {
		return 100
	}
	return uint8(math.Round(value))
}

func temperature(value float64) uint8 {
	if math.IsNaN(value) || value <= 0 {
		return 0
	}
	if value >= 255 {
		return 255
	}
	return uint8(math.Round(value))
}

func clampUint32(value uint64) uint32 {
	if value > math.MaxUint32 {
		return math.MaxUint32
	}
	return uint32(value)
}

func formatBytes(value uint64) string {
	const gib = 1024 * 1024 * 1024
	return fmt.Sprintf("%.1f GB", float64(value)/gib)
}
