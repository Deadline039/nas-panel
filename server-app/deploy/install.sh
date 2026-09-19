#!/bin/sh

set -eu

SCRIPT_DIR=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
INSTALL_DIR=/opt/nas-panel
CONFIG_DIR=/etc/nas-panel
RULES_DIR=/etc/udev/rules.d
SERVICE_DIR=/etc/systemd/system
SERVICE_NAME=nas-panel.service
SBIN_DIR=/usr/local/sbin
UNINSTALL_PATH=$SBIN_DIR/nas-panel-uninstall

if [ "$(id -u)" -ne 0 ]; then
    if command -v sudo >/dev/null 2>&1; then
        exec sudo -- "$0" "$@"
    fi
    echo "Run this installer as root." >&2
    exit 1
fi

if ! command -v systemctl >/dev/null 2>&1; then
    echo "systemd is required." >&2
    exit 1
fi

if ! command -v dfu-util >/dev/null 2>&1; then
    echo "Firmware uploads require dfu-util. Install it with your package manager."
fi

for path in \
    "$SCRIPT_DIR/nas-panel-server" \
    "$SCRIPT_DIR/web/dist/index.html" \
    "$SCRIPT_DIR/config.example.json" \
    "$SCRIPT_DIR/uninstall.sh" \
    "$SCRIPT_DIR/deploy/$SERVICE_NAME" \
    "$SCRIPT_DIR/deploy/70-nas-panel.rules"; do
    if [ ! -e "$path" ]; then
        echo "Missing package file: $path" >&2
        exit 1
    fi
done

if ! getent group nas-panel >/dev/null 2>&1; then
    groupadd --system nas-panel
fi

if ! id -u nas-panel >/dev/null 2>&1; then
    NOLOGIN_SHELL=$(command -v nologin || true)
    if [ -z "$NOLOGIN_SHELL" ]; then
        NOLOGIN_SHELL=/usr/sbin/nologin
    fi
    useradd --system --gid nas-panel --home-dir /var/lib/nas-panel \
        --shell "$NOLOGIN_SHELL" nas-panel
fi

systemctl stop "$SERVICE_NAME" >/dev/null 2>&1 || true

install -d -m 0755 "$INSTALL_DIR" "$INSTALL_DIR/web"
install -m 0755 "$SCRIPT_DIR/nas-panel-server" "$INSTALL_DIR/nas-panel-server"
rm -rf "$INSTALL_DIR/web/dist"
install -d -m 0755 "$INSTALL_DIR/web/dist"
cp -R "$SCRIPT_DIR/web/dist/." "$INSTALL_DIR/web/dist/"
chown -R root:root "$INSTALL_DIR"

install -d -m 0755 "$SBIN_DIR"
install -m 0755 "$SCRIPT_DIR/uninstall.sh" "$UNINSTALL_PATH"

install -d -m 0770 -o root -g nas-panel "$CONFIG_DIR"
if [ ! -f "$CONFIG_DIR/config.json" ]; then
    install -m 0660 -o root -g nas-panel \
        "$SCRIPT_DIR/config.example.json" "$CONFIG_DIR/config.json"
fi

install -d -m 0755 "$SERVICE_DIR" "$RULES_DIR"
install -m 0644 "$SCRIPT_DIR/deploy/$SERVICE_NAME" "$SERVICE_DIR/$SERVICE_NAME"
install -m 0644 "$SCRIPT_DIR/deploy/70-nas-panel.rules" \
    "$RULES_DIR/70-nas-panel.rules"

if command -v udevadm >/dev/null 2>&1; then
    udevadm control --reload-rules
    udevadm trigger --subsystem-match=hidraw || true
    udevadm trigger --subsystem-match=usb --attr-match=idVendor=3939 --attr-match=idProduct=3927 || true
fi

systemctl daemon-reload
systemctl enable --now "$SERVICE_NAME"

echo "NAS Panel installed successfully."
echo "Configuration: $CONFIG_DIR/config.json"
echo "Service status: systemctl status $SERVICE_NAME"
echo "Uninstall: $UNINSTALL_PATH"
