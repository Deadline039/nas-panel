#!/usr/bin/env python3
"""NAS panel HID mock server for protocol v1."""

import argparse
import math
import struct
import sys
import time

VID = 0x3939
PID = 0x0831
FRAME_SIZE = 256
PAYLOAD_SIZE = 246
VERSION = 1
FRAME_REQUEST = 0
FRAME_RESPONSE = 1
RESPONSE_PAGE_DATA = 0
RESPONSE_SETTING = 1
SETTING_FAN_CURVES = 0
FAN_CURVE = bytes((0, 0, 30, 40, 50, 60, 70, 80, 90, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100))

HEADER = struct.Struct("<BBBIHB")
REQUEST = struct.Struct("<BffBBB")
RESPONSE = struct.Struct("<BBBBBB")
LED_STATE = 0xE4  # 灯 0 关闭、灯 1 红色、灯 2 蓝色、灯 3 红蓝同时亮。
PAGE_DATA = (
    struct.Struct("<IBB12s"),
    struct.Struct("<BBB12sffff16s16s16s"),
    struct.Struct("<BB12sQBBBII"),
    struct.Struct("<12s80s50s50s"),
    struct.Struct("<BB50s30s"),
)
PAGE_NAMES = ("overview", "network", "storage", "system", "qrcode")


def crc8(data):
    """Calculate the CRC8 used by the panel firmware."""
    crc = 0
    for value in data:
        for _ in range(8):
            mix = (crc ^ value) & 0x80
            crc = (crc << 1) & 0xFF
            if mix != 0:
                crc ^= 0x4D
            value = (value << 1) & 0xFF
    return crc


def make_frame(kind, sequence, payload):
    """Build a zero-padded 256-byte HID report without a report ID."""
    if kind not in (FRAME_REQUEST, FRAME_RESPONSE):
        raise ValueError("invalid frame type")
    if len(payload) > PAYLOAD_SIZE:
        raise ValueError(f"payload exceeds {PAYLOAD_SIZE} bytes")
    header = HEADER.pack(VERSION, kind, 0, sequence, len(payload), crc8(payload))
    return (header + payload).ljust(FRAME_SIZE, b"\0")


def parse_request(raw):
    """Validate a request and return its sequence and report fields."""
    if len(raw) != FRAME_SIZE:
        raise ValueError(f"report length {len(raw)} != {FRAME_SIZE}")
    version, kind, reserved, sequence, length, checksum = HEADER.unpack_from(raw)
    if version != VERSION:
        raise ValueError(f"protocol version {version} != {VERSION}")
    if kind != FRAME_REQUEST or reserved != 0 or length != REQUEST.size:
        raise ValueError("invalid request header")
    payload = raw[HEADER.size : HEADER.size + length]
    if crc8(payload) != checksum:
        raise ValueError("invalid request CRC8")
    page, voltage, current, cpu_fan, hdd_fan, item_idx = REQUEST.unpack(payload)
    if page >= len(PAGE_DATA):
        raise ValueError(f"unknown page {page}")
    if math.isfinite(voltage) is False or math.isfinite(current) is False:
        raise ValueError("invalid voltage or current")
    if cpu_fan > 100 or hdd_fan > 100:
        raise ValueError("invalid fan percentage")
    return sequence, page, voltage, current, cpu_fan, hdd_fan, item_idx


def make_page_data(page, sample, index):
    """Generate data for the page and item selected with the physical keys."""
    totals = {1: 3, 2: 3, 4: 2}
    if page in totals and index >= totals[page]:
        data = bytearray(PAGE_DATA[page].size)
        data[0] = index
        data[1] = totals[page]
        return bytes(data)
    if page == 0:
        runtimes = (59, 60, 61, 90, 1439, 1440, 1441, 2160)
        return PAGE_DATA[page].pack(
            runtimes[sample % len(runtimes)], 20 + sample % 60, 40 + sample % 30, b"NAS-MOCK"
        )
    if page == 1:
        rates = (128.5, 2048.0, 2097152.0, 2147483648.0)
        connected = index == 2
        return PAGE_DATA[page].pack(
            index,
            totals[page],
            index,
            f"eth{index}".encode(),
            rates[sample % len(rates)],
            4096.0 + sample * 10,
            1024.5 + sample % 500,
            65536.0 + sample * 100,
            f"192.168.1.{100 + index}".encode() if connected else b"0.0.0.0",
            b"255.255.255.0" if connected else b"0.0.0.0",
            b"192.168.1.1" if connected else b"0.0.0.0",
        )
    if page == 2:
        return PAGE_DATA[page].pack(
            index,
            totals[page],
            f"/dev/sd{chr(97 + index)}".encode(),
            4_000_000_000_000,
            (74, 75, 89, 90)[sample % 4],
            index,
            (49, 50, 84, 85)[sample % 4],
            1234 + sample,
            123,
        )
    if page == 3:
        return PAGE_DATA[page].pack(
            b"NAS-MOCK",
            b"Linux mock server",
            b"Intel Core i5 (simulated)",
            b"32 GB DDR4 (simulated)",
        )
    if page == 4:
        links = (b"https://example.com/nas", b"https://github.com/Deadline039/nas-panel")
        return PAGE_DATA[page].pack(index, len(links), links[index], b"v0.1.0(12345678)")
    raise ValueError(f"unknown page {page}")


def make_response(raw, sample):
    """Build a response matching the received request sequence and selection."""
    sequence, page, *_measurements, item_idx = parse_request(raw)
    cpu_temperature = (34, 35, 49, 50, 69, 70, 84, 85)[sample % 8]
    hdd_temperature = (34, 35, 44, 45, 49, 50, 69, 70)[sample % 8]
    payload = RESPONSE.pack(
        RESPONSE_PAGE_DATA, 1, page, cpu_temperature, hdd_temperature, LED_STATE
    ) + make_page_data(page, sample, item_idx)
    return make_frame(FRAME_RESPONSE, sequence, payload)


