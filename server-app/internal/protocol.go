package main

import (
	"encoding/binary"
	"errors"
	"fmt"
	"math"
)

const (
	Version             = 1
	FrameSize           = 256
	PayloadSize         = 246
	RequestSize         = 12
	FrameRequest        = 0
	FrameResponse       = 1
	PageOverview        = 0
	PageNetwork         = 1
	PageStorage         = 2
	PageSystem          = 3
	PageAbout           = 4
	PageCount           = 5
	ResponsePrefix      = 5
	ResponsePage        = 0
	ResponseSetting     = 1
	SettingFanCurves    = 0
	SettingBootloader   = 1
	FanCurvePoints      = 20
	FanCurvePayloadSize = FanCurvePoints * 2
)

// Request contains the report sent by the GD32 panel.
type Request struct {
	Sequence    uint32  `json:"sequence"`
	Page        uint8   `json:"page"`
	Voltage     float32 `json:"voltage"`
	Current     float32 `json:"current"`
	CPUFanSpeed uint8   `json:"cpuFanSpeed"`
	HDDFanSpeed uint8   `json:"hddFanSpeed"`
	ItemIndex   uint8   `json:"itemIndex"`
}

// OverviewPayload is the page-zero payload.
type OverviewPayload struct {
	RunningMinutes uint32
	CPULoad        uint8
	MemoryLoad     uint8
}

// NetworkPayload is one network interface payload.
type NetworkPayload struct {
	Index        uint8
	Total        uint8
	Status       uint8
	Name         string
	UploadRate   float32
	UploadKB     float32
	DownloadRate float32
	DownloadKB   float32
	IPAddress    string
	Netmask      string
	Gateway      string
}

// StoragePayload is one disk payload.
type StoragePayload struct {
	Index        uint8
	Total        uint8
	Path         string
	Capacity     uint64
	UsedPercent  uint8
	Status       uint8
	Temperature  uint8
	PowerOnHours uint32
	Cycles       uint32
}

// SystemPayload contains host identity strings.
type SystemPayload struct {
	Name       string
	OSName     string
	CPUName    string
	MemoryName string
}

// AboutPayload contains one configured QR link.
type AboutPayload struct {
	Index         uint8
	Total         uint8
	URL           string
	ServerVersion string
}

// Response contains common temperatures and exactly one page payload.
type Response struct {
	Type           uint8
	Page           uint8
	Setting        uint8
	SettingData    []byte
	CPUTemperature uint8
	HDDTemperature uint8
	Overview       OverviewPayload
	Network        NetworkPayload
	Storage        StoragePayload
	System         SystemPayload
	About          AboutPayload
}

// DecodeRequest validates and decodes one 256-byte HID input report.
func DecodeRequest(frame []byte) (Request, error) {
	if len(frame) != FrameSize {
		return Request{}, fmt.Errorf("frame size %d, want %d", len(frame), FrameSize)
	}
	if frame[0] != Version {
		return Request{}, fmt.Errorf("protocol version %d, want %d", frame[0], Version)
	}
	if frame[1] != FrameRequest || frame[2] != 0 {
		return Request{}, errors.New("invalid request header")
	}
	length := int(binary.LittleEndian.Uint16(frame[7:9]))
	if length != RequestSize || length > PayloadSize {
		return Request{}, fmt.Errorf("request payload size %d", length)
	}
	payload := frame[10 : 10+length]
	if CRC8(payload) != frame[9] {
		return Request{}, errors.New("request CRC mismatch")
	}
	request := Request{
		Sequence:    binary.LittleEndian.Uint32(frame[3:7]),
		Page:        payload[0],
		Voltage:     math.Float32frombits(binary.LittleEndian.Uint32(payload[1:5])),
		Current:     math.Float32frombits(binary.LittleEndian.Uint32(payload[5:9])),
		CPUFanSpeed: payload[9],
		HDDFanSpeed: payload[10],
		ItemIndex:   payload[11],
	}
	if request.Page >= PageCount {
		return Request{}, fmt.Errorf("unknown page %d", request.Page)
	}
	if math.IsNaN(float64(request.Voltage)) || math.IsInf(float64(request.Voltage), 0) ||
		math.IsNaN(float64(request.Current)) || math.IsInf(float64(request.Current), 0) {
		return Request{}, errors.New("invalid power measurement")
	}
	if request.CPUFanSpeed > 100 || request.HDDFanSpeed > 100 {
		return Request{}, errors.New("invalid fan percentage")
	}
	return request, nil
}

