/**
 * Copyright (c) 2026, Deadline039
 *
 * SPDX-License-Identifier: MIT
 */

#include "bootloader.h"

#include "delay/delay.h"
#include "lcd/lcd.h"

#include <gd32f30x.h>
#include <string.h>

typedef enum {
    UPDATE_WAITING,
    UPDATE_ERASING,
    UPDATE_PROGRAMMING,
    UPDATE_VERIFYING
} update_phase_t;

typedef struct {
    uint32_t size;
    uint32_t crc;
} boot_image_info_t;

static struct {
    bool active;
    uint32_t total;
    uint32_t written;
    uint32_t expected_crc;
    uint32_t progress;
    uint32_t next_animation;
    uint8_t dots;
    update_phase_t phase;
    bool frozen;
} update;

/**
 * @brief Enable access to the backup registers.
 */
static void backup_write_enable(void)
{
    rcu_periph_clock_enable(RCU_PMU);
    rcu_periph_clock_enable(RCU_BKPI);
    pmu_backup_write_enable();
}

/**
 * @brief Calculate CRC32/ISO-HDLC for a memory region.
 * @param previous CRC of the preceding data, or zero for a new calculation.
 * @param data First byte of the region.
 * @param length Number of bytes.
 * @return Calculated CRC32 value.
 */
static uint32_t crc32_extend(uint32_t previous, const uint8_t *data, uint32_t length)
{
    uint32_t crc = previous ^ UINT32_MAX;
    for (uint32_t index = 0U; index < length; ++index) {
        crc ^= data[index];
        for (uint32_t bit = 0U; bit < 8U; ++bit) {
            if ((crc & 1U) != 0U) {
                crc = (crc >> 1U) ^ 0xEDB88320U;
            } else {
                crc >>= 1U;
            }
        }
    }
    return crc ^ UINT32_MAX;
}

/**
 * @brief Validate the application vectors and checksum metadata.
 * @return True when the installed application is bootable.
 */
static bool application_valid(void)
{
    const uint8_t *image = (const uint8_t *)(uintptr_t)BOOT_APP_BASE;
    boot_image_info_t info;
    uint32_t vectors[2];
    memcpy(&info, (const void *)(uintptr_t)BOOT_IMAGE_INFO, sizeof(info));
    memcpy(vectors, image, sizeof(vectors));
    if (info.size < 8U || info.size > BOOT_APP_LIMIT - BOOT_APP_BASE) {
        return false;
    }
    if (vectors[0] <= SRAM_BASE || vectors[0] > SRAM_BASE + 96U * 1024U) {
        return false;
    }
    if ((vectors[0] & 7U) != 0U || (vectors[1] & 1U) == 0U) {
        return false;
    }
    if ((vectors[1] & ~1U) < BOOT_APP_BASE + 8U ||
        (vectors[1] & ~1U) >= BOOT_APP_BASE + info.size) {
        return false;
    }

    return crc32_extend(0U, image, info.size) == info.crc;
}

static uint32_t drawn_progress_width;

/**
 * @brief Draw the status labels at fixed positions.
 */
static void status_draw_labels(void)
{
    lcd_clear(BLACK);
    drawn_progress_width = 0U;
    lcd_show_string(148, 16, 280, 32, 16, "Bootloader mode", WHITE);
    if (update.active == false) {
        lcd_show_string(124, 55, 304, 32, 32, "Waiting", WHITE);
        return;
    }

    if (update.phase == UPDATE_ERASING) {
        lcd_show_string(56, 55, 372, 32, 32, "Erasing:", WHITE);
    } else if (update.phase == UPDATE_PROGRAMMING) {
        lcd_show_string(56, 55, 372, 32, 32, "Programming:", WHITE);
    } else if (update.phase == UPDATE_VERIFYING) {
        lcd_show_string(56, 55, 372, 32, 32, "Verifying:", WHITE);
    }
}

/**
 * @brief Draw the progress number and moving dot indicator.
 */
