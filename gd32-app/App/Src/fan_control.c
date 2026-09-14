#include "fan_control.h"

#include <FreeRTOS.h>
#include <task.h>

#include <bsp.h>
#include <usb_data.h>

#define FAN_CONTROL_PERIOD_MS pdMS_TO_TICKS(1000)

/* Each entry applies from its index multiplied by 5 degrees Celsius. */
static const uint8_t fan_percent_table[15] = {
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 30U,
    40U, 50U, 60U, 70U, 80U, 90U, 100U
};

static TaskHandle_t fan_ctrl_task_handle;

/**
 * @brief Convert a temperature to a fan PWM percentage using 5 degree steps.
 * @param temperature Temperature in degrees Celsius.
 * @return PWM percentage from 0 to 100.
 */
uint8_t fan_ctrl_percent(uint8_t temperature)
{
    uint8_t index = temperature / 5U;
    if (index >= sizeof(fan_percent_table)) {
        index = sizeof(fan_percent_table) - 1U;
    }
    return fan_percent_table[index];
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
        vTaskDelayUntil(&wake_tick, FAN_CONTROL_PERIOD_MS);
    }
}

/**
 * @brief Create the background task that updates local fan PWM outputs.
 */
void fan_ctrl_init(void)
{
    xTaskCreate(fan_ctrl_task, "fan control", 128, NULL, 3, &fan_ctrl_task_handle);
}
