/**
 * Copyright (c) 2026, Deadline039
 *
 * SPDX-License-Identifier: MIT
 */

#include "fan_control.h"

#include <FreeRTOS.h>
#include <task.h>

#include <bsp.h>
#include <gd32f30x_fmc.h>
#include <string.h>
#include <usb_data.h>

#define FAN_CONTROL_PERIOD_MS   pdMS_TO_TICKS(1000)
#define FAN_CURVE_CPU           0U
#define FAN_CURVE_HDD           1U

#define FAN_CURVE_FLASH_ADDRESS 0x080FF000U
#define FAN_CURVE_MAGIC         0x46414E43U
#define FAN_CURVE_VERSION       2U
#define FAN_CURVE_STORAGE_WORDS 13U

/* The first 16 entries cover 25 to 100 degrees Celsius in 5 degree steps. */
static uint8_t fan_percent_table[FAN_CURVE_COUNT][FAN_CURVE_POINTS] = {
    { 0U, 0U, 30U, 40U, 50U, 60U, 70U, 80U, 90U, 100U,
      100U, 100U, 100U, 100U, 100U, 100U, 100U, 100U, 100U, 100U },
    { 0U, 0U, 30U, 40U, 50U, 60U, 70U, 80U, 90U, 100U,
      100U, 100U, 100U, 100U, 100U, 100U, 100U, 100U, 100U, 100U }
};

static TaskHandle_t fan_ctrl_task_handle;

/**
 * @brief Calculate a checksum for persisted curve data.
 * @param data Data bytes.
 * @param length Data length.
 * @return Calculated checksum.
 */
static uint32_t fan_curve_checksum(const uint8_t *data, size_t length)
{
    uint32_t checksum = 2166136261U;
    for (size_t index = 0U; index < length; index++) {
        checksum ^= data[index];
        checksum *= 16777619U;
    }
    return checksum;
}

/**
 * @brief Check that every curve entry is a valid PWM percentage.
 * @param curves Raw curve bytes.
 * @param length Curve data length.
 * @return True when the data contains exactly two valid 20-point curves.
 */
static bool fan_curves_valid(const uint8_t *curves, size_t length)
{
    if (curves == NULL || length != FAN_CURVE_BYTES) {
        return false;
    }
    for (size_t index = 0U; index < length; index++) {
        if (curves[index] > 100U) {
            return false;
        }
        if (index % FAN_CURVE_POINTS != 0U &&
            curves[index] < curves[index - 1U]) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Load valid fan curves from the reserved final Flash page.
 * @return True when stored data is valid and loaded.
 */
static bool fan_curves_load(void)
{
    const uint32_t *storage = (const uint32_t *)FAN_CURVE_FLASH_ADDRESS;
    const uint8_t *curves = (const uint8_t *)&storage[2];
    if (storage[0] != FAN_CURVE_MAGIC || storage[1] != FAN_CURVE_VERSION) {
        return false;
    }
    if (fan_curves_valid(curves, FAN_CURVE_BYTES) == false) {
        return false;
    }
    if (storage[FAN_CURVE_STORAGE_WORDS - 1U] !=
        fan_curve_checksum(curves, FAN_CURVE_BYTES)) {
        return false;
    }
    memcpy(fan_percent_table, curves, FAN_CURVE_BYTES);
    return true;
}

/**
 * @brief Write both fan curves to the reserved final Flash page.
 * @param curves Raw CPU curve followed by the raw HDD curve.
 * @return True when erase and programming complete successfully.
 */
static bool fan_curves_store(const uint8_t *curves)
{
    uint32_t storage[FAN_CURVE_STORAGE_WORDS];
    memset(storage, 0xFF, sizeof(storage));
    storage[0] = FAN_CURVE_MAGIC;
    storage[1] = FAN_CURVE_VERSION;
    memcpy(&storage[2], curves, FAN_CURVE_BYTES);
    storage[FAN_CURVE_STORAGE_WORDS - 1U] =
        fan_curve_checksum(curves, FAN_CURVE_BYTES);

    fmc_unlock();
    fmc_flag_clear(FMC_FLAG_BANK1_END);
    fmc_flag_clear(FMC_FLAG_BANK1_WPERR);
    fmc_flag_clear(FMC_FLAG_BANK1_PGERR);
    fmc_state_enum state = fmc_page_erase(FAN_CURVE_FLASH_ADDRESS);
    for (size_t index = 0U;
         index < FAN_CURVE_STORAGE_WORDS && state == FMC_READY; index++) {
        state = fmc_word_program(FAN_CURVE_FLASH_ADDRESS + index * sizeof(uint32_t),
                                 storage[index]);
    }
    fmc_lock();
    return state == FMC_READY;
}

/**
 * @brief Validate, persist, and activate CPU and HDD fan curves.
 * @param curves Raw CPU curve followed by the raw HDD curve.
 * @param length Curve data length in bytes.
 * @return True when the curves are valid and stored successfully.
 */
bool fan_ctrl_set_curves(const uint8_t *curves, size_t length)
{
    if (fan_curves_valid(curves, length) == false) {
        return false;
    }
    if (memcmp(fan_percent_table, curves, FAN_CURVE_BYTES) == 0) {
        return true;
    }
    if (fan_curves_store(curves) == false) {
        return false;
    }
    taskENTER_CRITICAL();
    memcpy(fan_percent_table, curves, FAN_CURVE_BYTES);
    taskEXIT_CRITICAL();
    return true;
}

/**
 * @brief Convert a temperature to a fan PWM percentage using 5 degree steps.
 * @param curve Fan curve lookup table.
 * @param temperature Temperature in degrees Celsius.
 * @return PWM percentage from 0 to 100.
 */
static uint8_t fan_ctrl_percent(const uint8_t *curve, uint8_t temperature)
{
    uint8_t clamped_temperature = temperature;
    if (clamped_temperature < FAN_CURVE_MIN_TEMPERATURE) {
        clamped_temperature = FAN_CURVE_MIN_TEMPERATURE;
    }
    if (clamped_temperature > FAN_CURVE_MAX_TEMPERATURE) {
        clamped_temperature = FAN_CURVE_MAX_TEMPERATURE;
    }
    uint8_t index = (clamped_temperature - FAN_CURVE_MIN_TEMPERATURE) / 5U;
    return curve[index];
}

/**
 * @brief Update PWM outputs from the most recent temperature snapshot.
 * @param args Unused task argument.
 */
__NO_RETURN static void fan_ctrl_task(void *args)
{
    (void)args;
    TickType_t wake_tick = xTaskGetTickCount();
    while (1) {
        fan_cpu_set(fan_ctrl_percent(fan_percent_table[FAN_CURVE_CPU],
                                     g_usb_data_resp.cpu_temperature));
        fan_hdd_set(fan_ctrl_percent(fan_percent_table[FAN_CURVE_HDD],
                                     g_usb_data_resp.hdd_temperature));
        vTaskDelayUntil(&wake_tick, FAN_CONTROL_PERIOD_MS);
    }
}

/**
 * @brief Create the background task that updates local fan PWM outputs.
 */
void fan_ctrl_init(void)
{
    (void)fan_curves_load();
    xTaskCreate(fan_ctrl_task, "fan control", 128, NULL, 3, &fan_ctrl_task_handle);
}
