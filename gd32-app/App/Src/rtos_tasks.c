/**
 * Copyright (c) 2026, Deadline039
 *
 * SPDX-License-Identifier: MIT
 */

#include <FreeRTOS.h>
#include <task.h>

#include <bsp.h>
#include "fan_control.h"

static TaskHandle_t start_task_handle;
static void start_task(void *args);

extern TaskHandle_t usb_task_handle;
void usb_task(void *args);

void ui_init(void);

/**
 * @brief Create the startup task and start the scheduler.
 */
void rtos_start(void)
{
    xTaskCreate(start_task, "start task", 256, NULL, 1, &start_task_handle);
    vTaskStartScheduler();
}

/**
 * @brief Create USB and UI tasks, then delete the startup task.
 * @param args Unused task argument.
 */
static void start_task(void *args)
{
    (void)args;

    taskENTER_CRITICAL();
    xTaskCreate(usb_task, "usb task", 256, NULL, 5, &usb_task_handle);
    fan_ctrl_init();
    ui_init();
    taskEXIT_CRITICAL();

    vTaskDelete(start_task_handle);
}
