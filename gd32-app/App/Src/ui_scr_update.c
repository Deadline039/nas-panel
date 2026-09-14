/**
 * Copyright (c) 2026, Deadline039
 *
 * SPDX-License-Identifier: MIT
 */

#include "ui_scr_update.h"

#include <bsp.h>

#include <lvgl.h>

#include <gui_guider.h>
#include <custom.h>
#include <usb_data.h>

extern lv_ui guider_ui;

#define UI_COLOR_BLUE   0x0093ffU
#define UI_COLOR_GREEN  0x2fda64U
#define UI_COLOR_YELLOW 0xffc107U
#define UI_COLOR_RED    0xff4040U

static uint32_t ui_runtime_value(uint32_t minutes, char *unit);
static double ui_storage_value(double kilobytes, uint8_t *unit);
static uint32_t ui_usage_color(uint8_t percent);
static uint32_t ui_temperature_color(uint8_t temperature);

/**
 * @brief Clear USB values and show that the current page is waiting for data.
 * @param page Current screen identifier.
 */
void update_scr_loading(uint8_t page)
{
    switch (page) {
        case LV_SCREEN_NETWORK:
            lv_label_set_text(guider_ui.screen_network_label_eth_name, "--");
            lv_label_set_text(guider_ui.screen_network_label_eth_state, "GETTING DATA");
            lv_label_set_text(guider_ui.screen_network_label_ip_addr, "--");
            lv_label_set_text(guider_ui.screen_network_label_subnet_mask, "--");
            lv_label_set_text(guider_ui.screen_network_label_gateway_val, "--");
            lv_label_set_text(guider_ui.screen_network_label_up_spd_val, "--");
            lv_label_set_text(guider_ui.screen_network_label_down_spd_val, "--");
            lv_label_set_text(guider_ui.screen_network_label_up_total_val, "--");
            lv_label_set_text(guider_ui.screen_network_label_down_total_val, "--");
            lv_label_set_text(guider_ui.screen_network_label_eth_idx, "GETTING DATA");
            lv_led_set_color(guider_ui.screen_network_led_eth_state, lv_color_hex(UI_COLOR_YELLOW));
            lv_led_on(guider_ui.screen_network_led_eth_state);
            lv_obj_set_style_text_color(guider_ui.screen_network_label_eth_state,
                                        lv_color_hex(UI_COLOR_YELLOW), LV_PART_MAIN);
            break;
        case LV_SCREEN_STORAGE:
            lv_label_set_text(guider_ui.screen_storage_label_disk_idx, "GETTING DATA");
            lv_label_set_text(guider_ui.screen_storage_label_dev_path_val, "--");
            lv_label_set_text(guider_ui.screen_storage_label_capacity_val, "--");
            lv_label_set_text(guider_ui.screen_storage_label_usage_percent, "--");
            lv_label_set_text(guider_ui.screen_storage_label_status, "--");
            lv_label_set_text(guider_ui.screen_storage_label_temperature, "--");
            lv_label_set_text(guider_ui.screen_storage_label_usage_time, "--");
            lv_label_set_text(guider_ui.screen_storage_label_cycles, "--");
            lv_arc_set_value(guider_ui.screen_storage_arc_usage, 0);
            break;
        case LV_SCREEN_SYS_INFO:
            lv_label_set_text(guider_ui.screen_sys_info_label_name_val, "GETTING DATA");
            lv_label_set_text(guider_ui.screen_sys_info_label_os_val, "--");
            lv_label_set_text(guider_ui.screen_sys_info_label_cpu_val, "--");
            lv_label_set_text(guider_ui.screen_sys_info_label_mem_val, "--");
            lv_label_set_text(guider_ui.screen_sys_info_label_cpu_temp_val, "--");
            lv_label_set_text(guider_ui.screen_sys_info_label_cpu_fan, "--");
            lv_label_set_text(guider_ui.screen_sys_info_label_hdd_fan, "--");
            lv_bar_set_value(guider_ui.screen_sys_info_bar_cpu_fan, 0, LV_ANIM_OFF);
            lv_bar_set_value(guider_ui.screen_sys_info_bar_hdd_fan, 0, LV_ANIM_OFF);
            break;
        case LV_SCREEN_ABOUT_QRCODE:
            lv_label_set_text(guider_ui.screen_about_qrcode_label_upper_ver_val, "--");
            lv_label_set_text(guider_ui.screen_about_qrcode_label_qrcode_val, "--");
            lv_label_set_text(guider_ui.screen_about_qrcode_label_qr_code_info, "GETTING DATA");
            lv_obj_add_flag(guider_ui.screen_about_qrcode_qrcode_1, LV_OBJ_FLAG_HIDDEN);
            break;
        default:
            break;
    }
}