static void status_draw_dynamic(void)
{
    static int dot_idx = 0;
    const char *dot_str[3] = { ".  ", " . ", "  ." };

    uint32_t percent = 0U;
    if (update.active == true && update.total != 0U) {
        percent = update.progress * 100U / update.total;
    }
    if (percent > 100U) {
        percent = 100U;
    }
    if (update.active == true) {
        lcd_show_num(344, 110, percent, 3, 16, WHITE);
        uint32_t progress_width = 286U * percent / 100U;
        if (progress_width > drawn_progress_width) {
            lcd_fill_region(44U + drawn_progress_width, 112U, 44U + progress_width - 1U,
                            123U, WHITE);
        } else if (progress_width < drawn_progress_width) {
            lcd_fill_region(44U + progress_width, 112U, 44U + drawn_progress_width - 1U,
                            123U, BLACK);
        }
        drawn_progress_width = progress_width;
        lcd_show_string(392, 110, 16, 16, 16, "%", WHITE);
    }

    lcd_show_string(272, 55, 32, 48, 32, dot_str[dot_idx], WHITE);
    dot_idx++;
    dot_idx %= 3;
}

/**
 * @brief Show the waiting layout and its first dot position.
 */
void bootloader_update_show_waiting(void)
{
    update.active = false;
    update.dots = 0U;
    update.next_animation = systick_get();
    status_draw_labels();
    status_draw_dynamic();
}

/**
 * @brief Erase the dedicated metadata page to invalidate the current application.
 * @return True when the metadata page is erased.
 */
static bool image_info_invalidate(void)
{
    fmc_unlock();
    fmc_flag_clear(FMC_FLAG_BANK1_END | FMC_FLAG_BANK1_WPERR | FMC_FLAG_BANK1_PGERR);
    fmc_state_enum result = fmc_page_erase(BOOT_METADATA_PAGE);
    fmc_lock();
    return result == FMC_READY;
}

/**
 * @brief Store application length and checksum in the metadata page.
 * @param size Application length in bytes.
 * @param crc Application CRC32 value.
 * @return True when metadata was written and verified.
 */
static bool image_info_write(uint32_t size, uint32_t crc)
{
    fmc_unlock();
    fmc_flag_clear(FMC_FLAG_BANK1_END | FMC_FLAG_BANK1_WPERR | FMC_FLAG_BANK1_PGERR);
    if (fmc_page_erase(BOOT_METADATA_PAGE) != FMC_READY ||
        fmc_word_program(BOOT_IMAGE_INFO, size) != FMC_READY ||
        fmc_word_program(BOOT_IMAGE_INFO + sizeof(uint32_t), crc) != FMC_READY) {
        fmc_lock();
        return false;
    }
    fmc_lock();

    boot_image_info_t info;
    memcpy(&info, (const void *)(uintptr_t)BOOT_IMAGE_INFO, sizeof(info));
    return info.size == size && info.crc == crc;
}

/**
 * @brief Check whether the device should leave bootloader mode.
 * @return True when no update request is pending and the application is valid.
 */
bool bootloader_should_start_application(void)
{
    backup_write_enable();
    if (bkp_read_data(BKP_DATA_0) == BOOT_REQUEST_MAGIC) {
        return false;
    }
    return application_valid();
}

/**
 * @brief Clear interrupt state and start the installed application.
 */
__attribute__((noreturn)) void bootloader_start_application(void)
{
    uint32_t base = BOOT_APP_BASE;
    __disable_irq();
    SysTick->CTRL = 0U;
    for (uint32_t index = 0U; index < 8U; ++index) {
        NVIC->ICER[index] = UINT32_MAX;
        NVIC->ICPR[index] = UINT32_MAX;
    }
    SCB->VTOR = base;
    __DSB();
    __ISB();
    __set_MSP(*(const uint32_t *)(uintptr_t)base);
    ((void (*)(void))(*(const uint32_t *)(uintptr_t)(base + 4U)))();
    while (1)
        ;
}

/**
 * @brief Reset update progress for a newly enumerated DFU session.
 */
void bootloader_update_reset(void)
{
    memset(&update, 0, sizeof(update));
}

/**
 * @brief Record a successful Flash erase in the application partition.
 * @param address Erased page address.
 * @return True when the address belongs to the application partition.
 */
