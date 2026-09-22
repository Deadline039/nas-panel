package main

import (
	"errors"
	"strings"
	"testing"
)

// TestParseSMART 验证用户硬盘输出中的字段、健康告警和失败诊断。
func TestParseSMART(t *testing.T) {
	tests := []struct {
		name, data, stderr string
		commandErr         error
		want               smartResult
		errorText          string
	}{
		{name: "WD Blue", data: `{"smartctl":{"exit_status":0},"smart_status":{"passed":true},"temperature":{"current":35},"power_on_time":{"hours":29052},"power_cycle_count":2205,"ata_smart_attributes":{"table":[{"id":4,"name":"Start_Stop_Count","value":94,"raw":{"value":6263}}]}}`, want: smartResult{temperature: 35, hours: 29052, cycles: 6263}},
		{name: "health failure retains metrics", data: `{"smartctl":{"exit_status":8},"smart_status":{"passed":false},"temperature":{"current":38},"power_on_time":{"hours":20},"power_cycle_count":1,"ata_smart_attributes":{"table":[{"id":4,"raw":{"value":3}}]}}`, commandErr: errors.New("exit status 8"), want: smartResult{temperature: 38, status: 2, hours: 20, cycles: 3}},
		{name: "missing start stop count", data: `{"smart_status":{"passed":true},"power_cycle_count":2205,"ata_smart_attributes":{"table":[{"id":12,"raw":{"value":2205}},{"id":193,"raw":{"value":24209}}]}}`, want: smartResult{}},
		{name: "zero start stop count", data: `{"smart_status":{"passed":true},"power_cycle_count":10,"ata_smart_attributes":{"table":[{"id":4,"raw":{"value":0}}]}}`, want: smartResult{}},
		{name: "start stop count saturation", data: `{"smart_status":{"passed":true},"ata_smart_attributes":{"table":[{"id":4,"raw":{"value":4294967296}}]}}`, want: smartResult{cycles: 4294967295}},
		{name: "permission", data: `{"smartctl":{"exit_status":2,"messages":[{"string":"Smartctl open device: /dev/sdb failed: Permission denied","severity":"error"}]}}`, commandErr: errors.New("exit status 2"), errorText: "Permission denied"},
		{name: "missing binary", commandErr: errors.New("smartctl: executable file not found in PATH"), errorText: "not found in PATH"},
		{name: "stderr", commandErr: errors.New("exit status 1"), stderr: "unsupported option -j", errorText: "unsupported option -j"},
		{name: "malformed", data: `not json`, stderr: "old smartctl", errorText: "invalid smartctl JSON"},
		{name: "empty success", data: `{}`, errorText: "SMART fields unavailable"},
		{name: "new drive with zero counters", data: `{"smart_status":{"passed":true},"power_on_time":{"hours":0},"power_cycle_count":0}`, want: smartResult{}},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			result, err := parseSMART([]byte(tt.data), tt.stderr, tt.commandErr)
			if tt.errorText != "" {
				if err == nil || strings.Contains(err.Error(), tt.errorText) == false {
					t.Fatalf("expected %q, got %v", tt.errorText, err)
				}
				return
			}
			if err != nil || result != tt.want {
				t.Fatalf("got %+v, %v; want %+v", result, err, tt.want)
			}
		})
	}
}