/**
 * @brief Refresh local power measurements, NAS availability, and overview statistics.
 */
void update_scr_overview(void)
{
    lv_label_set_text_fmt(guider_ui.screen_overview_label_voltage_val, "%.2f", g_usb_data_report.voltage);
    lv_label_set_text_fmt(guider_ui.screen_overview_label_current_val, "%.2f", g_usb_data_report.current);
    lv_label_set_text_fmt(guider_ui.screen_overview_label_power_val, "%.2f", g_usb_data_report.voltage * g_usb_data_report.current);
    bool pwr_state = pwr_get_state();
    uint32_t color = 0xA4A4A4U;
    if (pwr_state == true) {
        color = UI_COLOR_GREEN;
        lv_label_set_text(guider_ui.screen_overview_label_nas_state, "RUNNING");
    } else {
        lv_label_set_text(guider_ui.screen_overview_label_nas_state, "OFF");
    }
    lv_led_set_color(guider_ui.screen_overview_led_nas_status, lv_color_hex(color));
    lv_led_on(guider_ui.screen_overview_led_nas_status);
    lv_obj_set_style_text_color(guider_ui.screen_overview_label_nas_state, lv_color_hex(color), LV_PART_MAIN);
    if (g_usb_data_resp.valid == 0U || g_usb_data_resp.data == NULL) {
        lv_label_set_text(guider_ui.screen_overview_label_runtime_val, "--");
        lv_label_set_text(guider_ui.screen_overview_label_cpu_val, "--");
        lv_label_set_text(guider_ui.screen_overview_label_mem_val, "--");
        return;
    }
    const usb_data_overview_t *data = g_usb_data_resp.data;
    char unit;
    uint32_t runtime = ui_runtime_value(data->running_time, &unit);
    lv_label_set_text_fmt(guider_ui.screen_overview_label_runtime_val, "%lu%c", (unsigned long)runtime, unit);
    lv_label_set_text_fmt(guider_ui.screen_overview_label_cpu_val, "%u%%", (unsigned)data->cpu_load);
    lv_label_set_text_fmt(guider_ui.screen_overview_label_mem_val, "%u%%", (unsigned)data->mem_load);
}

/**
 * @brief Display a network quantity with matching KB, MB, GB, or TB units.
 * @param value_label Numeric label.
 * @param unit_label Unit label.
 * @param kilobytes Quantity in KB or KB/s.
 * @param rate True for a transfer rate.
 */
static void update_network_quantity(lv_obj_t *value_label, lv_obj_t *unit_label, float kilobytes, bool rate)
{
    const char *const units[] = { "KB", "MB", "GB", "TB" };
    const char *const rates[] = { "KB/s", "MB/s", "GB/s", "TB/s" };
    uint8_t unit;
    double value = ui_storage_value(kilobytes, &unit);
    lv_label_set_text_fmt(value_label, "%.1f", value);
    if (rate == true) {
        lv_label_set_text(unit_label, rates[unit]);
        return;
    }
    lv_label_set_text(unit_label, units[unit]);
}

/**
 * @brief Refresh interface names, addresses, scaled traffic, and availability colors.
 */
