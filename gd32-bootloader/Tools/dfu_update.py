#!/usr/bin/env python3
"""Validate and download a NAS Panel application through dfu-util."""

import argparse
from pathlib import Path
import shutil
import struct
import subprocess
import tempfile
import zlib

APP_BASE = 0x08008000
APP_LIMIT = 0x080FE000
METADATA_TRANSFER = 0x080FE000
DEFAULT_DEVICE = "3939:3927"
USB_VENDOR = 0x3939
USB_PRODUCT = 0x3927


def validate_image(path: Path) -> tuple[bytes, int]:
    """Validate an application image and return its data and CRC32."""
    image = path.read_bytes()
    if len(image) < 8:
        raise ValueError("Image is shorter than the vector table")
    if len(image) > APP_LIMIT - APP_BASE:
        raise ValueError("Image does not fit before the metadata page")
    stack, reset = struct.unpack_from("<2I", image)
    if not 0x20000000 < stack <= 0x20018000 or stack & 7 or reset & 1 == 0:
        raise ValueError("Image does not contain valid application vectors")
    reset_address = reset & ~1
    if reset_address < APP_BASE + 8 or reset_address >= APP_BASE + len(image):
        raise ValueError("Image reset vector is outside the application image")
    crc = zlib.crc32(image)
    print(f"Image: {path}")
    print(f"Size: {len(image)} bytes, CRC32: 0x{crc:08x}")
    return image, crc


def create_dfuse(image: bytes, crc: int) -> bytes:
    """Build a DfuSe image containing metadata first and application data second."""
    metadata = struct.pack("<2I", len(image), crc)
    elements = struct.pack("<2I", METADATA_TRANSFER, len(metadata)) + metadata
    elements += struct.pack("<2I", APP_BASE, len(image)) + image
    target = b"Target" + bytes([0]) + struct.pack("<I", 1) + b"NAS Panel".ljust(255, b"\0")
    target += struct.pack("<2I", len(elements), 2) + elements
    prefix = b"DfuSe" + bytes([1]) + struct.pack("<I", 11 + len(target)) + bytes([1])
    data = prefix + target
    suffix = struct.pack("<4H3sB", 0xFFFF, USB_PRODUCT, USB_VENDOR, 0x011A, b"UFD", 16)
    return data + suffix + struct.pack("<I", zlib.crc32(data + suffix) ^ 0xFFFFFFFF)


def main() -> None:
    """List a DFU device or program one verified image."""
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("image", nargs="?", type=Path, help="APP BIN")
    parser.add_argument("--device", default=DEFAULT_DEVICE, help="USB VID:PID accepted by dfu-util")
    parser.add_argument("--list", action="store_true", help="List matching DFU devices")
    parser.add_argument("--check", action="store_true", help="Validate an image without USB access")
    args = parser.parse_args()

    if args.check:
        if args.image is None:
            raise ValueError("--check requires an image")
        validate_image(args.image)
        return

    executable = shutil.which("dfu-util")
    if executable is None:
        raise RuntimeError("dfu-util is not installed or is not on PATH")
    if args.list or args.image is None:
        subprocess.run([executable, "-d", args.device, "-l"], check=True)
        return

    image, crc = validate_image(args.image)
    print("Erasing: bootloader will erase each application page")
    print("Programming: sending application image")
    print("Verify: finalizing DFU manifest and validating Flash CRC32")
    with tempfile.TemporaryDirectory() as directory:
        package_path = Path(directory) / "image.dfu"
        manifest_path = Path(directory) / "manifest.bin"
        manifest_path.write_bytes(b"")
        package_path.write_bytes(create_dfuse(image, crc))
        command = [executable, "-d", args.device, "-a", "0", "-D", str(package_path)]
        print("Running:", " ".join(command))
        subprocess.run(command, check=True)
        command = [
            executable,
            "-d",
            args.device,
            "-a",
            "0",
            "-s",
            f"0x{APP_BASE:08x}:leave:force",
            "-D",
            str(manifest_path),
        ]
        print("Finalizing:", " ".join(command))
        result = subprocess.run(command, check=False)
        if result.returncode == 0:
            print("Update complete")
            return
        if result.returncode == 74:
            print("Update complete: device reset after successful verification")
            return
        raise subprocess.CalledProcessError(result.returncode, command)


if __name__ == "__main__":
    main()
