/**
 * Copyright (c) 2026, Deadline039
 *
 * SPDX-License-Identifier: MIT
 */

#include <bsp.h>

#include <FreeRTOS.h>
#include <task.h>
#include <string.h>

#include <events_init.h>
#include <lv_port_disp.h>

#include <custom.h>
#include <usb_data.h>
#include <ui_scr_update.h>

#define LCD_IDLE_TIMEOUT_MS (5U * 60U * 1000U)

lv_ui guider_ui;

TaskHandle_t lvgl_task_handle;
void lvgl_task(void *args);

/**
 * @brief Initialize the keys and create the UI task.
 */
void ui_init(void)
{
    key_init();
    xTaskCreate(lvgl_task, "lvgl task", 512, NULL, 1, &lvgl_task_handle);
}

static void update_ui(void)
{
    static int current_scr;
    static int new_scr;

    if (key_down_get()) {
        new_scr = current_scr + 1;
    }
    if (key_up_get()) {
        new_scr = current_scr - 1;
    }

    if (new_scr != current_scr) {
        if (new_scr >= LV_SCREEN_RESERVE) {
            new_scr = LV_SCREEN_OVERVIEW;
        } else if (new_scr < 0) {
            new_scr = LV_SCREEN_ABOUT_QRCODE;
        }
        lv_ui_change_screen(current_scr, new_scr);
        current_scr = new_scr;
    }

    switch (current_scr) {
        case LV_SCREEN_OVERVIEW:
            update_scr_overview();
            break;
        case LV_SCREEN_NETWORK:
            update_scr_network();
            break;
        case LV_SCREEN_SYS_INFO:
            update_scr_sys_info();
            break;
        case LV_SCREEN_STORAGE:
            update_scr_storage();
            break;
        case LV_SCREEN_ABOUT_QRCODE:
            update_scr_about_qrcode();
            break;
        default:
            break;
    }
}

/**
 * @brief Initialize LVGL and handle UI updates and rendering in the same task.
 * @param args Unused task argument.
 */
__NO_RETURN void lvgl_task(void *args)
{
    (void)args;
    lv_init();
    vTaskDelay(100);
    lv_port_disp_init();

    setup_ui(&guider_ui);
    events_init(&guider_ui);
    custom_init(&guider_ui);

    TickType_t last_tick = xTaskGetTickCount();
    while (1) {
        update_ui();
        lv_timer_handler_run_in_period(5);
        lv_tick_inc(5);
        vTaskDelayUntil(&last_tick, pdMS_TO_TICKS(5));
    }
}