void update_scr_network(void)
{
    const usb_data_network_t *network = g_usb_data_resp.data;
    bool ready = network->total != 0U && network->idx == g_usb_data_report.item_idx;
    uint8_t state = NETWORK_DISCONNECTED;
    if (ready == true) {
        state = network->status;
    }
    const char *const states[] = { "DISCONNECTED", "GETTING IP", "CONNECTED" };
    const uint32_t colors[] = { UI_COLOR_RED, UI_COLOR_YELLOW, UI_COLOR_GREEN };
    lv_label_set_text(guider_ui.screen_network_label_eth_state, states[state]);
    lv_led_set_color(guider_ui.screen_network_led_eth_state, lv_color_hex(colors[state]));
    lv_led_on(guider_ui.screen_network_led_eth_state);
    lv_obj_set_style_text_color(guider_ui.screen_network_label_eth_state, lv_color_hex(colors[state]), LV_PART_MAIN);
    if (ready == false) {
        lv_label_set_text(guider_ui.screen_network_label_eth_name, "--");
        lv_label_set_text(guider_ui.screen_network_label_ip_addr, "--");
        lv_label_set_text(guider_ui.screen_network_label_subnet_mask, "--");
        lv_label_set_text(guider_ui.screen_network_label_gateway_val, "--");
        lv_label_set_text(guider_ui.screen_network_label_up_spd_val, "--");
        lv_label_set_text(guider_ui.screen_network_label_down_spd_val, "--");
        lv_label_set_text(guider_ui.screen_network_label_up_total_val, "--");
        lv_label_set_text(guider_ui.screen_network_label_down_total_val, "--");
        lv_label_set_text(guider_ui.screen_network_label_eth_idx, "Waiting for data");
        if (network->total == 0U) {
            lv_label_set_text(guider_ui.screen_network_label_eth_idx, "No interfaces");
        }
        return;
    }
    const usb_data_network_t *data = network;
    lv_label_set_text_fmt(guider_ui.screen_network_label_eth_name, "%.*s", (int)sizeof(data->name), data->name);
    lv_label_set_text_fmt(guider_ui.screen_network_label_ip_addr, "%.*s", (int)sizeof(data->ip_addr), data->ip_addr);
    lv_label_set_text_fmt(guider_ui.screen_network_label_subnet_mask, "%.*s", (int)sizeof(data->netmask), data->netmask);
    lv_label_set_text_fmt(guider_ui.screen_network_label_gateway_val, "%.*s", (int)sizeof(data->gateway), data->gateway);
    unsigned index = 0;
    if (data->total != 0) {
        index = (unsigned)data->idx + 1U;
    }
    lv_label_set_text_fmt(guider_ui.screen_network_label_eth_idx, "Ethernet %u of %u", index, (unsigned)data->total);
    update_network_quantity(guider_ui.screen_network_label_up_spd_val, guider_ui.screen_network_label_up_spd_unit, data->up_rate, true);
    update_network_quantity(guider_ui.screen_network_label_down_spd_val, guider_ui.screen_network_label_down_spd_unit, data->down_rate, true);
    update_network_quantity(guider_ui.screen_network_label_up_total_val, guider_ui.screen_network_label_up_total_unit, data->up_total, false);
    update_network_quantity(guider_ui.screen_network_label_down_total_val, guider_ui.screen_network_label_down_total_unit, data->down_total, false);
}

/**
 * @brief Refresh system information, temperature, and fan percentages.
 */
void update_scr_sys_info(void)
{
    lv_label_set_text_fmt(guider_ui.screen_sys_info_label_cpu_fan, "%u%%", (unsigned)g_usb_data_report.cpu_fan_speed);
    lv_label_set_text_fmt(guider_ui.screen_sys_info_label_hdd_fan, "%u%%", (unsigned)g_usb_data_report.hdd_fan_speed);
    lv_bar_set_value(guider_ui.screen_sys_info_bar_cpu_fan, g_usb_data_report.cpu_fan_speed, LV_ANIM_OFF);
    lv_bar_set_value(guider_ui.screen_sys_info_bar_hdd_fan, g_usb_data_report.hdd_fan_speed, LV_ANIM_OFF);
    const usb_data_sys_info_t *data = g_usb_data_resp.data;
    lv_label_set_text_fmt(guider_ui.screen_sys_info_label_name_val, "%.*s", (int)sizeof(data->name), data->name);
    lv_label_set_text_fmt(guider_ui.screen_sys_info_label_os_val, "%.*s", (int)sizeof(data->os_name), data->os_name);
    lv_label_set_text_fmt(guider_ui.screen_sys_info_label_cpu_val, "%.*s", (int)sizeof(data->cpu_name), data->cpu_name);
    lv_label_set_text_fmt(guider_ui.screen_sys_info_label_mem_val, "%.*s", (int)sizeof(data->mem_name), data->mem_name);
    lv_label_set_text_fmt(guider_ui.screen_sys_info_label_cpu_temp_val, "%u℃", (unsigned)g_usb_data_resp.cpu_temperature);
    lv_obj_set_style_text_color(guider_ui.screen_sys_info_label_cpu_temp_val, lv_color_hex(ui_temperature_color(g_usb_data_resp.cpu_temperature)), LV_PART_MAIN);
}

