package main

import (
	"encoding/json"
	"errors"
	"fmt"
	"log/slog"
	"math"
	"os"
	"path/filepath"
	"strings"
	"sync"
	"time"

	"github.com/shirou/gopsutil/v4/host"
)

const (
	energySaveInterval = 30 * time.Second
	energyMaxSampleGap = 10 * time.Second
)

// EnergySnapshot describes the latest power sample and accumulated energy.
type EnergySnapshot struct {
	PowerW    float64   `json:"powerW"`
	BootKWh   float64   `json:"bootKWh"`
	TotalKWh  float64   `json:"totalKWh"`
	UpdatedAt time.Time `json:"updatedAt,omitempty"`
}

type persistedEnergy struct {
	BootID    string    `json:"bootId"`
	BootKWh   float64   `json:"bootKWh"`
	TotalKWh  float64   `json:"totalKWh"`
	UpdatedAt time.Time `json:"updatedAt"`
}

// EnergyMeter integrates panel power samples and persists the lifetime total.
type EnergyMeter struct {
	mu           sync.RWMutex
	path         string
	bootID       string
	snapshot     EnergySnapshot
	lastSampleAt time.Time
	lastPowerW   float64
	lastSavedAt  time.Time
	logger       *slog.Logger
}

// NewEnergyMeter loads the persisted lifetime energy counter.
func NewEnergyMeter(path string, logger *slog.Logger) (*EnergyMeter, error) {
	meter := &EnergyMeter{path: path, bootID: systemBootID(), logger: logger}
	data, err := os.ReadFile(path)
	if errors.Is(err, os.ErrNotExist) {
		return meter, nil
	}
	if err != nil {
		return nil, fmt.Errorf("read energy data: %w", err)
	}
	var stored persistedEnergy
	if err := json.Unmarshal(data, &stored); err != nil {
		return nil, fmt.Errorf("decode energy data: %w", err)
	}
	if math.IsNaN(stored.TotalKWh) || math.IsInf(stored.TotalKWh, 0) || stored.TotalKWh < 0 ||
		math.IsNaN(stored.BootKWh) || math.IsInf(stored.BootKWh, 0) || stored.BootKWh < 0 {
		return nil, errors.New("energy data contains an invalid total")
	}
	meter.snapshot.TotalKWh = stored.TotalKWh
	if stored.BootID == meter.bootID {
		meter.snapshot.BootKWh = stored.BootKWh
	}
	meter.lastSavedAt = time.Now()
	return meter, nil
}

// Observe integrates one voltage and current sample into the energy counters.
func (m *EnergyMeter) Observe(voltage float32, current float32, now time.Time) {
	powerW := float64(voltage) * float64(current)
	if math.IsNaN(powerW) || math.IsInf(powerW, 0) || powerW < 0 {
		return
	}

	m.mu.Lock()
	if m.lastSampleAt.IsZero() == false {
		elapsed := now.Sub(m.lastSampleAt)
		if elapsed > 0 && elapsed <= energyMaxSampleGap {
			energyKWh := (m.lastPowerW + powerW) * 0.5 * elapsed.Hours() / 1000
			m.snapshot.BootKWh += energyKWh
			m.snapshot.TotalKWh += energyKWh
		}
	}
	m.snapshot.PowerW = powerW
	m.snapshot.UpdatedAt = now
	m.lastPowerW = powerW
	m.lastSampleAt = now
	shouldSave := now.Sub(m.lastSavedAt) >= energySaveInterval
	bootKWh := m.snapshot.BootKWh
	totalKWh := m.snapshot.TotalKWh
	if shouldSave {
		m.lastSavedAt = now
	}
	m.mu.Unlock()

	if shouldSave {
		if err := m.persist(bootKWh, totalKWh, now); err != nil {
			m.logger.Warn("persist energy data", "error", err)
		}
	}
}

// Current returns the latest power and energy counters.
func (m *EnergyMeter) Current() EnergySnapshot {
	m.mu.RLock()
	defer m.mu.RUnlock()
	return m.snapshot
}

// Close flushes the current lifetime energy counter to disk.
func (m *EnergyMeter) Close() error {
	m.mu.RLock()
	bootKWh := m.snapshot.BootKWh
	totalKWh := m.snapshot.TotalKWh
	m.mu.RUnlock()
	return m.persist(bootKWh, totalKWh, time.Now())
}

func (m *EnergyMeter) persist(bootKWh float64, totalKWh float64, now time.Time) error {
	stored := persistedEnergy{BootID: m.bootID, BootKWh: bootKWh, TotalKWh: totalKWh, UpdatedAt: now}
	data, err := json.MarshalIndent(stored, "", "  ")
	if err != nil {
		return fmt.Errorf("encode energy data: %w", err)
	}
	if err := os.MkdirAll(filepath.Dir(m.path), 0o755); err != nil {
		return fmt.Errorf("create energy directory: %w", err)
	}
	temporary := m.path + ".tmp"
	if err := os.WriteFile(temporary, append(data, '\n'), 0o600); err != nil {
		return fmt.Errorf("write energy data: %w", err)
	}
	if err := os.Rename(temporary, m.path); err != nil {
		return fmt.Errorf("replace energy data: %w", err)
	}
	return nil
}

func systemBootID() string {
	if data, err := os.ReadFile("/proc/sys/kernel/random/boot_id"); err == nil {
		bootID := strings.TrimSpace(string(data))
		if bootID != "" {
			return bootID
		}
	}
	info, err := host.Info()
	if err == nil && info.BootTime != 0 {
		return fmt.Sprintf("%s:%d", info.HostID, info.BootTime)
	}
	return fmt.Sprintf("process:%d", os.Getpid())
}
