/*
* Copyright 2026 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct
{
  
	lv_obj_t *screen_overview;
	bool screen_overview_del;
	lv_obj_t *screen_overview_img_NAS_LOGO;
	lv_obj_t *screen_overview_label_nas_name;
	lv_obj_t *screen_overview_img_nas_status;
	lv_obj_t *screen_overview_label_nas_state;
	lv_obj_t *screen_overview_cont_MEM;
	lv_obj_t *screen_overview_label_mem;
	lv_obj_t *screen_overview_label_mem_val;
	lv_obj_t *screen_overview_cont_CPU;
	lv_obj_t *screen_overview_label_cpu;
	lv_obj_t *screen_overview_label_cpu_val;
	lv_obj_t *screen_overview_cont_RUNTIME;
	lv_obj_t *screen_overview_label_runtime;
	lv_obj_t *screen_overview_label_runtime_val;
	lv_obj_t *screen_overview_cont_POWER;
	lv_obj_t *screen_overview_label_POWER_UNIT;
	lv_obj_t *screen_overview_label_power;
	lv_obj_t *screen_overview_label_power_val;
	lv_obj_t *screen_overview_cont_CURRENT;
	lv_obj_t *screen_overview_label_CURRENT_UNIT;
	lv_obj_t *screen_overview_label_current;
	lv_obj_t *screen_overview_label_current_val;
	lv_obj_t *screen_overview_cont_VOLTAGE;
	lv_obj_t *screen_overview_label_VOLTAGE_UNIT;
	lv_obj_t *screen_overview_label_voltage;
	lv_obj_t *screen_overview_label_voltage_val;
	lv_obj_t *screen_overview_label_indicator1;
	lv_obj_t *screen_overview_label_indicator2;
	lv_obj_t *screen_overview_label_indicator3;
	lv_obj_t *screen_overview_label_indicator4;
	lv_obj_t *screen_overview_label_indicator5;
	lv_obj_t *screen_network;
	bool screen_network_del;
	lv_obj_t *screen_network_cont_INFO;
	lv_obj_t *screen_network_label_gateway_val;
	lv_obj_t *screen_network_label_gateway;
	lv_obj_t *screen_network_label_subnet_mask;
	lv_obj_t *screen_network_label_subnet;
	lv_obj_t *screen_network_label_ip_addr;
	lv_obj_t *screen_network_label_ip;
	lv_obj_t *screen_network_cont_SPEED;
	lv_obj_t *screen_network_label_up_total_val;
	lv_obj_t *screen_network_label_up_total_unit;
	lv_obj_t *screen_network_label_up_spd_unit;
	lv_obj_t *screen_network_label_up_spd_val;
	lv_obj_t *screen_network_img_UP_LOGO;
	lv_obj_t *screen_network_label_down_total_val;
	lv_obj_t *screen_network_label_down_total_unit;
	lv_obj_t *screen_network_label_down_spd_unit;
	lv_obj_t *screen_network_label_down_spd_val;
	lv_obj_t *screen_network_img_DOWN_LOGO;
	lv_obj_t *screen_network_cont_ETH_NAME;
	lv_obj_t *screen_network_led_eth_state;
	lv_obj_t *screen_network_label_eth_state;
	lv_obj_t *screen_network_label_eth_name;
	lv_obj_t *screen_network_img_ETH_LOGO;
	lv_obj_t *screen_network_label_eth_idx;
	lv_obj_t *screen_network_label_indicator1;
	lv_obj_t *screen_network_label_indicator2;
	lv_obj_t *screen_network_label_indicator3;
	lv_obj_t *screen_network_label_indicator4;
	lv_obj_t *screen_network_label_indicator5;
	lv_obj_t *screen_storage;
	bool screen_storage_del;
	lv_obj_t *screen_storage_label_indicator1;
	lv_obj_t *screen_storage_label_indicator2;
	lv_obj_t *screen_storage_label_indicator3;
	lv_obj_t *screen_storage_label_indicator4;
	lv_obj_t *screen_storage_label_indicator5;
	lv_obj_t *screen_storage_cont_DISK_OVERVIEW;
	lv_obj_t *screen_storage_arc_usage;
	lv_obj_t *screen_storage_label_dev_path_val;
	lv_obj_t *screen_storage_img_DISK_LOGO;
	lv_obj_t *screen_storage_label_disk_idx;
	lv_obj_t *screen_storage_label_capacity;
	lv_obj_t *screen_storage_label_used;
	lv_obj_t *screen_storage_label_capacity_val;
	lv_obj_t *screen_storage_label_usage_precent;
	lv_obj_t *screen_storage_cont_STATE;
	lv_obj_t *screen_storage_img_USAGE_TIME;
	lv_obj_t *screen_storage_img_STATUS;
	lv_obj_t *screen_storage_img_TEMPERATURE;
	lv_obj_t *screen_storage_img_CYCLES;
	lv_obj_t *screen_storage_label_status;
	lv_obj_t *screen_storage_label_temperature;
	lv_obj_t *screen_storage_label_usage_time;
	lv_obj_t *screen_storage_label_cycles;
	lv_obj_t *screen_sys_info;
	bool screen_sys_info_del;
	lv_obj_t *screen_sys_info_label_indicator1;
	lv_obj_t *screen_sys_info_label_indicator2;
	lv_obj_t *screen_sys_info_label_indicator3;
	lv_obj_t *screen_sys_info_label_indicator4;
	lv_obj_t *screen_sys_info_label_indicator5;
	lv_obj_t *screen_sys_info_cont_INFO;
	lv_obj_t *screen_sys_info_label_name_val;
	lv_obj_t *screen_sys_info_label_name;
	lv_obj_t *screen_sys_info_label_os_val;
	lv_obj_t *screen_sys_info_label_os;
	lv_obj_t *screen_sys_info_label_cpu_val;
	lv_obj_t *screen_sys_info_label_cpu;
	lv_obj_t *screen_sys_info_label_mem_val;
	lv_obj_t *screen_sys_info_label_mem;
	lv_obj_t *screen_sys_info_cont_FAN_TEMP;
	lv_obj_t *screen_sys_info_bar_hdd_fan;
	lv_obj_t *screen_sys_info_label_hdd_fan;
	lv_obj_t *screen_sys_info_label_HDD_FAN;
	lv_obj_t *screen_sys_info_img_HDD_FAN;
	lv_obj_t *screen_sys_info_bar_cpu_fan;
	lv_obj_t *screen_sys_info_label_cpu_fan;
	lv_obj_t *screen_sys_info_label_CPU_FAN;
	lv_obj_t *screen_sys_info_img_CPU_FAN;
	lv_obj_t *screen_sys_info_label_cpu_temp_val;
	lv_obj_t *screen_sys_info_label_CPU_TEMP;
	lv_obj_t *screen_sys_info_img_CPU_TEMP;
	lv_obj_t *screen_about_qrcode;
	bool screen_about_qrcode_del;
	lv_obj_t *screen_about_qrcode_label_indicator1;
	lv_obj_t *screen_about_qrcode_label_indicator2;
	lv_obj_t *screen_about_qrcode_label_indicator3;
	lv_obj_t *screen_about_qrcode_label_indicator4;
	lv_obj_t *screen_about_qrcode_label_indicator5;
	lv_obj_t *screen_about_qrcode_cont_ABOUT;
	lv_obj_t *screen_about_qrcode_label_fw_ver_val;
	lv_obj_t *screen_about_qrcode_label_fw_ver;
	lv_obj_t *screen_about_qrcode_label_build_time_val;
	lv_obj_t *screen_about_qrcode_label_build_time;
	lv_obj_t *screen_about_qrcode_label_upper_ver_val;
	lv_obj_t *screen_about_qrcode_label_upper_ver;
	lv_obj_t *screen_about_qrcode_label_LICENSE_INFO;
	lv_obj_t *screen_about_qrcode_label_LICENSE;
	lv_obj_t *screen_about_qrcode_qrcode_1;
	lv_obj_t *screen_about_qrcode_label_qr_code_info;
	lv_obj_t *screen_about_qrcode_label_qrcode_val;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_animation(void * var, int32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb,
                       uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                       lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);


void init_scr_del_flag(lv_ui *ui);

void setup_ui(lv_ui *ui);

void init_keyboard(lv_ui *ui);

extern lv_ui guider_ui;


void setup_scr_screen_overview(lv_ui *ui);
void setup_scr_screen_network(lv_ui *ui);
void setup_scr_screen_storage(lv_ui *ui);
void setup_scr_screen_sys_info(lv_ui *ui);
void setup_scr_screen_about_qrcode(lv_ui *ui);
LV_IMG_DECLARE(_nas_logo_alpha_82x82);
LV_IMG_DECLARE(_offline_alpha_15x15);
LV_IMG_DECLARE(_upload_alpha_20x35);
LV_IMG_DECLARE(_download_alpha_20x35);
LV_IMG_DECLARE(_network_green_alpha_35x35);
LV_IMG_DECLARE(_hdd_alpha_38x46);
LV_IMG_DECLARE(_time_alpha_20x20);
LV_IMG_DECLARE(_hdd_health_alpha_20x20);
LV_IMG_DECLARE(_temperature_alpha_10x22);
LV_IMG_DECLARE(_start_cycle_alpha_20x20);
LV_IMG_DECLARE(_fan_alpha_26x26);
LV_IMG_DECLARE(_fan_alpha_26x26);
LV_IMG_DECLARE(_temperature_alpha_12x26);

LV_FONT_DECLARE(lv_font_Inter_Regular_16)
LV_FONT_DECLARE(lv_font_Inter_Regular_12)
LV_FONT_DECLARE(lv_font_Inter_Bold_12)
LV_FONT_DECLARE(lv_font_Inter_Bold_26)
LV_FONT_DECLARE(lv_font_Inter_Bold_20)
LV_FONT_DECLARE(lv_font_Inter_Bold_16)
LV_FONT_DECLARE(lv_font_Inter_Bold_14)
LV_FONT_DECLARE(lv_font_Inter_Bold_18)
LV_FONT_DECLARE(lv_font_Inter_Regular_14)


#ifdef __cplusplus
}
#endif
#endif
