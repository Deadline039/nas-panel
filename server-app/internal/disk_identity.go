package main

import (
	"os"
	"path/filepath"
	"strings"
)

// diskStableIDs 仅读取 udev 已创建的整盘标识链接，不读取设备内容或唤醒磁盘。
func diskStableIDs(directory string) map[string]string {
	ids := make(map[string]string)
	ranks := make(map[string]int)
	entries, err := os.ReadDir(directory)
	if err != nil {
		return ids
	}
	for _, entry := range entries {
		name := entry.Name()
		if strings.Contains(name, "-part") {
			continue
		}
		rank := 0
		switch {
		case strings.HasPrefix(name, "wwn-"):
			rank = 4
		case strings.HasPrefix(name, "nvme-eui.") || strings.HasPrefix(name, "nvme-uuid."):
			rank = 3
		case strings.HasPrefix(name, "ata-") || strings.HasPrefix(name, "scsi-"):
			rank = 2
		case strings.HasPrefix(name, "usb-") || strings.HasPrefix(name, "nvme-"):
			rank = 1
		default:
			continue
		}
		target, err := filepath.EvalSymlinks(filepath.Join(directory, name))
		if err != nil {
			continue
		}
		if rank > ranks[target] {
			ids[target], ranks[target] = name, rank
		}
	}
	return ids
}