// EncodeResponse encodes a page response in the firmware protocol layout.
func EncodeResponse(sequence uint32, response Response) ([FrameSize]byte, error) {
	var frame [FrameSize]byte
	payload := make([]byte, 0, PayloadSize)
	payload = append(payload, response.Type, 1)
	if response.Type == ResponseSetting {
		if response.Setting != SettingFanCurves && response.Setting != SettingBootloader {
			return frame, fmt.Errorf("unknown setting %d", response.Setting)
		}
		if response.Setting == SettingBootloader && len(response.SettingData) != 0 {
			return frame, errors.New("bootloader setting must not contain data")
		}
		if response.Setting == SettingFanCurves && len(response.SettingData) != FanCurvePayloadSize {
			return frame, fmt.Errorf("fan curve payload size %d, want %d", len(response.SettingData), FanCurvePayloadSize)
		}
		payload = append(payload, response.Setting, response.CPUTemperature, response.HDDTemperature)
		payload = append(payload, response.SettingData...)
	} else if response.Type == ResponsePage {
		if response.Page >= PageCount {
			return frame, fmt.Errorf("unknown page %d", response.Page)
		}
		payload = append(payload, response.Page, response.CPUTemperature, response.HDDTemperature)
	} else {
		return frame, fmt.Errorf("unknown response type %d", response.Type)
	}
	if response.Type == ResponseSetting {
		return encodeFrame(sequence, payload), nil
	}
	switch response.Page {
	case PageOverview:
		payload = appendUint32(payload, response.Overview.RunningMinutes)
		payload = append(payload, response.Overview.CPULoad, response.Overview.MemoryLoad)
	case PageNetwork:
		payload = append(payload, response.Network.Index, response.Network.Total, response.Network.Status)
		payload = appendString(payload, response.Network.Name, 12)
		payload = appendFloat32(payload, response.Network.UploadRate)
		payload = appendFloat32(payload, response.Network.UploadKB)
		payload = appendFloat32(payload, response.Network.DownloadRate)
		payload = appendFloat32(payload, response.Network.DownloadKB)
		payload = appendString(payload, response.Network.IPAddress, 16)
		payload = appendString(payload, response.Network.Netmask, 16)
		payload = appendString(payload, response.Network.Gateway, 16)
	case PageStorage:
		payload = append(payload, response.Storage.Index, response.Storage.Total)
		payload = appendString(payload, response.Storage.Path, 12)
		payload = appendUint64(payload, response.Storage.Capacity)
		payload = append(payload, response.Storage.UsedPercent, response.Storage.Status, response.Storage.Temperature)
		payload = appendUint32(payload, response.Storage.PowerOnHours)
		payload = appendUint32(payload, response.Storage.Cycles)
	case PageSystem:
		payload = appendString(payload, response.System.Name, 12)
		payload = appendString(payload, response.System.OSName, 80)
		payload = appendString(payload, response.System.CPUName, 50)
		payload = appendString(payload, response.System.MemoryName, 50)
	case PageAbout:
		payload = append(payload, response.About.Index, response.About.Total)
		payload = appendString(payload, response.About.URL, 50)
		payload = appendString(payload, response.About.ServerVersion, 30)
	}
	if len(payload) > PayloadSize {
		return frame, fmt.Errorf("response payload size %d", len(payload))
	}
	return encodeFrame(sequence, payload), nil
}

func encodeFrame(sequence uint32, payload []byte) [FrameSize]byte {
	var frame [FrameSize]byte
	frame[0] = Version
	frame[1] = FrameResponse
	binary.LittleEndian.PutUint32(frame[3:7], sequence)
	binary.LittleEndian.PutUint16(frame[7:9], uint16(len(payload)))
	frame[9] = CRC8(payload)
	copy(frame[10:], payload)
	return frame
}

// CRC8 calculates the CRC used by the firmware lookup table.
func CRC8(data []byte) uint8 {
	var crc uint8
	for _, value := range data {
		for bit := 0; bit < 8; bit++ {
			mix := (crc ^ value) & 0x80
			crc <<= 1
			if mix != 0 {
				crc ^= 0x4d
			}
			value <<= 1
		}
	}
	return crc
}

func appendUint32(dst []byte, value uint32) []byte {
	var encoded [4]byte
	binary.LittleEndian.PutUint32(encoded[:], value)
	return append(dst, encoded[:]...)
}

func appendUint64(dst []byte, value uint64) []byte {
	var encoded [8]byte
	binary.LittleEndian.PutUint64(encoded[:], value)
	return append(dst, encoded[:]...)
}

func appendFloat32(dst []byte, value float32) []byte {
	return appendUint32(dst, math.Float32bits(value))
}

func appendString(dst []byte, value string, size int) []byte {
	start := len(dst)
	dst = append(dst, make([]byte, size)...)
	copy(dst[start:], []byte(value))
	return dst
}
