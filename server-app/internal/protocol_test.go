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

// TestFirmwareVersionReport 验证独立 SET 命令及损坏数据的拒绝行为。
func TestFirmwareVersionReport(t *testing.T) {
	frame := make([]byte, FrameSize)
	frame[0], frame[1], frame[10] = Version, FrameSet, SettingFirmwareVersion
	binary.LittleEndian.PutUint32(frame[3:7], 42)
	binary.LittleEndian.PutUint16(frame[7:9], FirmwareVersionReportSize)
	copy(frame[11:41], "v0.1")
	copy(frame[41:50], "12345678")
	frame[9] = CRC8(frame[10:50])
	request, err := DecodeRequest(frame)
	if err != nil || request.Type != FrameSet || request.Sequence != 42 || request.FirmwareVersion != "v0.1" || request.FirmwareCommit != "12345678" {
		t.Fatalf("%+v: %v", request, err)
	}
	for _, offset := range []int{0, 1, 2, 7, 9, 10, 11} {
		broken := append([]byte(nil), frame...)
		broken[offset] ^= 0xff
		if _, err := DecodeRequest(broken); err == nil {
			t.Fatalf("accepted corrupt offset %d", offset)
		}
	}
	for i := 11; i < 41; i++ {
		frame[i] = 'x'
	}
	frame[9] = CRC8(frame[10:50])
	if _, err := DecodeRequest(frame); err == nil {
		t.Fatal("accepted unterminated version")
	}
	ack, err := EncodeResponse(42, Response{Type: ResponseSetting, Setting: SettingFirmwareVersion, LEDState: 0xe4})
	if err != nil || ack[12] != SettingFirmwareVersion || ack[15] != 0xe4 || binary.LittleEndian.Uint16(ack[7:9]) != ResponsePrefix {
		t.Fatalf("invalid ACK: %x %v", ack[:16], err)
	}
}
