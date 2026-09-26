package main

import (
	"encoding/json"
	"fmt"
	"net/http"
	"time"
)

// getLEDConfig 返回灯位颜色与绑定。
func (s *Server) getLEDConfig(w http.ResponseWriter, _ *http.Request) {
	writeJSON(w, http.StatusOK, s.config.Get().LED)
}

// putLEDConfig 独立保存灯配置，不覆盖其他网页设置。
func (s *Server) putLEDConfig(w http.ResponseWriter, r *http.Request) {
	defer r.Body.Close()
	var cfg LEDConfig
	decoder := json.NewDecoder(http.MaxBytesReader(w, r.Body, 8192))
	decoder.DisallowUnknownFields()
	if err := decoder.Decode(&cfg); err != nil {
		writeError(w, 400, err)
		return
	}
	normalizeLEDColors(&cfg)
	if err := validateLEDConfig(cfg); err != nil {
		writeError(w, 400, err)
		return
	}
	// 检查在线硬盘的路径绑定与 UUID 绑定是否实际指向同一块磁盘。
	seen := map[string]bool{}
	for _, binding := range cfg.Bindings {
		disk := diskForLEDBinding(binding, s.collector.Current().Disks)
		if disk == nil {
			continue
		}
		if seen[disk.Path] {
			writeError(w, 409, fmt.Errorf("disk %s already occupies another LED", disk.Path))
			return
		}
		seen[disk.Path] = true
	}
	if err := s.config.SaveLED(cfg); err != nil {
		writeError(w, 400, err)
		return
	}
	writeJSON(w, http.StatusOK, cfg)
}

// testLED 发起有限时长的单通道测试，断开浏览器后也能自动结束。
func (s *Server) testLED(w http.ResponseWriter, r *http.Request) {
	defer r.Body.Close()
	var input struct {
		Position int   `json:"position"`
		State    uint8 `json:"state"`
	}
	decoder := json.NewDecoder(http.MaxBytesReader(w, r.Body, 1024))
	decoder.DisallowUnknownFields()
	if err := decoder.Decode(&input); err != nil {
		writeError(w, 400, err)
		return
	}
	if err := s.panel.TestLED(input.Position, input.State, time.Now()); err != nil {
		writeError(w, 400, err)
		return
	}
	writeJSON(w, http.StatusOK, map[string]int{"durationSeconds": 5})
}
