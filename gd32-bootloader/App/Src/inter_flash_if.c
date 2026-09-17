/**
 * Copyright (c) 2026, Deadline039
 *
 * SPDX-License-Identifier: MIT
 */

#include "inter_flash_if.h"

#include "bootloader.h"

#include <gd32f30x.h>
#include <string.h>

static uint8_t flash_init(void);
static uint8_t flash_deinit(void);
static uint8_t flash_erase(uint32_t address);
static uint8_t flash_write(uint8_t *data, uint32_t address, uint32_t length);
static uint8_t *flash_read(uint8_t *data, uint32_t address, uint32_t length);
static uint8_t flash_check_address(uint32_t address);
static uint8_t erased_pages[46];

dfu_mem_prop dfu_inter_flash_cb = {
    (const uint8_t *)INTER_FLASH_IF_STR,
    flash_init,
    flash_deinit,
    flash_erase,
    flash_write,
    flash_read,
    flash_check_address,
    60U,
    80U
};

/**
 * @brief Clear Flash operation flags.
 */
static void flash_clear_flags(void)
{
    fmc_flag_clear(FMC_FLAG_BANK0_END | FMC_FLAG_BANK0_WPERR | FMC_FLAG_BANK0_PGERR);
    fmc_flag_clear(FMC_FLAG_BANK1_END | FMC_FLAG_BANK1_WPERR | FMC_FLAG_BANK1_PGERR);
}

/**
 * @brief Get the page index within the application partition.
 * @param address Address in the target page.
 * @return Page index.
 */
static uint32_t flash_page_index(uint32_t address)
{
    if (address < 0x08080000U) {
        return (address - BOOT_APP_BASE) / 2048U;
    }
    return 240U + (address - 0x08080000U) / 4096U;
}

/**
 * @brief Get the aligned address of a target page.
 * @param address Address in the target page.
 * @return Page base address.
 */
static uint32_t flash_page_base(uint32_t address)
{
    if (address < 0x08080000U) {
        return address & ~(2048U - 1U);
    }
    return address & ~(4096U - 1U);
}

/**
 * @brief Check whether a page has been erased during this DFU session.
 * @param page Page index.
 * @return True when the page is erased.
 */
static bool flash_page_is_erased(uint32_t page)
{
    return (erased_pages[page / 8U] & (1U << (page % 8U))) != 0U;
}

/**
 * @brief Mark a page erased during this DFU session.
 * @param page Page index.
 */
static void flash_page_set_erased(uint32_t page)
{
    erased_pages[page / 8U] |= 1U << (page % 8U);
}

/**
 * @brief Erase one target page and record it in the DFU session map.
 * @param address Page address.
 * @return MEM_OK on success, otherwise MEM_FAIL.
 */
static uint8_t flash_erase_page(uint32_t address)
{
    fmc_unlock();
    flash_clear_flags();
    fmc_state_enum result = fmc_page_erase(address);
    fmc_lock();
    if (result != FMC_READY || bootloader_update_erase(address) == false) {
        return MEM_FAIL;
    }
    flash_page_set_erased(flash_page_index(address));
    return MEM_OK;
}

/**
 * @brief Initialize the internal Flash DFU target.
 * @return MEM_OK.
 */
static uint8_t flash_init(void)
{
    memset(erased_pages, 0, sizeof(erased_pages));
    return MEM_OK;
}

/**
 * @brief Deinitialize the internal Flash DFU target.
 * @return MEM_OK.
 */
static uint8_t flash_deinit(void)
{
    fmc_lock();
    return MEM_OK;
}

/**
 * @brief Erase one application Flash page.
 * @param address Page address.
 * @return MEM_OK on success, otherwise MEM_FAIL.
 */
static uint8_t flash_erase(uint32_t address)
{
    if (address >= BOOT_METADATA_PAGE && address < BOOT_CONFIG_BASE) {
        return MEM_OK;
    }
    uint32_t page_size = 2048U;
    if (address >= 0x08080000U) {
        page_size = 4096U;
    }
    if (flash_check_address(address) == MEM_FAIL || address % page_size != 0U) {
        return MEM_FAIL;
    }
    return flash_erase_page(address);
}

/**
 * @brief Program one DFU data block and verify every Flash word.
 * @param data Data block.
 * @param address Destination address.
 * @param length Number of bytes.
 * @return MEM_OK on success, otherwise MEM_FAIL.
 */
static uint8_t flash_write(uint8_t *data, uint32_t address, uint32_t length)
{
    if (address == BOOT_METADATA_PAGE && length == 8U) {
        return bootloader_update_set_image_info(data, length) == true ? MEM_OK : MEM_FAIL;
    }
    if (data == NULL || length == 0U || flash_check_address(address) == MEM_FAIL ||
        length > BOOT_APP_LIMIT - address) {
        return MEM_FAIL;
    }
    uint32_t page = flash_page_base(address);
    uint32_t end = address + length;
    while (page < end) {
        uint32_t page_index = flash_page_index(page);
        if (flash_page_is_erased(page_index) == false && flash_erase_page(page) == MEM_FAIL) {
            return MEM_FAIL;
        }
        page += (page < 0x08080000U) ? 2048U : 4096U;
    }
    fmc_unlock();
    flash_clear_flags();
    for (uint32_t offset = 0U; offset < length; offset += 4U) {
        uint32_t word = UINT32_MAX;
        uint32_t count = length - offset;
        if (count > 4U) {
            count = 4U;
        }
        memcpy(&word, data + offset, count);
        if (fmc_word_program(address + offset, word) != FMC_READY ||
            *(const volatile uint32_t *)(uintptr_t)(address + offset) != word) {
            fmc_lock();
            return MEM_FAIL;
        }
    }
    fmc_lock();
    if (bootloader_update_write(data, address, length) == false) {
        return MEM_FAIL;
    }
    return MEM_OK;
}

/**
 * @brief Return the mapped Flash address for a DFU upload request.
 * @param data Unused transfer buffer.
 * @param address Source address.
 * @param length Unused transfer length.
 * @return Mapped Flash pointer.
 */
static uint8_t *flash_read(uint8_t *data, uint32_t address, uint32_t length)
{
    (void)data;
    (void)length;
    return (uint8_t *)(uintptr_t)address;
}

/**
 * @brief Check whether an address belongs to the application partition.
 * @param address Flash address.
 * @return MEM_OK when writable, otherwise MEM_FAIL.
 */
static uint8_t flash_check_address(uint32_t address)
{
    if (address >= BOOT_APP_BASE && address < BOOT_APP_LIMIT) {
        return MEM_OK;
    }
    return MEM_FAIL;
}
