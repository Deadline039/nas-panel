package main

import (
	"encoding/binary"
	"testing"
)

// TestLEDResponsePrefix 验证所有回复都携带原始 LED 字节且纳入长度与 CRC。
func TestLEDResponsePrefix(t *testing.T) {
	responses := []Response{
		{Page: PageOverview}, {Page: PageNetwork}, {Page: PageStorage},
		{Page: PageSystem}, {Page: PageAbout},
		{Type: ResponseSetting, Setting: SettingFanCurves, SettingData: make([]byte, FanCurvePayloadSize)},
		{Type: ResponseSetting, Setting: SettingBootloader},
	}
	sizes := []int{24, 85, 39, 198, 88, 46, 6}
	for i, response := range responses {
		response.LEDState = 0xe4
		response.CPUTemperature = 35
		response.HDDTemperature = 40
		frame, err := EncodeResponse(42, response)
		if err != nil {
			t.Fatal(err)
		}
		length := int(binary.LittleEndian.Uint16(frame[7:9]))
		if length != sizes[i] || frame[13] != 35 || frame[14] != 40 || frame[15] != 0xe4 {
			t.Fatalf("response %d: length %d, prefix %x", i, length, frame[10:16])
		}
		if CRC8(frame[10:10+length]) != frame[9] {
			t.Fatalf("response %d CRC mismatch", i)
		}
		frame[15] ^= 1
		if CRC8(frame[10:10+length]) == frame[9] {
			t.Fatal("LED bit not covered by CRC")
		}
	}
}

// TestSetLEDs 验证四灯编码顺序以及非法状态不会部分更新。
func TestSetLEDs(t *testing.T) {
	s := &Service{}
	if err := s.SetLEDs([4]uint8{0, 1, 2, 3}); err != nil {
		t.Fatal(err)
	}
	if s.ledState != 0xe4 {
		t.Fatalf("encoded %02x", s.ledState)
	}
	if err := s.SetLEDs([4]uint8{1, 2, 3, 4}); err == nil {
		t.Fatal("accepted invalid state")
	}
	if s.ledState != 0xe4 {
		t.Fatal("invalid states changed LEDs")
	}
	if err := s.SetLEDs([4]uint8{}); err != nil || s.ledState != 0 {
		t.Fatal("failed to clear LEDs")
	}
}
