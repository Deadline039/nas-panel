package main

import (
	"errors"
	"fmt"
	"time"
)

// LEDColors 记录两个物理通道的用户校准颜色，不参与硬件位编码。
type LEDColors struct {
	Color0 string `json:"color0"`
	Color1 string `json:"color1"`
}

// LEDBinding 将一块硬盘的三种健康状态独占绑定到一个灯位。
type LEDBinding struct {
	Path    string   `json:"path"`
	UUID    string   `json:"uuid"`
	UseUUID bool     `json:"useUUID"`
	States  [3]uint8 `json:"states"`
}

// LEDConfig 保存四个灯位的颜色及硬盘绑定。
type LEDConfig struct {
	SameColors bool          `json:"sameColors"`
	Colors     [4]LEDColors  `json:"colors"`
	Bindings   [4]LEDBinding `json:"bindings"`
}

// defaultLEDConfig 默认不绑定硬盘，所有灯熄灭。
func defaultLEDConfig() LEDConfig {
	c := LEDConfig{SameColors: true}
	for i := range c.Colors {
		c.Colors[i] = LEDColors{"red", "blue"}
	}
	return c
}

// normalizeLEDColors 统一颜色模式下将第一列复制到其余灯位。
func normalizeLEDColors(c *LEDConfig) {
	if c.SameColors {
		for i := 1; i < len(c.Colors); i++ {
			c.Colors[i] = c.Colors[0]
		}
	}
}

// validateLEDConfig 防止重复占用灯位、硬盘及颜色组合。
func validateLEDConfig(c LEDConfig) error {
	validColor := map[string]bool{"red": true, "blue": true, "green": true, "yellow": true, "orange": true, "white": true, "purple": true, "cyan": true}
	paths, ids := map[string]bool{}, map[string]bool{}
	for i, colors := range c.Colors {
		if !validColor[colors.Color0] || !validColor[colors.Color1] || colors.Color0 == colors.Color1 {
			return fmt.Errorf("LED %d requires two different colors", i+1)
		}
		b := c.Bindings[i]
		if b.Path == "" {
			if b.UUID != "" || b.UseUUID || b.States != [3]uint8{} {
				return fmt.Errorf("LED %d has an incomplete binding", i+1)
			}
			continue
		}
		if len(b.Path) > 256 || len(b.UUID) > 256 {
			return errors.New("disk identity is too long")
		}
		if b.UseUUID && b.UUID == "" {
			return errors.New("stable disk identity is unavailable")
		}
		if (!b.UseUUID && paths[b.Path]) || (b.UseUUID && ids[b.UUID]) {
			return errors.New("a disk can only occupy one LED")
		}
		if !b.UseUUID {
			paths[b.Path] = true
		}
		if b.UseUUID {
			ids[b.UUID] = true
		}
		used := map[uint8]bool{}
		for _, state := range b.States {
			if state < 1 || state > 3 || used[state] {
				return errors.New("each disk status must use a different LED color combination")
			}
			used[state] = true
		}
	}
	return nil
}

// diskForLEDBinding UUID 模式只匹配稳定标识，禁止退回可能被其他硬盘复用的路径。
func diskForLEDBinding(b LEDBinding, disks []Disk) *Disk {
	var found *Disk
	for i := range disks {
		d := &disks[i]
		match := b.Path != "" && d.Path == b.Path
		if b.UseUUID {
			match = b.UUID != "" && d.UUID == b.UUID
		}
		if match {
			if found != nil {
				return nil
			}
			found = d
		}
	}
	return found
}

// diskLEDStates 为无绑定、离线或无有效 SMART 数据的灯位返回关闭状态。
func diskLEDStates(c LEDConfig, disks []Disk) [4]uint8 {
	var states [4]uint8
	usedDisks := make(map[string]bool)
	for i, binding := range c.Bindings {
		disk := diskForLEDBinding(binding, disks)
		if disk == nil || !disk.SMARTAvailable || disk.Status > 2 || usedDisks[disk.Path] {
			continue
		}
		states[i] = binding.States[disk.Status]
		usedDisks[disk.Path] = true
	}
	return states
}

// responseLEDState 每帧重新计算状态；测试只覆盖一个灯位，并在截止时间后自动恢复。
func (s *Service) responseLEDState(cfg LEDConfig, snapshot Snapshot, now time.Time) uint8 {
	states := diskLEDStates(cfg, snapshot.Disks)
	// 采集线程停止更新时不能持续展示旧健康状态。
	if snapshot.UpdatedAt.IsZero() || now.Sub(snapshot.UpdatedAt) > 30*time.Second {
		states = [4]uint8{}
	}
	s.mu.Lock()
	defer s.mu.Unlock()
	if now.Before(s.ledTestUntil) {
		states[s.ledTestPosition] = s.ledTestState
	}
	var encoded uint8
	for i, state := range states {
		encoded |= state << (2 * i)
	}
	s.ledState = encoded
	return encoded
}

// TestLED 临时点亮指定通道，超时恢复，不修改持久配置。
func (s *Service) TestLED(position int, state uint8, now time.Time) error {
	if position < 0 || position >= 4 || state > 3 {
		return errors.New("invalid LED position or state")
	}
	s.mu.Lock()
	defer s.mu.Unlock()
	if !s.status.Connected || s.maintenance {
		return errors.New("panel is disconnected or updating firmware")
	}
	s.ledTestPosition, s.ledTestState = position, state
	s.ledTestUntil = now.Add(5 * time.Second)
	if state == 0 {
		s.ledTestUntil = time.Time{}
	}
	return nil
}
