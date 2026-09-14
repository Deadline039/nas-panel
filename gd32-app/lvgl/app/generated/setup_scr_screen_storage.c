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



void setup_scr_screen_storage(lv_ui *ui)
{
    //Write codes screen_storage
    ui->screen_storage = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_storage, 428, 142);
    lv_obj_set_scrollbar_mode(ui->screen_storage, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_storage, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_storage, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_storage, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_storage, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_storage_label_indicator1
    ui->screen_storage_label_indicator1 = lv_label_create(ui->screen_storage);
    lv_label_set_text(ui->screen_storage_label_indicator1, "");
    lv_label_set_long_mode(ui->screen_storage_label_indicator1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_storage_label_indicator1, 418, 54);
    lv_obj_set_size(ui->screen_storage_label_indicator1, 6, 6);

    //Write style for screen_storage_label_indicator1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_storage_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_storage_label_indicator1, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_storage_label_indicator1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_storage_label_indicator1, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_storage_label_indicator1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_storage_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_storage_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_storage_label_indicator1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_storage_label_indicator1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_storage_label_indicator1, lv_color_hex(0xbcbcbc), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_storage_label_indicator1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_storage_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_storage_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_storage_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_storage_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_storage_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_storage_label_indicator2
    ui->screen_storage_label_indicator2 = lv_label_create(ui->screen_storage);
    lv_label_set_text(ui->screen_storage_label_indicator2, "");
    lv_label_set_long_mode(ui->screen_storage_label_indicator2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_storage_label_indicator2, 418, 42);
    lv_obj_set_size(ui->screen_storage_label_indicator2, 6, 6);

    //Write style for screen_storage_label_indicator2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_storage_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_storage_label_indicator2, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_storage_label_indicator2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_storage_label_indicator2, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_storage_label_indicator2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_storage_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_storage_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_storage_label_indicator2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_storage_label_indicator2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_storage_label_indicator2, lv_color_hex(0xbcbcbc), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_storage_label_indicator2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_storage_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_storage_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_storage_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_storage_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_storage_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_storage_label_indicator3
    ui->screen_storage_label_indicator3 = lv_label_create(ui->screen_storage);
    lv_label_set_text(ui->screen_storage_label_indicator3, "");
    lv_label_set_long_mode(ui->screen_storage_label_indicator3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_storage_label_indicator3, 416, 66);
    lv_obj_set_size(ui->screen_storage_label_indicator3, 10, 10);

    //Write style for screen_storage_label_indicator3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_storage_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_storage_label_indicator3, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_storage_label_indicator3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_storage_label_indicator3, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_storage_label_indicator3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_storage_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_storage_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_storage_label_indicator3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_storage_label_indicator3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_storage_label_indicator3, lv_color_hex(0x51a8f9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_storage_label_indicator3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_storage_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_storage_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_storage_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_storage_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_storage_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_storage_label_indicator4
    ui->screen_storage_label_indicator4 = lv_label_create(ui->screen_storage);
    lv_label_set_text(ui->screen_storage_label_indicator4, "");
    lv_label_set_long_mode(ui->screen_storage_label_indicator4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_storage_label_indicator4, 418, 82);
    lv_obj_set_size(ui->screen_storage_label_indicator4, 6, 6);

    //Write style for screen_storage_label_indicator4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_storage_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_storage_label_indicator4, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_storage_label_indicator4, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_storage_label_indicator4, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_storage_label_indicator4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_storage_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_storage_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_storage_label_indicator4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_storage_label_indicator4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_storage_label_indicator4, lv_color_hex(0xbcbcbc), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_storage_label_indicator4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_storage_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_storage_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_storage_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_storage_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_storage_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_storage_label_indicator5
    ui->screen_storage_label_indicator5 = lv_label_create(ui->screen_storage);
    lv_label_set_text(ui->screen_storage_label_indicator5, "");
    lv_label_set_long_mode(ui->screen_storage_label_indicator5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_storage_label_indicator5, 418, 94);
    lv_obj_set_size(ui->screen_storage_label_indicator5, 6, 6);

    //Write style for screen_storage_label_indicator5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_storage_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_storage_label_indicator5, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_storage_label_indicator5, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_storage_label_indicator5, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_storage_label_indicator5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_storage_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_storage_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_storage_label_indicator5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_storage_label_indicator5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_storage_label_indicator5, lv_color_hex(0xbcbcbc), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_storage_label_indicator5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_storage_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_storage_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_storage_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_storage_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_storage_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_storage_cont_DISK_OVERVIEW
    ui->screen_storage_cont_DISK_OVERVIEW = lv_obj_create(ui->screen_storage);
    lv_obj_set_pos(ui->screen_storage_cont_DISK_OVERVIEW, 7, 7);
    lv_obj_set_size(ui->screen_storage_cont_DISK_OVERVIEW, 230, 124);
    lv_obj_set_scrollbar_mode(ui->screen_storage_cont_DISK_OVERVIEW, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_storage_cont_DISK_OVERVIEW, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_storage_cont_DISK_OVERVIEW, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_storage_cont_DISK_OVERVIEW, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_storage_cont_DISK_OVERVIEW, lv_color_hex(0xc9c9c9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_storage_cont_DISK_OVERVIEW, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_storage_cont_DISK_OVERVIEW, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_storage_cont_DISK_OVERVIEW, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_storage_cont_DISK_OVERVIEW, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_storage_cont_DISK_OVERVIEW, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_storage_cont_DISK_OVERVIEW, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_storage_cont_DISK_OVERVIEW, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_storage_cont_DISK_OVERVIEW, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_storage_arc_usage
    ui->screen_storage_arc_usage = lv_arc_create(ui->screen_storage_cont_DISK_OVERVIEW);
    lv_arc_set_mode(ui->screen_storage_arc_usage, LV_ARC_MODE_NORMAL);
    lv_arc_set_range(ui->screen_storage_arc_usage, 0, 101);
    lv_arc_set_bg_angles(ui->screen_storage_arc_usage, 0, 360);
    lv_arc_set_value(ui->screen_storage_arc_usage, 50);
    lv_arc_set_rotation(ui->screen_storage_arc_usage, 270);
    lv_obj_set_pos(ui->screen_storage_arc_usage, 136, 23);
    lv_obj_set_size(ui->screen_storage_arc_usage, 85, 85);

    //Write style for screen_storage_arc_usage, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_storage_arc_usage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_storage_arc_usage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui->screen_storage_arc_usage, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->screen_storage_arc_usage, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->screen_storage_arc_usage, lv_color_hex(0x4d4d4d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_storage_arc_usage, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_storage_arc_usage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_storage_arc_usage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_storage_arc_usage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_storage_arc_usage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_storage_arc_usage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_storage_arc_usage, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_arc_width(ui->screen_storage_arc_usage, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->screen_storage_arc_usage, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->screen_storage_arc_usage, lv_color_hex(0x0093ff), LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for screen_storage_arc_usage, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_storage_arc_usage, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->screen_storage_arc_usage, 5, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes screen_storage_label_dev_path_val
    ui->screen_storage_label_dev_path_val = lv_label_create(ui->screen_storage_cont_DISK_OVERVIEW);
    lv_label_set_text(ui->screen_storage_label_dev_path_val, "/dev/nvme01");
    lv_label_set_long_mode(ui->screen_storage_label_dev_path_val, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_pos(ui->screen_storage_label_dev_path_val, 9, 93);
    lv_obj_set_size(ui->screen_storage_label_dev_path_val, 120, 18);

    //Write style for screen_storage_label_dev_path_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_storage_label_dev_path_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_storage_label_dev_path_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_storage_label_dev_path_val, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_storage_label_dev_path_val, &lv_font_Inter_Bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_storage_label_dev_path_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_storage_label_dev_path_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_storage_label_dev_path_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_storage_label_dev_path_val, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_storage_label_dev_path_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_storage_label_dev_path_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_storage_label_dev_path_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_storage_label_dev_path_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_storage_label_dev_path_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_storage_label_dev_path_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_storage_img_DISK_LOGO
    ui->screen_storage_img_DISK_LOGO = lv_img_create(ui->screen_storage_cont_DISK_OVERVIEW);
    lv_obj_add_flag(ui->screen_storage_img_DISK_LOGO, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_storage_img_DISK_LOGO, &_hdd_alpha_38x46);
    lv_img_set_pivot(ui->screen_storage_img_DISK_LOGO, 50,50);
    lv_img_set_angle(ui->screen_storage_img_DISK_LOGO, 0);
    lv_obj_set_pos(ui->screen_storage_img_DISK_LOGO, 9, 15);
    lv_obj_set_size(ui->screen_storage_img_DISK_LOGO, 38, 46);

    //Write style for screen_storage_img_DISK_LOGO, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_storage_img_DISK_LOGO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_storage_img_DISK_LOGO, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_storage_img_DISK_LOGO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_storage_img_DISK_LOGO, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_storage_label_disk_idx
    ui->screen_storage_label_disk_idx = lv_label_create(ui->screen_storage_cont_DISK_OVERVIEW);
    lv_label_set_text(ui->screen_storage_label_disk_idx, "Disk 1 of 3");
    lv_label_set_long_mode(ui->screen_storage_label_disk_idx, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_storage_label_disk_idx, 9, 76);
    lv_obj_set_size(ui->screen_storage_label_disk_idx, 100, 12);

    //Write style for screen_storage_label_disk_idx, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_storage_label_disk_idx, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_storage_label_disk_idx, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_storage_label_disk_idx, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_storage_label_disk_idx, &lv_font_Inter_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_storage_label_disk_idx, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_storage_label_disk_idx, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_storage_label_disk_idx, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_storage_label_disk_idx, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_storage_label_disk_idx, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_storage_label_disk_idx, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_storage_label_disk_idx, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_storage_label_disk_idx, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_storage_label_disk_idx, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_storage_label_disk_idx, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_storage_label_capacity
    ui->screen_storage_label_capacity = lv_label_create(ui->screen_storage_cont_DISK_OVERVIEW);
    lv_label_set_text(ui->screen_storage_label_capacity, "Capacity");
    lv_label_set_long_mode(ui->screen_storage_label_capacity, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_storage_label_capacity, 54, 21);
    lv_obj_set_size(ui->screen_storage_label_capacity, 65, 14);

    //Write style for screen_storage_label_capacity, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_storage_label_capacity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_storage_label_capacity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_storage_label_capacity, lv_color_hex(0x8b8b8b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_storage_label_capacity, &lv_font_Inter_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_storage_label_capacity, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_storage_label_capacity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_storage_label_capacity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_storage_label_capacity, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_storage_label_capacity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_storage_label_capacity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_storage_label_capacity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_storage_label_capacity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_storage_label_capacity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_storage_label_capacity, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_storage_label_used
    ui->screen_storage_label_used = lv_label_create(ui->screen_storage_cont_DISK_OVERVIEW);
    lv_label_set_text(ui->screen_storage_label_used, "Used");
    lv_label_set_long_mode(ui->screen_storage_label_used, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_storage_label_used, 154, 73);
    lv_obj_set_size(ui->screen_storage_label_used, 50, 12);

    //Write style for screen_storage_label_used, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_storage_label_used, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_storage_label_used, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_storage_label_used, lv_color_hex(0x909090), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_storage_label_used, &lv_font_Inter_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_storage_label_used, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_storage_label_used, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_storage_label_used, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_storage_label_used, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_storage_label_used, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_storage_label_used, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_storage_label_used, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_storage_label_used, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_storage_label_used, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_storage_label_used, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_storage_label_capacity_val
    ui->screen_storage_label_capacity_val = lv_label_create(ui->screen_storage_cont_DISK_OVERVIEW);
    lv_label_set_text(ui->screen_storage_label_capacity_val, "500GB");
    lv_label_set_long_mode(ui->screen_storage_label_capacity_val, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_storage_label_capacity_val, 53, 40);
    lv_obj_set_size(ui->screen_storage_label_capacity_val, 66, 18);

    //Write style for screen_storage_label_capacity_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_storage_label_capacity_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_storage_label_capacity_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_storage_label_capacity_val, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_storage_label_capacity_val, &lv_font_Inter_Bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_storage_label_capacity_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_storage_label_capacity_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_storage_label_capacity_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_storage_label_capacity_val, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_storage_label_capacity_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_storage_label_capacity_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_storage_label_capacity_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_storage_label_capacity_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_storage_label_capacity_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_storage_label_capacity_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_storage_label_usage_percent
    ui->screen_storage_label_usage_percent = lv_label_create(ui->screen_storage_cont_DISK_OVERVIEW);
    lv_label_set_text(ui->screen_storage_label_usage_percent, "100%");
    lv_label_set_long_mode(ui->screen_storage_label_usage_percent, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_storage_label_usage_percent, 152, 49);
    lv_obj_set_size(ui->screen_storage_label_usage_percent, 55, 18);

    //Write style for screen_storage_label_usage_percent, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_storage_label_usage_percent, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_storage_label_usage_percent, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_storage_label_usage_percent, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_storage_label_usage_percent, &lv_font_Inter_Bold_18, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_storage_label_usage_percent, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_storage_label_usage_percent, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_storage_label_usage_percent, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_storage_label_usage_percent, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_storage_label_usage_percent, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_storage_label_usage_percent, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_storage_label_usage_percent, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_storage_label_usage_percent, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_storage_label_usage_percent, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_storage_label_usage_percent, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_storage_cont_STATE
    ui->screen_storage_cont_STATE = lv_obj_create(ui->screen_storage);
    lv_obj_set_pos(ui->screen_storage_cont_STATE, 241, 7);
    lv_obj_set_size(ui->screen_storage_cont_STATE, 170, 124);
    lv_obj_set_scrollbar_mode(ui->screen_storage_cont_STATE, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_storage_cont_STATE, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_storage_cont_STATE, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_storage_cont_STATE, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_storage_cont_STATE, lv_color_hex(0xC9C9C9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_storage_cont_STATE, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_storage_cont_STATE, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_storage_cont_STATE, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_storage_cont_STATE, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_storage_cont_STATE, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_storage_cont_STATE, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_storage_cont_STATE, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_storage_cont_STATE, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_storage_img_USAGE_TIME
    ui->screen_storage_img_USAGE_TIME = lv_img_create(ui->screen_storage_cont_STATE);
    lv_obj_add_flag(ui->screen_storage_img_USAGE_TIME, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_storage_img_USAGE_TIME, &_time_alpha_20x20);
    lv_img_set_pivot(ui->screen_storage_img_USAGE_TIME, 0,0);
    lv_img_set_angle(ui->screen_storage_img_USAGE_TIME, 0);
    lv_obj_set_pos(ui->screen_storage_img_USAGE_TIME, 8, 64);
    lv_obj_set_size(ui->screen_storage_img_USAGE_TIME, 20, 20);

    //Write style for screen_storage_img_USAGE_TIME, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_storage_img_USAGE_TIME, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_storage_img_USAGE_TIME, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_storage_img_USAGE_TIME, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_storage_img_USAGE_TIME, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_storage_img_STATUS
    ui->screen_storage_img_STATUS = lv_img_create(ui->screen_storage_cont_STATE);
    lv_obj_add_flag(ui->screen_storage_img_STATUS, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_storage_img_STATUS, &_hdd_health_alpha_20x20);
    lv_img_set_pivot(ui->screen_storage_img_STATUS, 0,0);
    lv_img_set_angle(ui->screen_storage_img_STATUS, 0);
    lv_obj_set_pos(ui->screen_storage_img_STATUS, 8, 8);
    lv_obj_set_size(ui->screen_storage_img_STATUS, 20, 20);

    //Write style for screen_storage_img_STATUS, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_storage_img_STATUS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_storage_img_STATUS, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_storage_img_STATUS, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_storage_img_STATUS, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_storage_img_TEMPERATURE
    ui->screen_storage_img_TEMPERATURE = lv_img_create(ui->screen_storage_cont_STATE);
    lv_obj_add_flag(ui->screen_storage_img_TEMPERATURE, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_storage_img_TEMPERATURE, &_temperature_alpha_10x22);
    lv_img_set_pivot(ui->screen_storage_img_TEMPERATURE, 0,0);
    lv_img_set_angle(ui->screen_storage_img_TEMPERATURE, 0);
    lv_obj_set_pos(ui->screen_storage_img_TEMPERATURE, 13, 35);
    lv_obj_set_size(ui->screen_storage_img_TEMPERATURE, 10, 22);

    //Write style for screen_storage_img_TEMPERATURE, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_storage_img_TEMPERATURE, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_storage_img_TEMPERATURE, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_storage_img_TEMPERATURE, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_storage_img_TEMPERATURE, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_storage_img_CYCLES
    ui->screen_storage_img_CYCLES = lv_img_create(ui->screen_storage_cont_STATE);
    lv_obj_add_flag(ui->screen_storage_img_CYCLES, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_storage_img_CYCLES, &_start_cycle_alpha_20x20);
    lv_img_set_pivot(ui->screen_storage_img_CYCLES, 0,0);
    lv_img_set_angle(ui->screen_storage_img_CYCLES, 0);
    lv_obj_set_pos(ui->screen_storage_img_CYCLES, 8, 91);
    lv_obj_set_size(ui->screen_storage_img_CYCLES, 20, 20);

    //Write style for screen_storage_img_CYCLES, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_storage_img_CYCLES, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_storage_img_CYCLES, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_storage_img_CYCLES, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_storage_img_CYCLES, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_storage_label_status
    ui->screen_storage_label_status = lv_label_create(ui->screen_storage_cont_STATE);
    lv_label_set_text(ui->screen_storage_label_status, "Status Good");
    lv_label_set_long_mode(ui->screen_storage_label_status, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_storage_label_status, 37, 10);
    lv_obj_set_size(ui->screen_storage_label_status, 120, 16);

    //Write style for screen_storage_label_status, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_storage_label_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_storage_label_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_storage_label_status, lv_color_hex(0x2FDA64), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_storage_label_status, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_storage_label_status, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_storage_label_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_storage_label_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_storage_label_status, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_storage_label_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_storage_label_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_storage_label_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_storage_label_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_storage_label_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_storage_label_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_storage_label_temperature
    ui->screen_storage_label_temperature = lv_label_create(ui->screen_storage_cont_STATE);
    lv_label_set_text(ui->screen_storage_label_temperature, "45℃");
    lv_label_set_long_mode(ui->screen_storage_label_temperature, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_pos(ui->screen_storage_label_temperature, 37, 38);
    lv_obj_set_size(ui->screen_storage_label_temperature, 120, 16);

    //Write style for screen_storage_label_temperature, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_storage_label_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_storage_label_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_storage_label_temperature, lv_color_hex(0x2FDA64), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_storage_label_temperature, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_storage_label_temperature, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_storage_label_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_storage_label_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_storage_label_temperature, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_storage_label_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_storage_label_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_storage_label_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_storage_label_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_storage_label_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_storage_label_temperature, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_storage_label_usage_time
    ui->screen_storage_label_usage_time = lv_label_create(ui->screen_storage_cont_STATE);
    lv_label_set_text(ui->screen_storage_label_usage_time, "144842 hours");
    lv_label_set_long_mode(ui->screen_storage_label_usage_time, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_storage_label_usage_time, 37, 66);
    lv_obj_set_size(ui->screen_storage_label_usage_time, 120, 16);

    //Write style for screen_storage_label_usage_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_storage_label_usage_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_storage_label_usage_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_storage_label_usage_time, lv_color_hex(0x2FDA64), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_storage_label_usage_time, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_storage_label_usage_time, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_storage_label_usage_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_storage_label_usage_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_storage_label_usage_time, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_storage_label_usage_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_storage_label_usage_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_storage_label_usage_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_storage_label_usage_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_storage_label_usage_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_storage_label_usage_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_storage_label_cycles
    ui->screen_storage_label_cycles = lv_label_create(ui->screen_storage_cont_STATE);
    lv_label_set_text(ui->screen_storage_label_cycles, "22548 cycles");
    lv_label_set_long_mode(ui->screen_storage_label_cycles, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_storage_label_cycles, 36, 94);
    lv_obj_set_size(ui->screen_storage_label_cycles, 120, 17);

    //Write style for screen_storage_label_cycles, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_storage_label_cycles, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_storage_label_cycles, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_storage_label_cycles, lv_color_hex(0x2FDA64), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_storage_label_cycles, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_storage_label_cycles, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_storage_label_cycles, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_storage_label_cycles, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_storage_label_cycles, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_storage_label_cycles, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_storage_label_cycles, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_storage_label_cycles, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_storage_label_cycles, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_storage_label_cycles, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_storage_label_cycles, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_storage.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_storage);

}