bool bootloader_update_erase(uint32_t address)
{
    if (address < BOOT_APP_BASE || address >= BOOT_APP_LIMIT) {
        return false;
    }
    if (update.active == false) {
        if (image_info_invalidate() == false) {
            return false;
        }
        update.active = true;
        update.phase = UPDATE_ERASING;
        status_draw_labels();
    }
    update.progress = address - BOOT_APP_BASE;
    status_draw_dynamic();
    return true;
}

/**
 * @brief Record a successful DFU data block.
 * @param data Downloaded block.
 * @param address Flash destination.
 * @param length Number of downloaded bytes.
 * @return True when the complete block is inside the application partition.
 */
bool bootloader_update_write(const uint8_t *data, uint32_t address, uint32_t length)
{
    if (data == NULL || length == 0U) {
        return false;
    }
    if (address < BOOT_APP_BASE || address > BOOT_APP_LIMIT) {
        return false;
    }
    if (length > BOOT_APP_LIMIT - address) {
        return false;
    }
    uint32_t end = address + length - BOOT_APP_BASE;
    if (end > update.written) {
        update.written = end;
    }
    update.active = true;
    if (update.phase != UPDATE_PROGRAMMING) {
        update.phase = UPDATE_PROGRAMMING;
        status_draw_labels();
    }
    update.progress = update.written;
    status_draw_dynamic();
    return true;
}

/**
 * @brief Store host-provided image metadata before application data.
 * @param data Metadata containing image length and CRC32.
 * @param length Metadata length.
 * @return True when the metadata is valid and stored.
 */
bool bootloader_update_set_image_info(const uint8_t *data, uint32_t length)
{
    boot_image_info_t info;
    if (data == NULL || length != sizeof(info)) {
        return false;
    }
    memcpy(&info, data, sizeof(info));
    if (info.size < 8U || info.size > BOOT_APP_LIMIT - BOOT_APP_BASE) {
        return false;
    }
    update.active = true;
    update.total = info.size;
    update.written = 0U;
    update.expected_crc = info.crc;
    update.frozen = false;
    update.phase = UPDATE_ERASING;
    update.progress = 0U;
    status_draw_labels();
    status_draw_dynamic();
    return true;
}

/**
 * @brief Validate the written image and allow bootloader mode to exit.
 * @return True when the image is ready to boot.
 */
bool bootloader_update_finish(void)
{
    if (update.written == 0U || update.written != update.total) {
        update.active = false;
        update.frozen = true;
        lcd_clear(BLACK);
        lcd_show_string(108, 55, 240, 32, 32, "Verify failed", WHITE);
        return false;
    }
    update.phase = UPDATE_VERIFYING;
    update.progress = 0U;
    status_draw_labels();
    uint32_t crc = 0U;
    const uint8_t *image = (const uint8_t *)(uintptr_t)BOOT_APP_BASE;
    for (uint32_t offset = 0U; offset < update.written; offset += 4096U) {
        uint32_t length = update.written - offset;
        if (length > 4096U) {
            length = 4096U;
        }
        crc = crc32_extend(crc, image + offset, length);
        update.progress = offset + length;
        status_draw_dynamic();
    }
    if (crc != update.expected_crc || image_info_write(update.written, crc) == false ||
        application_valid() == false) {
        update.active = false;
        update.frozen = true;
        lcd_clear(BLACK);
        lcd_show_string(108, 55, 240, 32, 32, "Verify failed", WHITE);
        return false;
    }
    backup_write_enable();
    bkp_write_data(BKP_DATA_0, 0U);
    update.active = false;
    lcd_clear(BLACK);
    lcd_show_string(92, 55, 300, 32, 32, "Success, waiting 3 seconds", WHITE);
    delay_ms(3000U);
    return true;
}

/**
 * @brief Stop the update animation after a DFU abort.
 */
void bootloader_update_abort(void)
{
    update.frozen = false;
    update.active = false;
    status_draw_labels();
    status_draw_dynamic();
}

/**
 * @brief Advance the three-dot animation while DFU is active.
 */
void bootloader_update_poll(void)
{
    if (update.frozen == true) {
        return;
    }
    uint32_t now = systick_get();
    if (now - update.next_animation < 250U) {
        return;
    }
    update.next_animation = now;
    update.dots = (uint8_t)((update.dots + 1U) % 3U);
    status_draw_dynamic();
}
