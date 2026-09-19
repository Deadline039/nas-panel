package main

import (
	"encoding/binary"
	"errors"
	"hash/crc32"
)

const (
	firmwareBase    = 0x08008000
	firmwareLimit   = 0x080FE000
	firmwareMaxSize = firmwareLimit - firmwareBase
)

// validateFirmware 校验原始 APP 的大小、栈顶与复位向量，拒绝 bootloader 和旧地址镜像。
func validateFirmware(image []byte) error {
	if len(image) < 8 || len(image) > firmwareMaxSize {
		return errors.New("APP BIN size must be between 8 and 1007616 bytes")
	}
	stack := binary.LittleEndian.Uint32(image)
	reset := binary.LittleEndian.Uint32(image[4:])
	address := reset &^ 1
	if stack <= 0x20000000 || stack > 0x20018000 || stack&7 != 0 || reset&1 == 0 || address < firmwareBase+8 || uint64(address) >= uint64(firmwareBase)+uint64(len(image)) {
		return errors.New("invalid APP vectors: use a BIN linked at 0x08008000")
	}
	return nil
}

// firmwarePackage 生成与 bootloader 测试脚本相同的 DfuSe 文件，元数据先于 APP。
func firmwarePackage(image []byte) []byte {
	elements := appendUint32(nil, firmwareLimit)
	elements = appendUint32(elements, 8)
	elements = appendUint32(elements, uint32(len(image)))
	elements = appendUint32(elements, crc32.ChecksumIEEE(image))
	elements = appendUint32(elements, firmwareBase)
	elements = appendUint32(elements, uint32(len(image)))
	elements = append(elements, image...)
	target := append([]byte("Target"), 0)
	target = appendUint32(target, 1)
	name := make([]byte, 255)
	copy(name, "NAS Panel")
	target = append(target, name...)
	target = appendUint32(target, uint32(len(elements)))
	target = appendUint32(target, 2)
	target = append(target, elements...)
	data := append([]byte("DfuSe"), 1)
	data = appendUint32(data, uint32(11+len(target)))
	data = append(data, 1)
	data = append(data, target...)
	data = append(data, 0xff, 0xff, 0x27, 0x39, 0x39, 0x39, 0x1a, 0x01, 'U', 'F', 'D', 16)
	return appendUint32(data, crc32.ChecksumIEEE(data)^0xffffffff)
}
