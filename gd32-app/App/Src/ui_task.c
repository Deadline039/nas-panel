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

#define LCD_IDLE_TIMEOUT_MS pdMS_TO_TICKS(5U * 60U * 1000U)

typedef struct {
    uint8_t page;
    uint8_t item[LV_SCREEN_RESERVE];
    uint8_t total[LV_SCREEN_RESERVE];
    bool total_known[LV_SCREEN_RESERVE];
    bool enter_last;
    TickType_t last_input_tick;
    bool sleeping;
} ui_state_t;

usb_data_report_t g_usb_data_report;
usb_data_resp_t g_usb_data_resp;

static ui_state_t ui_state;

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

/**
 * @brief Check whether a screen displays a user-selected data item.
 * @param page Screen identifier.
 * @return True for network, storage, and QR code screens.
 */
static bool ui_page_has_items(uint8_t page)
{
    return page == LV_SCREEN_NETWORK || page == LV_SCREEN_STORAGE || page == LV_SCREEN_ABOUT_QRCODE;
}

/**
 * @brief Clear item navigation when USB data is unavailable.
 */
static void ui_clear_items(void)
{
    for (uint8_t page = 0U; page < LV_SCREEN_RESERVE; page++) {
        if (ui_page_has_items(page) == false) {
            continue;
        }
        ui_state.item[page] = 0U;
        ui_state.total[page] = 0U;
        ui_state.total_known[page] = true;
    }
    ui_state.enter_last = false;
}

/**
 * @brief Update a screen item count and clamp its selected index.
 * @param page Screen identifier.
 * @param total Latest item count.
 */
static void ui_set_total(uint8_t page, uint8_t total)
{
    if (page >= LV_SCREEN_RESERVE || ui_page_has_items(page) == false) {
        return;
    }
    ui_state.total_known[page] = true;
    ui_state.total[page] = total;
    if (total == 0U) {
        ui_state.item[page] = 0U;
    } else if (ui_state.item[page] >= total ||
               (ui_state.page == page && ui_state.enter_last == true)) {
        ui_state.item[page] = total - 1U;
    }
    if (ui_state.page == page) {
        ui_state.enter_last = false;
    }
}

/**
 * @brief Move through list items before crossing to the adjacent screen.
 * @param previous True for the up key, false for the down key.
 */
static void ui_move(bool previous)
{
    uint8_t page = ui_state.page;
    if (ui_page_has_items(page) == true && ui_state.total_known[page] == true &&
        ui_state.total[page] != 0U) {
        if (previous == true && ui_state.item[page] > 0U) {
            --ui_state.item[page];
            return;
        }
        if (previous == false && ui_state.item[page] + 1U < ui_state.total[page]) {
            ++ui_state.item[page];
            return;
        }
    }
    if (previous == true) {
        page = (page + LV_SCREEN_RESERVE - 1U) % LV_SCREEN_RESERVE;
    } else {
        page = (page + 1U) % LV_SCREEN_RESERVE;
    }
    ui_state.page = page;
    ui_state.item[page] = 0U;
    ui_state.enter_last = false;
    if (previous == true && ui_page_has_items(page) == true) {
        if (ui_state.total_known[page] == false) {
            ui_state.enter_last = true;
        } else if (ui_state.total[page] != 0U) {
            ui_state.item[page] = ui_state.total[page] - 1U;
        }
    }
}

/**
 * @brief Update item counts from the latest page response.
 * @param response Latest NAS response.
 */
static void ui_update_totals(const usb_data_resp_t *response)
{
    if (response->valid == 0U || response->type != 0U || response->data == NULL) {
        return;
    }
    switch (ui_state.page) {
        case LV_SCREEN_NETWORK:
            ui_set_total(LV_SCREEN_NETWORK, ((const usb_data_network_t *)response->data)->total);
            break;
        case LV_SCREEN_STORAGE:
            ui_set_total(LV_SCREEN_STORAGE, ((const usb_data_disk_t *)response->data)->total);
            break;
        case LV_SCREEN_ABOUT_QRCODE:
            ui_set_total(LV_SCREEN_ABOUT_QRCODE, ((const usb_data_about_qrcode_t *)response->data)->total);
            break;
        default:
            break;
    }
}

/**
 * @brief Refresh the selected screen from the latest USB snapshot.
 */
static void update_ui(void)
{
    static TickType_t last_refresh;
    uint8_t old_page = ui_state.page;
    uint8_t old_item = ui_state.item[old_page];
    TickType_t now = xTaskGetTickCount();

    if (usb_data_is_available() == false) {
        ui_clear_items();
        taskENTER_CRITICAL();
        g_usb_data_resp.valid = 0U;
        taskEXIT_CRITICAL();
    } else {
        ui_update_totals(&g_usb_data_resp);
    }

    bool down = key_down_get();
    bool up = key_up_get();

    if (down == true || up == true) {
        bool was_sleeping = ui_state.sleeping;
        ui_state.last_input_tick = now;
        ui_state.sleeping = false;
        if (was_sleeping == true) {
            lcd_backlight_ctrl(1);
        } else {
            ui_move(up);
        }
    } else if (now - ui_state.last_input_tick >= LCD_IDLE_TIMEOUT_MS &&
               ui_state.sleeping == false) {
        ui_state.sleeping = true;
        lcd_backlight_ctrl(0);
    }

    uint8_t page = ui_state.page;
    uint8_t item = ui_state.item[page];
    bool changed = page != old_page || item != old_item;
    if (page != old_page) {
        lv_ui_change_screen((lv_ui_screen_t)old_page, (lv_ui_screen_t)page);
    }
    taskENTER_CRITICAL();
    g_usb_data_report.page = page;
    g_usb_data_report.item_idx = item;
    if (changed == true) {
        g_usb_data_resp.valid = 0U;
    }
    taskEXIT_CRITICAL();

    if (changed == false && now - last_refresh < pdMS_TO_TICKS(100U)) {
        return;
    }
    last_refresh = now;

    if (page != LV_SCREEN_OVERVIEW && page != LV_SCREEN_ABOUT_QRCODE &&
        g_usb_data_resp.valid == 0U) {
        update_scr_loading(page);
        return;
    }

    switch (page) {
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
    ui_state.last_input_tick = xTaskGetTickCount();

    TickType_t last_tick = xTaskGetTickCount();
    while (1) {
        update_ui();
        lv_timer_handler_run_in_period(5);
        lv_tick_inc(5);
        vTaskDelayUntil(&last_tick, pdMS_TO_TICKS(5));
    }
}