/**
 * @brief Refresh disk capacity, usage, health, and lifetime statistics.
 */
void update_scr_storage(void)
{
    const usb_data_disk_t *data = g_usb_data_resp.data;
    if (data->total == 0U || data->idx != g_usb_data_report.item_idx) {
        lv_label_set_text(guider_ui.screen_storage_label_disk_idx, "Waiting for data");
        if (data->total == 0U) {
            lv_label_set_text(guider_ui.screen_storage_label_disk_idx, "No disks");
        }
        lv_label_set_text(guider_ui.screen_storage_label_dev_path_val, "--");
        lv_label_set_text(guider_ui.screen_storage_label_capacity_val, "--");
        lv_label_set_text(guider_ui.screen_storage_label_usage_percent, "--");
        lv_label_set_text(guider_ui.screen_storage_label_status, "--");
        lv_label_set_text(guider_ui.screen_storage_label_temperature, "--");
        lv_label_set_text(guider_ui.screen_storage_label_usage_time, "--");
        lv_label_set_text(guider_ui.screen_storage_label_cycles, "--");
        lv_arc_set_value(guider_ui.screen_storage_arc_usage, 0);
        return;
    }
    const char *const status[] = { "Status Good", "Status Warning", "Status Failure" };
    unsigned index = 0;
    if (data->total != 0) {
        index = (unsigned)data->idx + 1U;
    }
    lv_label_set_text_fmt(guider_ui.screen_storage_label_disk_idx, "Disk %u of %u", index, (unsigned)data->total);
    lv_label_set_text_fmt(guider_ui.screen_storage_label_dev_path_val, "%.*s", (int)sizeof(data->path), data->path);
    const char *const units[] = { "KB", "MB", "GB", "TB" };
    uint8_t unit;
    double capacity = ui_storage_value((double)data->capacity / 1024.0, &unit);
    lv_label_set_text_fmt(guider_ui.screen_storage_label_capacity_val, "%.1f%s", capacity, units[unit]);
    lv_label_set_text_fmt(guider_ui.screen_storage_label_usage_percent, "%u%%", (unsigned)data->used);
    lv_arc_set_value(guider_ui.screen_storage_arc_usage, data->used);
    lv_color_t usage_color = lv_color_hex(ui_usage_color(data->used));
    lv_obj_set_style_arc_color(guider_ui.screen_storage_arc_usage, usage_color, LV_PART_INDICATOR);
    lv_obj_set_style_text_color(guider_ui.screen_storage_label_usage_percent, usage_color, LV_PART_MAIN);
    const uint32_t status_colors[] = { UI_COLOR_GREEN, UI_COLOR_YELLOW, UI_COLOR_RED };
    lv_label_set_text(guider_ui.screen_storage_label_status, status[data->status]);
    lv_obj_set_style_text_color(guider_ui.screen_storage_label_status, lv_color_hex(status_colors[data->status]), LV_PART_MAIN);
    lv_label_set_text_fmt(guider_ui.screen_storage_label_temperature, "%u℃", (unsigned)data->temperature);
    lv_obj_set_style_text_color(guider_ui.screen_storage_label_temperature, lv_color_hex(ui_temperature_color(data->temperature)), LV_PART_MAIN);
    lv_label_set_text_fmt(guider_ui.screen_storage_label_usage_time, "%lu hours", (unsigned long)data->time);
    lv_label_set_text_fmt(guider_ui.screen_storage_label_cycles, "%lu cycles", (unsigned long)data->cycles);
}

