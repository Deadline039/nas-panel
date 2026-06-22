/**
 * Copyright (c) 2026, Deadline039
 *
 * SPDX-License-Identifier: MIT
 */

#include <bsp.h>

#include <FreeRTOS.h>
#include <task.h>

#include "events_init.h"
#include "lv_port_disp.h"
#include "key/key.h"

#include <lvgl.h>

#include <gui_guider.h>
#include <custom.h>
#include <sys/stat.h>

#define PRESS_KEY_DURATION_MS 50

lv_ui guider_ui;

TaskHandle_t lvgl_task_handle;
void lvgl_task(void *args);

TaskHandle_t ui_task_handle;
void ui_task(void *args);

void ui_init(void)
{
    key_init();
    xTaskCreate(lvgl_task, "lvgl task", 512, NULL, 1, &lvgl_task_handle);
}

static void update_scr_overview(void)
{
    static TickType_t last_tick;
    static bool last_pwr_state;
    TickType_t now_tick = xTaskGetTickCount();

    if (now_tick - last_tick > pdMS_TO_TICKS(100)) {
        uint16_t v_raw;
        int16_t i_raw;
        float v, i;
        ina219_read_bus_voltage(p_ina219_handle, &v_raw, &v);
        ina219_read_current(p_ina219_handle, &i_raw, &i);
        i /= 1000.0f;
        v /= 1000.0f;
        lv_label_set_text_fmt(guider_ui.screen_overview_label_voltage_val, "%.2f", v);
        lv_label_set_text_fmt(guider_ui.screen_overview_label_current_val, "%.2f", i);
        lv_label_set_text_fmt(guider_ui.screen_overview_label_power_val, "%.2f", v * i);
        last_tick = now_tick;
    }

    bool pwr_state = pwr_get_state();
    if (last_pwr_state != pwr_state) {
        last_pwr_state = pwr_state;
        if (pwr_state == true) {
            hc595_set_led(2, 0, 1);
        } else {
            hc595_set_led(2, 0, 0);
        }
    }
}

static void update_scr_network(void)
{
}

static void update_scr_sys_info(void)
{
}

static void update_scr_storage(void)
{
}

static void update_scr_about_qrcode(void)
{
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

__NO_RETURN void lvgl_task(void *args)
{
    lv_init();
    vTaskDelay(100);
    lv_port_disp_init();

    setup_ui(&guider_ui);
    events_init(&guider_ui);
    custom_init(&guider_ui);

    /* update power first */
    if (pwr_get_state() == true) {
        hc595_set_led(2, 0, 1);
    } else {
        hc595_set_led(2, 0, 0);
    }

    TickType_t last_tick = xTaskGetTickCount();
    while (1) {
        update_ui();
        lv_timer_handler_run_in_period(5);
        lv_tick_inc(5);
        vTaskDelayUntil(&last_tick, pdMS_TO_TICKS(5));
    }
}
