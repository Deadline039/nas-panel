/**
 * Copyright (c) 2026, Deadline039
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BOOTLOADER_H
#define BOOTLOADER_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define BOOT_APP_BASE      0x08008000U
#define BOOT_CONFIG_BASE   0x080FF000U
#define BOOT_METADATA_PAGE (BOOT_CONFIG_BASE - 4096U)
#define BOOT_APP_LIMIT     BOOT_METADATA_PAGE
#define BOOT_IMAGE_INFO    (BOOT_CONFIG_BASE - 8U)
#define BOOT_REQUEST_MAGIC 0xB007U

bool bootloader_should_start_application(void);

void bootloader_start_application(void);

void bootloader_update_reset(void);

bool bootloader_update_erase(uint32_t address);

bool bootloader_update_write(const uint8_t *data, uint32_t address, uint32_t length);

bool bootloader_update_set_image_info(const uint8_t *data, uint32_t length);

void bootloader_update_show_waiting(void);

bool bootloader_update_finish(void);

void bootloader_update_abort(void);

void bootloader_update_poll(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* BOOTLOADER_H */
