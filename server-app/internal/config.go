package main

import (
	"encoding/json"
	"errors"
	"fmt"
	"os"
	"path/filepath"
	"strings"
	"sync"
)

// Link describes one URL displayed as a QR code on the panel.
type Link struct {
	Name string `json:"name"`
	URL  string `json:"url"`
}

// FanCurves contains the 5-degree PWM lookup values used by the panel.
type FanCurves struct {
	CPU FanCurve `json:"cpu"`
	HDD FanCurve `json:"hdd"`
}

// FanCurve is one fixed-length sequence of PWM percentages.
type FanCurve [FanCurvePoints]uint8

// UnmarshalJSON requires every fan curve to contain exactly 20 values.
func (curve *FanCurve) UnmarshalJSON(data []byte) error {
	var values []uint8
	if err := json.Unmarshal(data, &values); err != nil {
		return err
	}
	if len(values) != FanCurvePoints {
		return fmt.Errorf("fan curve must contain %d values", FanCurvePoints)
	}
	copy(curve[:], values)
	return nil
}

// Config contains user-editable server settings.
type Config struct {
	WebPort       uint16    `json:"webPort"`
	PanelSerial   string    `json:"panelSerial"`
	ServerVersion string    `json:"serverVersion"`
	PublicScheme  string    `json:"publicScheme"`
	BasePath      string    `json:"basePath"`
	Links         []Link    `json:"links"`
	FanCurves     FanCurves `json:"fanCurves"`
}

// Store provides synchronized access to the persisted configuration.
type Store struct {
	mu   sync.RWMutex
	path string
	cfg  Config
}

// Default returns a usable configuration for a local installation.
func Default() Config {
	return Config{
		WebPort:       8080,
		ServerVersion: "0.1.0",
		PublicScheme:  "http",
		Links:         []Link{},
		FanCurves:     defaultFanCurves(),
	}
}

// Load reads a configuration file or creates it with defaults when absent.
func Load(path string) (*Store, error) {
	store := &Store{path: path, cfg: Default()}
	data, err := os.ReadFile(path)
	if errors.Is(err, os.ErrNotExist) {
		if err := store.Save(store.cfg); err != nil {
			return nil, err
		}
		return store, nil
	}
	if err != nil {
		return nil, fmt.Errorf("read config: %w", err)
	}
	if err := json.Unmarshal(data, &store.cfg); err != nil {
		return nil, fmt.Errorf("decode config: %w", err)
	}
	normalized := normalizeStoredFanCurves(&store.cfg.FanCurves)
	if err := Validate(store.cfg); err != nil {
		return nil, fmt.Errorf("validate config: %w", err)
	}
	if normalized {
		if err := store.Save(store.cfg); err != nil {
			return nil, fmt.Errorf("normalize config: %w", err)
		}
	}
	return store, nil
}

// Get returns a copy of the current configuration.
func (s *Store) Get() Config {
	s.mu.RLock()
	defer s.mu.RUnlock()
	return clone(s.cfg)
}

// Save validates, persists, and publishes a configuration atomically.
func (s *Store) Save(cfg Config) error {
	if err := Validate(cfg); err != nil {
		return err
	}
	data, err := json.MarshalIndent(cfg, "", "  ")
	if err != nil {
		return fmt.Errorf("encode config: %w", err)
	}
	if err := os.MkdirAll(filepath.Dir(s.path), 0o755); err != nil {
		return fmt.Errorf("create config directory: %w", err)
	}
	temporary := s.path + ".tmp"
	if err := os.WriteFile(temporary, append(data, '\n'), 0o600); err != nil {
		return fmt.Errorf("write config: %w", err)
	}
	if err := os.Rename(temporary, s.path); err != nil {
		return fmt.Errorf("replace config: %w", err)
	}
	s.mu.Lock()
	s.cfg = clone(cfg)
	s.mu.Unlock()
	return nil
}

// Validate checks limits imposed by the firmware protocol.
func Validate(cfg Config) error {
	if cfg.WebPort == 0 {
		return errors.New("web port must be between 1 and 65535")
	}
	if len([]byte(cfg.ServerVersion)) > 9 {
		return errors.New("server version must fit in 9 UTF-8 bytes")
	}
	if cfg.PublicScheme != "http" && cfg.PublicScheme != "https" {
		return errors.New("public scheme must be http or https")
	}
	if cfg.BasePath != "" {
		if strings.HasPrefix(cfg.BasePath, "/") == false {
			return errors.New("base path must start with /")
		}
		if strings.HasSuffix(cfg.BasePath, "/") || strings.Contains(cfg.BasePath, "//") ||
			strings.ContainsAny(cfg.BasePath, "?#") {
			return errors.New("base path must not end with / or contain //, ? or #")
		}
		if len([]byte(cfg.BasePath)) > 19 {
			return errors.New("base path must fit in 19 UTF-8 bytes")
		}
	}
	if len(cfg.Links) > 255 {
		return errors.New("at most 255 links are supported")
	}
	for index, link := range cfg.Links {
		if strings.TrimSpace(link.Name) == "" {
			return fmt.Errorf("link %d name is required", index+1)
		}
		if strings.TrimSpace(link.URL) == "" {
			return fmt.Errorf("link %d URL is required", index+1)
		}
		if len([]byte(link.URL)) > 49 {
			return fmt.Errorf("link %d URL must fit in 49 UTF-8 bytes", index+1)
		}
	}
	if err := validateFanCurve("CPU", cfg.FanCurves.CPU); err != nil {
		return err
	}
	if err := validateFanCurve("HDD", cfg.FanCurves.HDD); err != nil {
		return err
	}
	return nil
}

func clone(cfg Config) Config {
	copied := cfg
	copied.Links = append([]Link{}, cfg.Links...)
	return copied
}

func defaultFanCurves() FanCurves {
	curve := FanCurve{0, 0, 30, 40, 50, 60, 70, 80, 90, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100}
	return FanCurves{
		CPU: curve,
		HDD: curve,
	}
}

func validateFanCurve(name string, curve FanCurve) error {
	for index, value := range curve {
		if value > 100 {
			return fmt.Errorf("%s fan curve value %d must be between 0 and 100", name, index)
		}
		if index > 0 && value < curve[index-1] {
			return fmt.Errorf("%s fan curve value %d must not be lower than value %d", name, index, index-1)
		}
	}
	return nil
}

func normalizeStoredFanCurves(curves *FanCurves) bool {
	cpuChanged := normalizeStoredFanCurve(&curves.CPU)
	hddChanged := normalizeStoredFanCurve(&curves.HDD)
	legacy := FanCurve{0, 0, 0, 0, 0, 0, 0, 30, 40, 50, 60, 70, 80, 90, 100, 100, 100, 100, 100, 100}
	defaults := defaultFanCurves()
	if curves.CPU == legacy {
		curves.CPU = defaults.CPU
		cpuChanged = true
	}
	if curves.HDD == legacy {
		curves.HDD = defaults.HDD
		hddChanged = true
	}
	return cpuChanged || hddChanged
}

func normalizeStoredFanCurve(curve *FanCurve) bool {
	changed := false
	for index := len(curve) - 2; index >= 0; index-- {
		if curve[index] > curve[index+1] {
			curve[index] = curve[index+1]
			changed = true
		}
	}
	return changed
}
