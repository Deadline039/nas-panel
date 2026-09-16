#!/bin/sh

set -eu

INSTALL_DIR=/opt/nas-panel
CONFIG_DIR=/etc/nas-panel
STATE_DIR=/var/lib/nas-panel
RULE_PATH=/etc/udev/rules.d/70-nas-panel.rules
SERVICE_PATH=/etc/systemd/system/nas-panel.service
SERVICE_NAME=nas-panel.service
UNINSTALL_PATH=/usr/local/sbin/nas-panel-uninstall
PURGE=false

usage() {
    echo "Usage: nas-panel-uninstall [--purge]"
    echo "  --purge  Also remove configuration, energy data, user, and group."
}

case "${1:-}" in
    "")
        ;;
    --purge)
        PURGE=true
        ;;
    -h | --help)
        usage
        exit 0
        ;;
    *)
        usage >&2
        exit 2
        ;;
esac

if [ "$#" -gt 1 ]; then
    usage >&2
    exit 2
fi

if [ "$(id -u)" -ne 0 ]; then
    if command -v sudo >/dev/null 2>&1; then
        exec sudo -- "$0" "$@"
    fi
    echo "Run this uninstaller as root." >&2
    exit 1
fi

if command -v systemctl >/dev/null 2>&1; then
    systemctl disable --now "$SERVICE_NAME" >/dev/null 2>&1 || true
fi

rm -f "$SERVICE_PATH" "$RULE_PATH"
rm -rf "$INSTALL_DIR"

if command -v systemctl >/dev/null 2>&1; then
    systemctl daemon-reload
    systemctl reset-failed "$SERVICE_NAME" >/dev/null 2>&1 || true
fi

if command -v udevadm >/dev/null 2>&1; then
    udevadm control --reload-rules
    udevadm trigger --subsystem-match=hidraw || true
fi

if [ "$PURGE" = true ]; then
    rm -rf "$CONFIG_DIR" "$STATE_DIR"
    if id -u nas-panel >/dev/null 2>&1 && command -v userdel >/dev/null 2>&1; then
        userdel nas-panel
    fi
    if getent group nas-panel >/dev/null 2>&1 && command -v groupdel >/dev/null 2>&1; then
        groupdel nas-panel
    fi
else
    echo "Preserved configuration: $CONFIG_DIR"
    echo "Preserved energy data: $STATE_DIR"
fi

rm -f "$UNINSTALL_PATH"
echo "NAS Panel uninstalled successfully."
