/**
 * Copyright (c) 2026, Deadline039
 *
 * SPDX-License-Identifier: MIT
 */

#include <FreeRTOS.h>
#include <task.h>

#include <bsp.h>

static TaskHandle_t start_task_handle;
static void start_task(void *args);

extern TaskHandle_t usb_task_handle;
void usb_task(void *args);

void ui_init(void);

void rtos_start(void)
{
    xTaskCreate(start_task, "start task", 256, NULL, 1, &start_task_handle);
    vTaskStartScheduler();
}

static void start_task(void *args)
{
    (void)args;

    taskENTER_CRITICAL();
    xTaskCreate(usb_task, "usb task", 256, NULL, 5, &usb_task_handle);
    ui_init();
    taskEXIT_CRITICAL();

    vTaskDelete(start_task_handle);
}