/**
 * @brief Refresh the server version and QR link with bounded string reads.
 */
void update_scr_about_qrcode(void)
{
    const usb_data_about_qrcode_t *data = g_usb_data_resp.data;
    if (data->total == 0U || data->idx != g_usb_data_report.item_idx) {
        lv_label_set_text(guider_ui.screen_about_qrcode_label_upper_ver_val, "--");
        lv_label_set_text(guider_ui.screen_about_qrcode_label_qrcode_val, "--");
        lv_label_set_text(guider_ui.screen_about_qrcode_label_qr_code_info, "Waiting for data");
        if (data->total == 0U) {
            lv_label_set_text(guider_ui.screen_about_qrcode_label_qr_code_info, "No links");
        }
        lv_obj_add_flag(guider_ui.screen_about_qrcode_qrcode_1, LV_OBJ_FLAG_HIDDEN);
        return;
    }
    lv_obj_clear_flag(guider_ui.screen_about_qrcode_qrcode_1, LV_OBJ_FLAG_HIDDEN);
    lv_label_set_text_fmt(guider_ui.screen_about_qrcode_label_upper_ver_val, "%.*s", (int)sizeof(data->server_version), data->server_version);
    char address[sizeof(data->web_addr) + 1];
    memcpy(address, data->web_addr, sizeof(data->web_addr));
    address[sizeof(data->web_addr)] = '\0';
    if (strcmp(lv_label_get_text(guider_ui.screen_about_qrcode_label_qrcode_val), address) != 0) {
        lv_label_set_text(guider_ui.screen_about_qrcode_label_qrcode_val, address);
        lv_qrcode_update(guider_ui.screen_about_qrcode_qrcode_1, address, strlen(address));
    }
    unsigned index = 0;
    if (data->total != 0) {
        index = (unsigned)data->idx + 1U;
    }
    lv_label_set_text_fmt(guider_ui.screen_about_qrcode_label_qr_code_info, "Link %u of %u", index, (unsigned)data->total);
}

/**
 * @brief Convert runtime minutes to a rounded minute, hour, or day value.
 * @param minutes Runtime in minutes.
 * @param unit Receives the selected unit character.
 * @return Rounded runtime value.
 */
static uint32_t ui_runtime_value(uint32_t minutes, char *unit)
{
    uint32_t divisor = 1;
    *unit = 'm';
    if (minutes > 1440U) {
        divisor = 1440U;
        *unit = 'd';
    } else if (minutes > 60U) {
        divisor = 60U;
        *unit = 'h';
    }
    return (uint32_t)(((uint64_t)minutes + divisor / 2U) / divisor);
}

/**
 * @brief Scale KB to a readable unit and avoid displaying a rounded 1024.
 * @param kilobytes Quantity in KB.
 * @param unit Receives the unit index.
 * @return Scaled value.
 */
static double ui_storage_value(double kilobytes, uint8_t *unit)
{
    *unit = 0;
    while (*unit < 3 && kilobytes >= 1023.95) {
        kilobytes /= 1024.0;
        ++*unit;
    }
    return kilobytes;
}

/**
 * @brief Select blue, yellow, or red for disk usage.
 * @param percent Disk usage percentage.
 * @return RGB color value.
 */
static uint32_t ui_usage_color(uint8_t percent)
{
    if (percent >= 90) {
        return UI_COLOR_RED;
    }
    if (percent >= 75) {
        return UI_COLOR_YELLOW;
    }
    return UI_COLOR_BLUE;
}

/**
 * @brief Select green, yellow, or red for either CPU or disk temperature.
 * @param temperature Temperature in degrees Celsius.
 * @return RGB color value.
 */
static uint32_t ui_temperature_color(uint8_t temperature)
{
    if (temperature >= 85) {
        return UI_COLOR_RED;
    }
    if (temperature >= 50) {
        return UI_COLOR_YELLOW;
    }
    return UI_COLOR_GREEN;
}
