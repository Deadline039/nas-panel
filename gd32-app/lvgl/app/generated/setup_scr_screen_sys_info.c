/*
* Copyright 2026 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



void setup_scr_screen_sys_info(lv_ui *ui)
{
    //Write codes screen_sys_info
    ui->screen_sys_info = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_sys_info, 428, 142);
    lv_obj_set_scrollbar_mode(ui->screen_sys_info, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_sys_info, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_sys_info, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_sys_info, lv_color_hex(0x090607), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_sys_info, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sys_info_label_indicator1
    ui->screen_sys_info_label_indicator1 = lv_label_create(ui->screen_sys_info);
    lv_label_set_text(ui->screen_sys_info_label_indicator1, "");
    lv_label_set_long_mode(ui->screen_sys_info_label_indicator1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_sys_info_label_indicator1, 418, 42);
    lv_obj_set_size(ui->screen_sys_info_label_indicator1, 6, 6);

    //Write style for screen_sys_info_label_indicator1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_sys_info_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sys_info_label_indicator1, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_sys_info_label_indicator1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_sys_info_label_indicator1, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_sys_info_label_indicator1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_sys_info_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_sys_info_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_sys_info_label_indicator1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_sys_info_label_indicator1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_sys_info_label_indicator1, lv_color_hex(0xbcbcbc), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_sys_info_label_indicator1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_sys_info_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_sys_info_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_sys_info_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_sys_info_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sys_info_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sys_info_label_indicator2
    ui->screen_sys_info_label_indicator2 = lv_label_create(ui->screen_sys_info);
    lv_label_set_text(ui->screen_sys_info_label_indicator2, "");
    lv_label_set_long_mode(ui->screen_sys_info_label_indicator2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_sys_info_label_indicator2, 418, 54);
    lv_obj_set_size(ui->screen_sys_info_label_indicator2, 6, 6);

    //Write style for screen_sys_info_label_indicator2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_sys_info_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sys_info_label_indicator2, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_sys_info_label_indicator2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_sys_info_label_indicator2, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_sys_info_label_indicator2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_sys_info_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_sys_info_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_sys_info_label_indicator2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_sys_info_label_indicator2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_sys_info_label_indicator2, lv_color_hex(0xbcbcbc), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_sys_info_label_indicator2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_sys_info_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_sys_info_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_sys_info_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_sys_info_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sys_info_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sys_info_label_indicator3
    ui->screen_sys_info_label_indicator3 = lv_label_create(ui->screen_sys_info);
    lv_label_set_text(ui->screen_sys_info_label_indicator3, "");
    lv_label_set_long_mode(ui->screen_sys_info_label_indicator3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_sys_info_label_indicator3, 418, 66);
    lv_obj_set_size(ui->screen_sys_info_label_indicator3, 6, 6);

    //Write style for screen_sys_info_label_indicator3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_sys_info_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sys_info_label_indicator3, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_sys_info_label_indicator3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_sys_info_label_indicator3, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_sys_info_label_indicator3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_sys_info_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_sys_info_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_sys_info_label_indicator3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_sys_info_label_indicator3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_sys_info_label_indicator3, lv_color_hex(0xbcbcbc), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_sys_info_label_indicator3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_sys_info_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_sys_info_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_sys_info_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_sys_info_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sys_info_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sys_info_label_indicator4
    ui->screen_sys_info_label_indicator4 = lv_label_create(ui->screen_sys_info);
    lv_label_set_text(ui->screen_sys_info_label_indicator4, "");
    lv_label_set_long_mode(ui->screen_sys_info_label_indicator4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_sys_info_label_indicator4, 416, 78);
    lv_obj_set_size(ui->screen_sys_info_label_indicator4, 10, 10);

    //Write style for screen_sys_info_label_indicator4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_sys_info_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sys_info_label_indicator4, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_sys_info_label_indicator4, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_sys_info_label_indicator4, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_sys_info_label_indicator4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_sys_info_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_sys_info_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_sys_info_label_indicator4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_sys_info_label_indicator4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_sys_info_label_indicator4, lv_color_hex(0x51a8f9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_sys_info_label_indicator4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_sys_info_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_sys_info_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_sys_info_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_sys_info_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sys_info_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sys_info_label_indicator5
    ui->screen_sys_info_label_indicator5 = lv_label_create(ui->screen_sys_info);
    lv_label_set_text(ui->screen_sys_info_label_indicator5, "");
    lv_label_set_long_mode(ui->screen_sys_info_label_indicator5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_sys_info_label_indicator5, 418, 94);
    lv_obj_set_size(ui->screen_sys_info_label_indicator5, 6, 6);

    //Write style for screen_sys_info_label_indicator5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_sys_info_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sys_info_label_indicator5, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_sys_info_label_indicator5, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_sys_info_label_indicator5, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_sys_info_label_indicator5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_sys_info_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_sys_info_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_sys_info_label_indicator5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_sys_info_label_indicator5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_sys_info_label_indicator5, lv_color_hex(0xbcbcbc), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_sys_info_label_indicator5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_sys_info_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_sys_info_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_sys_info_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_sys_info_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sys_info_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sys_info_cont_INFO
    ui->screen_sys_info_cont_INFO = lv_obj_create(ui->screen_sys_info);
    lv_obj_set_pos(ui->screen_sys_info_cont_INFO, 8, 7);
    lv_obj_set_size(ui->screen_sys_info_cont_INFO, 210, 126);
    lv_obj_set_scrollbar_mode(ui->screen_sys_info_cont_INFO, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_sys_info_cont_INFO, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_sys_info_cont_INFO, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_sys_info_cont_INFO, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_sys_info_cont_INFO, lv_color_hex(0xC9C9c9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_sys_info_cont_INFO, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sys_info_cont_INFO, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_sys_info_cont_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_sys_info_cont_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_sys_info_cont_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_sys_info_cont_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_sys_info_cont_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sys_info_cont_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sys_info_label_name_val
    ui->screen_sys_info_label_name_val = lv_label_create(ui->screen_sys_info_cont_INFO);
    lv_label_set_text(ui->screen_sys_info_label_name_val, "NAS NAME");
    lv_label_set_long_mode(ui->screen_sys_info_label_name_val, LV_LABEL_LONG_SCROLL);
    lv_obj_set_pos(ui->screen_sys_info_label_name_val, 72, 12);
    lv_obj_set_size(ui->screen_sys_info_label_name_val, 130, 17);

    //Write style for screen_sys_info_label_name_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_sys_info_label_name_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sys_info_label_name_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_sys_info_label_name_val, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_sys_info_label_name_val, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_sys_info_label_name_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_sys_info_label_name_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_sys_info_label_name_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_sys_info_label_name_val, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_sys_info_label_name_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_sys_info_label_name_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_sys_info_label_name_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_sys_info_label_name_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_sys_info_label_name_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sys_info_label_name_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sys_info_label_name
    ui->screen_sys_info_label_name = lv_label_create(ui->screen_sys_info_cont_INFO);
    lv_label_set_text(ui->screen_sys_info_label_name, "Name");
    lv_label_set_long_mode(ui->screen_sys_info_label_name, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_sys_info_label_name, 3, 13);
    lv_obj_set_size(ui->screen_sys_info_label_name, 60, 16);

    //Write style for screen_sys_info_label_name, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_sys_info_label_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sys_info_label_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_sys_info_label_name, lv_color_hex(0x717171), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_sys_info_label_name, &lv_font_Inter_Regular_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_sys_info_label_name, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_sys_info_label_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_sys_info_label_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_sys_info_label_name, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_sys_info_label_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_sys_info_label_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_sys_info_label_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_sys_info_label_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_sys_info_label_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sys_info_label_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sys_info_label_os_val
    ui->screen_sys_info_label_os_val = lv_label_create(ui->screen_sys_info_cont_INFO);
    lv_label_set_text(ui->screen_sys_info_label_os_val, "Ubuntu 24.04.4 LTS (GNU/Linux 6.8.0-124-generic x86_64)");
    lv_label_set_long_mode(ui->screen_sys_info_label_os_val, LV_LABEL_LONG_SCROLL);
    lv_obj_set_pos(ui->screen_sys_info_label_os_val, 72, 40);
    lv_obj_set_size(ui->screen_sys_info_label_os_val, 130, 17);

    //Write style for screen_sys_info_label_os_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_sys_info_label_os_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sys_info_label_os_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_sys_info_label_os_val, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_sys_info_label_os_val, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_sys_info_label_os_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_sys_info_label_os_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_sys_info_label_os_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_sys_info_label_os_val, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_sys_info_label_os_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_sys_info_label_os_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_sys_info_label_os_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_sys_info_label_os_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_sys_info_label_os_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sys_info_label_os_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sys_info_label_os
    ui->screen_sys_info_label_os = lv_label_create(ui->screen_sys_info_cont_INFO);
    lv_label_set_text(ui->screen_sys_info_label_os, "OS");
    lv_label_set_long_mode(ui->screen_sys_info_label_os, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_sys_info_label_os, 4, 41);
    lv_obj_set_size(ui->screen_sys_info_label_os, 60, 16);

    //Write style for screen_sys_info_label_os, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_sys_info_label_os, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sys_info_label_os, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_sys_info_label_os, lv_color_hex(0x717171), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_sys_info_label_os, &lv_font_Inter_Regular_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_sys_info_label_os, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_sys_info_label_os, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_sys_info_label_os, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_sys_info_label_os, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_sys_info_label_os, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_sys_info_label_os, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_sys_info_label_os, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_sys_info_label_os, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_sys_info_label_os, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sys_info_label_os, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sys_info_label_cpu_val
    ui->screen_sys_info_label_cpu_val = lv_label_create(ui->screen_sys_info_cont_INFO);
    lv_label_set_text(ui->screen_sys_info_label_cpu_val, "Intel J1900@1.99GHz");
    lv_label_set_long_mode(ui->screen_sys_info_label_cpu_val, LV_LABEL_LONG_SCROLL);
    lv_obj_set_pos(ui->screen_sys_info_label_cpu_val, 72, 70);
    lv_obj_set_size(ui->screen_sys_info_label_cpu_val, 130, 17);

    //Write style for screen_sys_info_label_cpu_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_sys_info_label_cpu_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sys_info_label_cpu_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_sys_info_label_cpu_val, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_sys_info_label_cpu_val, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_sys_info_label_cpu_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_sys_info_label_cpu_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_sys_info_label_cpu_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_sys_info_label_cpu_val, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_sys_info_label_cpu_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_sys_info_label_cpu_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_sys_info_label_cpu_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_sys_info_label_cpu_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_sys_info_label_cpu_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sys_info_label_cpu_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sys_info_label_cpu
    ui->screen_sys_info_label_cpu = lv_label_create(ui->screen_sys_info_cont_INFO);
    lv_label_set_text(ui->screen_sys_info_label_cpu, "CPU");
    lv_label_set_long_mode(ui->screen_sys_info_label_cpu, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_sys_info_label_cpu, 4, 69);
    lv_obj_set_size(ui->screen_sys_info_label_cpu, 60, 16);

    //Write style for screen_sys_info_label_cpu, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_sys_info_label_cpu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sys_info_label_cpu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_sys_info_label_cpu, lv_color_hex(0x717171), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_sys_info_label_cpu, &lv_font_Inter_Regular_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_sys_info_label_cpu, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_sys_info_label_cpu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_sys_info_label_cpu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_sys_info_label_cpu, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_sys_info_label_cpu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_sys_info_label_cpu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_sys_info_label_cpu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_sys_info_label_cpu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_sys_info_label_cpu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sys_info_label_cpu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sys_info_label_mem_val
    ui->screen_sys_info_label_mem_val = lv_label_create(ui->screen_sys_info_cont_INFO);
    lv_label_set_text(ui->screen_sys_info_label_mem_val, "8G DDR3@1600MHz");
    lv_label_set_long_mode(ui->screen_sys_info_label_mem_val, LV_LABEL_LONG_SCROLL);
    lv_obj_set_pos(ui->screen_sys_info_label_mem_val, 72, 96);
    lv_obj_set_size(ui->screen_sys_info_label_mem_val, 130, 17);

    //Write style for screen_sys_info_label_mem_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_sys_info_label_mem_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sys_info_label_mem_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_sys_info_label_mem_val, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_sys_info_label_mem_val, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_sys_info_label_mem_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_sys_info_label_mem_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_sys_info_label_mem_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_sys_info_label_mem_val, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_sys_info_label_mem_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_sys_info_label_mem_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_sys_info_label_mem_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_sys_info_label_mem_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_sys_info_label_mem_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sys_info_label_mem_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sys_info_label_mem
    ui->screen_sys_info_label_mem = lv_label_create(ui->screen_sys_info_cont_INFO);
    lv_label_set_text(ui->screen_sys_info_label_mem, "Memory");
    lv_label_set_long_mode(ui->screen_sys_info_label_mem, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_sys_info_label_mem, 4, 97);
    lv_obj_set_size(ui->screen_sys_info_label_mem, 60, 16);

    //Write style for screen_sys_info_label_mem, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_sys_info_label_mem, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sys_info_label_mem, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_sys_info_label_mem, lv_color_hex(0x717171), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_sys_info_label_mem, &lv_font_Inter_Regular_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_sys_info_label_mem, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_sys_info_label_mem, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_sys_info_label_mem, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_sys_info_label_mem, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_sys_info_label_mem, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_sys_info_label_mem, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_sys_info_label_mem, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_sys_info_label_mem, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_sys_info_label_mem, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sys_info_label_mem, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sys_info_cont_FAN_TEMP
    ui->screen_sys_info_cont_FAN_TEMP = lv_obj_create(ui->screen_sys_info);
    lv_obj_set_pos(ui->screen_sys_info_cont_FAN_TEMP, 224, 7);
    lv_obj_set_size(ui->screen_sys_info_cont_FAN_TEMP, 185, 126);
    lv_obj_set_scrollbar_mode(ui->screen_sys_info_cont_FAN_TEMP, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_sys_info_cont_FAN_TEMP, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_sys_info_cont_FAN_TEMP, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_sys_info_cont_FAN_TEMP, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_sys_info_cont_FAN_TEMP, lv_color_hex(0xc9c9c9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_sys_info_cont_FAN_TEMP, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sys_info_cont_FAN_TEMP, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_sys_info_cont_FAN_TEMP, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_sys_info_cont_FAN_TEMP, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_sys_info_cont_FAN_TEMP, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_sys_info_cont_FAN_TEMP, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_sys_info_cont_FAN_TEMP, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sys_info_cont_FAN_TEMP, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sys_info_bar_hdd_fan
    ui->screen_sys_info_bar_hdd_fan = lv_bar_create(ui->screen_sys_info_cont_FAN_TEMP);
    lv_obj_set_style_anim_time(ui->screen_sys_info_bar_hdd_fan, 1000, 0);
    lv_bar_set_mode(ui->screen_sys_info_bar_hdd_fan, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui->screen_sys_info_bar_hdd_fan, 0, 100);
    lv_bar_set_value(ui->screen_sys_info_bar_hdd_fan, 100, LV_ANIM_OFF);
    lv_obj_set_pos(ui->screen_sys_info_bar_hdd_fan, 76, 105);
    lv_obj_set_size(ui->screen_sys_info_bar_hdd_fan, 100, 5);

    //Write style for screen_sys_info_bar_hdd_fan, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_sys_info_bar_hdd_fan, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_sys_info_bar_hdd_fan, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_sys_info_bar_hdd_fan, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sys_info_bar_hdd_fan, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sys_info_bar_hdd_fan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_sys_info_bar_hdd_fan, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_sys_info_bar_hdd_fan, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_sys_info_bar_hdd_fan, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_sys_info_bar_hdd_fan, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sys_info_bar_hdd_fan, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes screen_sys_info_label_hdd_fan
    ui->screen_sys_info_label_hdd_fan = lv_label_create(ui->screen_sys_info_cont_FAN_TEMP);
    lv_label_set_text(ui->screen_sys_info_label_hdd_fan, "100%");
    lv_label_set_long_mode(ui->screen_sys_info_label_hdd_fan, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_sys_info_label_hdd_fan, 76, 87);
    lv_obj_set_size(ui->screen_sys_info_label_hdd_fan, 40, 12);

    //Write style for screen_sys_info_label_hdd_fan, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_sys_info_label_hdd_fan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sys_info_label_hdd_fan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_sys_info_label_hdd_fan, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_sys_info_label_hdd_fan, &lv_font_Inter_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_sys_info_label_hdd_fan, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_sys_info_label_hdd_fan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_sys_info_label_hdd_fan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_sys_info_label_hdd_fan, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_sys_info_label_hdd_fan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_sys_info_label_hdd_fan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_sys_info_label_hdd_fan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_sys_info_label_hdd_fan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_sys_info_label_hdd_fan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sys_info_label_hdd_fan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sys_info_label_HDD_FAN
    ui->screen_sys_info_label_HDD_FAN = lv_label_create(ui->screen_sys_info_cont_FAN_TEMP);
    lv_label_set_text(ui->screen_sys_info_label_HDD_FAN, "HDD");
    lv_label_set_long_mode(ui->screen_sys_info_label_HDD_FAN, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_sys_info_label_HDD_FAN, 35, 92);
    lv_obj_set_size(ui->screen_sys_info_label_HDD_FAN, 38, 16);

    //Write style for screen_sys_info_label_HDD_FAN, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_sys_info_label_HDD_FAN, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sys_info_label_HDD_FAN, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_sys_info_label_HDD_FAN, lv_color_hex(0x727272), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_sys_info_label_HDD_FAN, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_sys_info_label_HDD_FAN, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_sys_info_label_HDD_FAN, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_sys_info_label_HDD_FAN, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_sys_info_label_HDD_FAN, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_sys_info_label_HDD_FAN, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_sys_info_label_HDD_FAN, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_sys_info_label_HDD_FAN, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_sys_info_label_HDD_FAN, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_sys_info_label_HDD_FAN, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sys_info_label_HDD_FAN, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sys_info_img_HDD_FAN
    ui->screen_sys_info_img_HDD_FAN = lv_img_create(ui->screen_sys_info_cont_FAN_TEMP);
    lv_obj_add_flag(ui->screen_sys_info_img_HDD_FAN, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_sys_info_img_HDD_FAN, &_fan_alpha_26x26);
    lv_img_set_pivot(ui->screen_sys_info_img_HDD_FAN, 0,0);
    lv_img_set_angle(ui->screen_sys_info_img_HDD_FAN, 0);
    lv_obj_set_pos(ui->screen_sys_info_img_HDD_FAN, 7, 87);
    lv_obj_set_size(ui->screen_sys_info_img_HDD_FAN, 26, 26);

    //Write style for screen_sys_info_img_HDD_FAN, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_sys_info_img_HDD_FAN, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_sys_info_img_HDD_FAN, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sys_info_img_HDD_FAN, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_sys_info_img_HDD_FAN, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sys_info_bar_cpu_fan
    ui->screen_sys_info_bar_cpu_fan = lv_bar_create(ui->screen_sys_info_cont_FAN_TEMP);
    lv_obj_set_style_anim_time(ui->screen_sys_info_bar_cpu_fan, 1000, 0);
    lv_bar_set_mode(ui->screen_sys_info_bar_cpu_fan, LV_BAR_MODE_NORMAL);
    lv_bar_set_range(ui->screen_sys_info_bar_cpu_fan, 0, 100);
    lv_bar_set_value(ui->screen_sys_info_bar_cpu_fan, 100, LV_ANIM_OFF);
    lv_obj_set_pos(ui->screen_sys_info_bar_cpu_fan, 76, 70);
    lv_obj_set_size(ui->screen_sys_info_bar_cpu_fan, 100, 5);

    //Write style for screen_sys_info_bar_cpu_fan, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_sys_info_bar_cpu_fan, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_sys_info_bar_cpu_fan, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_sys_info_bar_cpu_fan, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sys_info_bar_cpu_fan, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sys_info_bar_cpu_fan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_sys_info_bar_cpu_fan, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_sys_info_bar_cpu_fan, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_sys_info_bar_cpu_fan, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_sys_info_bar_cpu_fan, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sys_info_bar_cpu_fan, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write codes screen_sys_info_label_cpu_fan
    ui->screen_sys_info_label_cpu_fan = lv_label_create(ui->screen_sys_info_cont_FAN_TEMP);
    lv_label_set_text(ui->screen_sys_info_label_cpu_fan, "100%");
    lv_label_set_long_mode(ui->screen_sys_info_label_cpu_fan, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_sys_info_label_cpu_fan, 76, 52);
    lv_obj_set_size(ui->screen_sys_info_label_cpu_fan, 40, 12);

    //Write style for screen_sys_info_label_cpu_fan, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_sys_info_label_cpu_fan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sys_info_label_cpu_fan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_sys_info_label_cpu_fan, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_sys_info_label_cpu_fan, &lv_font_Inter_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_sys_info_label_cpu_fan, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_sys_info_label_cpu_fan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_sys_info_label_cpu_fan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_sys_info_label_cpu_fan, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_sys_info_label_cpu_fan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_sys_info_label_cpu_fan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_sys_info_label_cpu_fan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_sys_info_label_cpu_fan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_sys_info_label_cpu_fan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sys_info_label_cpu_fan, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sys_info_label_CPU_FAN
    ui->screen_sys_info_label_CPU_FAN = lv_label_create(ui->screen_sys_info_cont_FAN_TEMP);
    lv_label_set_text(ui->screen_sys_info_label_CPU_FAN, "CPU");
    lv_label_set_long_mode(ui->screen_sys_info_label_CPU_FAN, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_sys_info_label_CPU_FAN, 36, 56);
    lv_obj_set_size(ui->screen_sys_info_label_CPU_FAN, 35, 16);

    //Write style for screen_sys_info_label_CPU_FAN, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_sys_info_label_CPU_FAN, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sys_info_label_CPU_FAN, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_sys_info_label_CPU_FAN, lv_color_hex(0x727272), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_sys_info_label_CPU_FAN, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_sys_info_label_CPU_FAN, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_sys_info_label_CPU_FAN, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_sys_info_label_CPU_FAN, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_sys_info_label_CPU_FAN, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_sys_info_label_CPU_FAN, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_sys_info_label_CPU_FAN, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_sys_info_label_CPU_FAN, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_sys_info_label_CPU_FAN, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_sys_info_label_CPU_FAN, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sys_info_label_CPU_FAN, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sys_info_img_CPU_FAN
    ui->screen_sys_info_img_CPU_FAN = lv_img_create(ui->screen_sys_info_cont_FAN_TEMP);
    lv_obj_add_flag(ui->screen_sys_info_img_CPU_FAN, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_sys_info_img_CPU_FAN, &_fan_alpha_26x26);
    lv_img_set_pivot(ui->screen_sys_info_img_CPU_FAN, 0,0);
    lv_img_set_angle(ui->screen_sys_info_img_CPU_FAN, 0);
    lv_obj_set_pos(ui->screen_sys_info_img_CPU_FAN, 7, 50);
    lv_obj_set_size(ui->screen_sys_info_img_CPU_FAN, 26, 26);

    //Write style for screen_sys_info_img_CPU_FAN, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_sys_info_img_CPU_FAN, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_sys_info_img_CPU_FAN, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sys_info_img_CPU_FAN, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_sys_info_img_CPU_FAN, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sys_info_label_cpu_temp_val
    ui->screen_sys_info_label_cpu_temp_val = lv_label_create(ui->screen_sys_info_cont_FAN_TEMP);
    lv_label_set_text(ui->screen_sys_info_label_cpu_temp_val, "45℃");
    lv_label_set_long_mode(ui->screen_sys_info_label_cpu_temp_val, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_sys_info_label_cpu_temp_val, 81, 18);
    lv_obj_set_size(ui->screen_sys_info_label_cpu_temp_val, 90, 16);

    //Write style for screen_sys_info_label_cpu_temp_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_sys_info_label_cpu_temp_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sys_info_label_cpu_temp_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_sys_info_label_cpu_temp_val, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_sys_info_label_cpu_temp_val, &lv_font_Inter_Bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_sys_info_label_cpu_temp_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_sys_info_label_cpu_temp_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_sys_info_label_cpu_temp_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_sys_info_label_cpu_temp_val, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_sys_info_label_cpu_temp_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_sys_info_label_cpu_temp_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_sys_info_label_cpu_temp_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_sys_info_label_cpu_temp_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_sys_info_label_cpu_temp_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sys_info_label_cpu_temp_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sys_info_label_CPU_TEMP
    ui->screen_sys_info_label_CPU_TEMP = lv_label_create(ui->screen_sys_info_cont_FAN_TEMP);
    lv_label_set_text(ui->screen_sys_info_label_CPU_TEMP, "CPU");
    lv_label_set_long_mode(ui->screen_sys_info_label_CPU_TEMP, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_sys_info_label_CPU_TEMP, 36, 18);
    lv_obj_set_size(ui->screen_sys_info_label_CPU_TEMP, 35, 16);

    //Write style for screen_sys_info_label_CPU_TEMP, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_sys_info_label_CPU_TEMP, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sys_info_label_CPU_TEMP, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_sys_info_label_CPU_TEMP, lv_color_hex(0x717171), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_sys_info_label_CPU_TEMP, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_sys_info_label_CPU_TEMP, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_sys_info_label_CPU_TEMP, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_sys_info_label_CPU_TEMP, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_sys_info_label_CPU_TEMP, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_sys_info_label_CPU_TEMP, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_sys_info_label_CPU_TEMP, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_sys_info_label_CPU_TEMP, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_sys_info_label_CPU_TEMP, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_sys_info_label_CPU_TEMP, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_sys_info_label_CPU_TEMP, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_sys_info_img_CPU_TEMP
    ui->screen_sys_info_img_CPU_TEMP = lv_img_create(ui->screen_sys_info_cont_FAN_TEMP);
    lv_obj_add_flag(ui->screen_sys_info_img_CPU_TEMP, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_sys_info_img_CPU_TEMP, &_temperature_alpha_12x26);
    lv_img_set_pivot(ui->screen_sys_info_img_CPU_TEMP, 0,0);
    lv_img_set_angle(ui->screen_sys_info_img_CPU_TEMP, 0);
    lv_obj_set_pos(ui->screen_sys_info_img_CPU_TEMP, 14, 13);
    lv_obj_set_size(ui->screen_sys_info_img_CPU_TEMP, 12, 26);

    //Write style for screen_sys_info_img_CPU_TEMP, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_sys_info_img_CPU_TEMP, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_sys_info_img_CPU_TEMP, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_sys_info_img_CPU_TEMP, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_sys_info_img_CPU_TEMP, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_sys_info.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_sys_info);

}