def make_fan_setting(sequence):
    """Build the raw CPU and HDD fan-curve setting response."""
    payload = RESPONSE.pack(RESPONSE_SETTING, 1, SETTING_FAN_CURVES, 35, 40, LED_STATE)
    payload += FAN_CURVE + FAN_CURVE
    return make_frame(FRAME_RESPONSE, sequence, payload)


def self_check():
    """Check every request and response layout without opening a HID device."""
    expected_sizes = (24, 85, 39, 198, 88)
    for page, name in enumerate(PAGE_NAMES):
        request = make_frame(
            FRAME_REQUEST, 42, REQUEST.pack(page, 12.0, 1.25, 30, 40, 0)
        )
        parsed = parse_request(request)
        if parsed != (42, page, 12.0, 1.25, 30, 40, 0):
            raise AssertionError(f"{name} request layout mismatch")
        response = make_response(request, 7)
        header = HEADER.unpack_from(response)
        if len(response) != FRAME_SIZE or header[1] != FRAME_RESPONSE:
            raise AssertionError(f"{name} response frame mismatch")
        if header[4] != expected_sizes[page]:
            raise AssertionError(f"{name} payload size {header[4]} != {expected_sizes[page]}")
        payload = response[HEADER.size : HEADER.size + header[4]]
        if payload[5] != LED_STATE:
            raise AssertionError("LED state mismatch")
        if crc8(payload) != header[5]:
            raise AssertionError(f"{name} response CRC8 mismatch")
        print(
            f"{name}: request={REQUEST.size} bytes, response={header[4]} bytes, "
            f"frame={len(response)} bytes"
        )
    setting = make_fan_setting(42)
    header = HEADER.unpack_from(setting)
    if header[4] != RESPONSE.size + len(FAN_CURVE) * 2:
        raise AssertionError("fan setting payload size mismatch")
    payload = setting[HEADER.size : HEADER.size + header[4]]
    if crc8(payload) != header[5]:
        raise AssertionError("fan setting CRC8 mismatch")
    print(f"fan setting: response={header[4]} bytes, curves={len(FAN_CURVE)}+{len(FAN_CURVE)} bytes")


def open_device(hid, serial):
    """Find and open exactly one matching panel."""
    devices = hid.enumerate(VID, PID)
    devices = [item for item in devices if serial is None or item.get("serial_number") == serial]
    if len(devices) != 1:
        raise RuntimeError(
            f"found {len(devices)} matching interfaces; use --list or --serial"
        )
    device = hid.device()
    device.open_path(devices[0]["path"])
    return device, devices[0]


def main():
    """List panels, verify layouts, or run the HID mock server."""
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--serial", help="panel serial number")
    parser.add_argument("--list", action="store_true", help="list matching HID devices")
    parser.add_argument("--dry-run", action="store_true", help="check protocol layouts offline")
    parser.add_argument("--count", type=int, default=0, help="exit after this many replies; zero runs continuously")
    parser.add_argument("--delay", type=float, default=0, help="delay each response in seconds")
    args = parser.parse_args()
    if args.count < 0 or math.isfinite(args.delay) is False or args.delay < 0:
        parser.error("--count and --delay must be nonnegative")
    if args.dry_run:
        self_check()
        return 0
    try:
        import hid
    except ImportError:
        print("Install hidapi with: python3 -m pip install hidapi", file=sys.stderr)
        return 1
    if args.list:
        devices = hid.enumerate(VID, PID)
        for info in devices:
            print(
                f"serial={info.get('serial_number')} "
                f"product={info.get('product_string')} path={info['path']!r}"
            )
        if len(devices) == 0:
            print("No 3939:0831 HID device found")
        return 0
    try:
        device, info = open_device(hid, args.serial)
    except (OSError, RuntimeError) as exc:
        print(f"Unable to open panel: {exc}", file=sys.stderr)
        return 1
    try:
        print(
            f"Opened {info.get('serial_number')}; use the panel keys to change pages/items. "
            "Press Ctrl+C to stop.",
            flush=True,
        )
        count = 0
        samples = [0] * len(PAGE_DATA)
        last_notice = time.monotonic()
        while args.count == 0 or count < args.count:
            raw = bytes(device.read(FRAME_SIZE, 1000))
            if len(raw) == 0:
                if time.monotonic() - last_notice >= 5:
                    print("Still waiting for a panel request", flush=True)
                    last_notice = time.monotonic()
                continue
            try:
                sequence, page, voltage, current, cpu_fan, hdd_fan, item_idx = parse_request(raw)
                response = make_response(raw, samples[page])
            except ValueError as exc:
                print(f"Ignoring invalid request: {exc}", file=sys.stderr)
                continue
            if args.delay > 0:
                time.sleep(args.delay)
            written = device.write(b"\0" + response)
            if written != FRAME_SIZE + 1:
                raise OSError(f"incomplete HID write: {written}/{FRAME_SIZE + 1}")
            print(
                f"seq={sequence} page={page}:{PAGE_NAMES[page]} item={item_idx} "
                f"U={voltage:.2f}V I={current:.2f}A "
                f"fans={cpu_fan}%/{hdd_fan}% -> response",
                flush=True,
            )
            count += 1
            samples[page] += 1
            last_notice = time.monotonic()
    except KeyboardInterrupt:
        print("\nStopped")
    except (OSError, RuntimeError) as exc:
        print(f"USB communication failed: {exc}", file=sys.stderr)
        return 1
    finally:
        device.close()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
