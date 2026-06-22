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



void setup_scr_screen_overview(lv_ui *ui)
{
    //Write codes screen_overview
    ui->screen_overview = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_overview, 428, 142);
    lv_obj_set_scrollbar_mode(ui->screen_overview, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_overview, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_overview, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_overview, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_overview, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_overview_img_NAS_LOGO
    ui->screen_overview_img_NAS_LOGO = lv_img_create(ui->screen_overview);
    lv_obj_add_flag(ui->screen_overview_img_NAS_LOGO, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_overview_img_NAS_LOGO, &_nas_logo_alpha_82x82);
    lv_img_set_pivot(ui->screen_overview_img_NAS_LOGO, 50,50);
    lv_img_set_angle(ui->screen_overview_img_NAS_LOGO, 0);
    lv_obj_set_pos(ui->screen_overview_img_NAS_LOGO, 12, 11);
    lv_obj_set_size(ui->screen_overview_img_NAS_LOGO, 82, 82);

    //Write style for screen_overview_img_NAS_LOGO, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_overview_img_NAS_LOGO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_overview_img_NAS_LOGO, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_overview_img_NAS_LOGO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_overview_img_NAS_LOGO, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_overview_label_nas_name
    ui->screen_overview_label_nas_name = lv_label_create(ui->screen_overview);
    lv_label_set_text(ui->screen_overview_label_nas_name, "NAS Name");
    lv_label_set_long_mode(ui->screen_overview_label_nas_name, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_pos(ui->screen_overview_label_nas_name, 12, 100);
    lv_obj_set_size(ui->screen_overview_label_nas_name, 83, 16);

    //Write style for screen_overview_label_nas_name, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_overview_label_nas_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_overview_label_nas_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_overview_label_nas_name, lv_color_hex(0x4d9efc), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_overview_label_nas_name, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_overview_label_nas_name, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_overview_label_nas_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_overview_label_nas_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_overview_label_nas_name, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_overview_label_nas_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_overview_label_nas_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_overview_label_nas_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_overview_label_nas_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_overview_label_nas_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_overview_label_nas_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_overview_img_nas_status
    ui->screen_overview_img_nas_status = lv_img_create(ui->screen_overview);
    lv_obj_add_flag(ui->screen_overview_img_nas_status, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_overview_img_nas_status, &_offline_alpha_15x15);
    lv_img_set_pivot(ui->screen_overview_img_nas_status, 50,50);
    lv_img_set_angle(ui->screen_overview_img_nas_status, 0);
    lv_obj_set_pos(ui->screen_overview_img_nas_status, 11, 119);
    lv_obj_set_size(ui->screen_overview_img_nas_status, 15, 15);

    //Write style for screen_overview_img_nas_status, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_overview_img_nas_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_overview_img_nas_status, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_overview_img_nas_status, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_overview_img_nas_status, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_overview_label_nas_state
    ui->screen_overview_label_nas_state = lv_label_create(ui->screen_overview);
    lv_label_set_text(ui->screen_overview_label_nas_state, "Offline");
    lv_label_set_long_mode(ui->screen_overview_label_nas_state, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_overview_label_nas_state, 30, 121);
    lv_obj_set_size(ui->screen_overview_label_nas_state, 63, 12);

    //Write style for screen_overview_label_nas_state, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_overview_label_nas_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_overview_label_nas_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_overview_label_nas_state, lv_color_hex(0xa4a4a4), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_overview_label_nas_state, &lv_font_Inter_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_overview_label_nas_state, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_overview_label_nas_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_overview_label_nas_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_overview_label_nas_state, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_overview_label_nas_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_overview_label_nas_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_overview_label_nas_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_overview_label_nas_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_overview_label_nas_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_overview_label_nas_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_overview_cont_MEM
    ui->screen_overview_cont_MEM = lv_obj_create(ui->screen_overview);
    lv_obj_set_pos(ui->screen_overview_cont_MEM, 313, 70);
    lv_obj_set_size(ui->screen_overview_cont_MEM, 100, 55);
    lv_obj_set_scrollbar_mode(ui->screen_overview_cont_MEM, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_overview_cont_MEM, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_overview_cont_MEM, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_overview_cont_MEM, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_overview_cont_MEM, lv_color_hex(0xC9C9C9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_overview_cont_MEM, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_overview_cont_MEM, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_overview_cont_MEM, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_overview_cont_MEM, lv_color_hex(0x050505), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_overview_cont_MEM, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_overview_cont_MEM, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_overview_cont_MEM, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_overview_cont_MEM, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_overview_cont_MEM, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_overview_cont_MEM, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_overview_label_mem
    ui->screen_overview_label_mem = lv_label_create(ui->screen_overview_cont_MEM);
    lv_label_set_text(ui->screen_overview_label_mem, "MEMORY");
    lv_label_set_long_mode(ui->screen_overview_label_mem, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_overview_label_mem, 5, 5);
    lv_obj_set_size(ui->screen_overview_label_mem, 63, 12);

    //Write style for screen_overview_label_mem, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_overview_label_mem, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_overview_label_mem, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_overview_label_mem, lv_color_hex(0x9e9e9e), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_overview_label_mem, &lv_font_Inter_Bold_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_overview_label_mem, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_overview_label_mem, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_overview_label_mem, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_overview_label_mem, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_overview_label_mem, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_overview_label_mem, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_overview_label_mem, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_overview_label_mem, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_overview_label_mem, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_overview_label_mem, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_overview_label_mem_val
    ui->screen_overview_label_mem_val = lv_label_create(ui->screen_overview_cont_MEM);
    lv_label_set_text(ui->screen_overview_label_mem_val, "25%");
    lv_label_set_long_mode(ui->screen_overview_label_mem_val, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_overview_label_mem_val, 3, 22);
    lv_obj_set_size(ui->screen_overview_label_mem_val, 70, 26);

    //Write style for screen_overview_label_mem_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_overview_label_mem_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_overview_label_mem_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_overview_label_mem_val, lv_color_hex(0x9a7aff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_overview_label_mem_val, &lv_font_Inter_Bold_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_overview_label_mem_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_overview_label_mem_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_overview_label_mem_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_overview_label_mem_val, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_overview_label_mem_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_overview_label_mem_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_overview_label_mem_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_overview_label_mem_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_overview_label_mem_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_overview_label_mem_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_overview_cont_CPU
    ui->screen_overview_cont_CPU = lv_obj_create(ui->screen_overview);
    lv_obj_set_pos(ui->screen_overview_cont_CPU, 209, 70);
    lv_obj_set_size(ui->screen_overview_cont_CPU, 100, 55);
    lv_obj_set_scrollbar_mode(ui->screen_overview_cont_CPU, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_overview_cont_CPU, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_overview_cont_CPU, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_overview_cont_CPU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_overview_cont_CPU, lv_color_hex(0xC9C9C9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_overview_cont_CPU, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_overview_cont_CPU, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_overview_cont_CPU, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_overview_cont_CPU, lv_color_hex(0x050505), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_overview_cont_CPU, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_overview_cont_CPU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_overview_cont_CPU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_overview_cont_CPU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_overview_cont_CPU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_overview_cont_CPU, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_overview_label_cpu
    ui->screen_overview_label_cpu = lv_label_create(ui->screen_overview_cont_CPU);
    lv_label_set_text(ui->screen_overview_label_cpu, "CPU");
    lv_label_set_long_mode(ui->screen_overview_label_cpu, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_overview_label_cpu, 5, 5);
    lv_obj_set_size(ui->screen_overview_label_cpu, 63, 12);

    //Write style for screen_overview_label_cpu, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_overview_label_cpu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_overview_label_cpu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_overview_label_cpu, lv_color_hex(0x9e9e9e), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_overview_label_cpu, &lv_font_Inter_Bold_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_overview_label_cpu, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_overview_label_cpu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_overview_label_cpu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_overview_label_cpu, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_overview_label_cpu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_overview_label_cpu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_overview_label_cpu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_overview_label_cpu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_overview_label_cpu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_overview_label_cpu, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_overview_label_cpu_val
    ui->screen_overview_label_cpu_val = lv_label_create(ui->screen_overview_cont_CPU);
    lv_label_set_text(ui->screen_overview_label_cpu_val, "18%");
    lv_label_set_long_mode(ui->screen_overview_label_cpu_val, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_overview_label_cpu_val, 3, 22);
    lv_obj_set_size(ui->screen_overview_label_cpu_val, 70, 26);

    //Write style for screen_overview_label_cpu_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_overview_label_cpu_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_overview_label_cpu_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_overview_label_cpu_val, lv_color_hex(0x00e0ff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_overview_label_cpu_val, &lv_font_Inter_Bold_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_overview_label_cpu_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_overview_label_cpu_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_overview_label_cpu_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_overview_label_cpu_val, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_overview_label_cpu_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_overview_label_cpu_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_overview_label_cpu_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_overview_label_cpu_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_overview_label_cpu_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_overview_label_cpu_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_overview_cont_RUNTIME
    ui->screen_overview_cont_RUNTIME = lv_obj_create(ui->screen_overview);
    lv_obj_set_pos(ui->screen_overview_cont_RUNTIME, 104, 70);
    lv_obj_set_size(ui->screen_overview_cont_RUNTIME, 100, 55);
    lv_obj_set_scrollbar_mode(ui->screen_overview_cont_RUNTIME, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_overview_cont_RUNTIME, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_overview_cont_RUNTIME, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_overview_cont_RUNTIME, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_overview_cont_RUNTIME, lv_color_hex(0xC9C9C9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_overview_cont_RUNTIME, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_overview_cont_RUNTIME, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_overview_cont_RUNTIME, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_overview_cont_RUNTIME, lv_color_hex(0x050505), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_overview_cont_RUNTIME, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_overview_cont_RUNTIME, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_overview_cont_RUNTIME, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_overview_cont_RUNTIME, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_overview_cont_RUNTIME, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_overview_cont_RUNTIME, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_overview_label_runtime
    ui->screen_overview_label_runtime = lv_label_create(ui->screen_overview_cont_RUNTIME);
    lv_label_set_text(ui->screen_overview_label_runtime, "RUN TIME");
    lv_label_set_long_mode(ui->screen_overview_label_runtime, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_overview_label_runtime, 5, 5);
    lv_obj_set_size(ui->screen_overview_label_runtime, 63, 12);

    //Write style for screen_overview_label_runtime, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_overview_label_runtime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_overview_label_runtime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_overview_label_runtime, lv_color_hex(0x9e9e9e), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_overview_label_runtime, &lv_font_Inter_Bold_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_overview_label_runtime, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_overview_label_runtime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_overview_label_runtime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_overview_label_runtime, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_overview_label_runtime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_overview_label_runtime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_overview_label_runtime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_overview_label_runtime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_overview_label_runtime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_overview_label_runtime, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_overview_label_runtime_val
    ui->screen_overview_label_runtime_val = lv_label_create(ui->screen_overview_cont_RUNTIME);
    lv_label_set_text(ui->screen_overview_label_runtime_val, "123d");
    lv_label_set_long_mode(ui->screen_overview_label_runtime_val, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_overview_label_runtime_val, 3, 22);
    lv_obj_set_size(ui->screen_overview_label_runtime_val, 70, 26);

    //Write style for screen_overview_label_runtime_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_overview_label_runtime_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_overview_label_runtime_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_overview_label_runtime_val, lv_color_hex(0xD01FBB), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_overview_label_runtime_val, &lv_font_Inter_Bold_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_overview_label_runtime_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_overview_label_runtime_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_overview_label_runtime_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_overview_label_runtime_val, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_overview_label_runtime_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_overview_label_runtime_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_overview_label_runtime_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_overview_label_runtime_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_overview_label_runtime_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_overview_label_runtime_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_overview_cont_POWER
    ui->screen_overview_cont_POWER = lv_obj_create(ui->screen_overview);
    lv_obj_set_pos(ui->screen_overview_cont_POWER, 313, 11);
    lv_obj_set_size(ui->screen_overview_cont_POWER, 100, 55);
    lv_obj_set_scrollbar_mode(ui->screen_overview_cont_POWER, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_overview_cont_POWER, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_overview_cont_POWER, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_overview_cont_POWER, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_overview_cont_POWER, lv_color_hex(0xC9C9C9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_overview_cont_POWER, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_overview_cont_POWER, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_overview_cont_POWER, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_overview_cont_POWER, lv_color_hex(0x050505), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_overview_cont_POWER, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_overview_cont_POWER, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_overview_cont_POWER, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_overview_cont_POWER, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_overview_cont_POWER, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_overview_cont_POWER, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_overview_label_POWER_UNIT
    ui->screen_overview_label_POWER_UNIT = lv_label_create(ui->screen_overview_cont_POWER);
    lv_label_set_text(ui->screen_overview_label_POWER_UNIT, "W");
    lv_label_set_long_mode(ui->screen_overview_label_POWER_UNIT, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_overview_label_POWER_UNIT, 75, 26);
    lv_obj_set_size(ui->screen_overview_label_POWER_UNIT, 20, 20);

    //Write style for screen_overview_label_POWER_UNIT, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_overview_label_POWER_UNIT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_overview_label_POWER_UNIT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_overview_label_POWER_UNIT, lv_color_hex(0xC5C5C5), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_overview_label_POWER_UNIT, &lv_font_Inter_Bold_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_overview_label_POWER_UNIT, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_overview_label_POWER_UNIT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_overview_label_POWER_UNIT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_overview_label_POWER_UNIT, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_overview_label_POWER_UNIT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_overview_label_POWER_UNIT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_overview_label_POWER_UNIT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_overview_label_POWER_UNIT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_overview_label_POWER_UNIT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_overview_label_POWER_UNIT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_overview_label_power
    ui->screen_overview_label_power = lv_label_create(ui->screen_overview_cont_POWER);
    lv_label_set_text(ui->screen_overview_label_power, "POWER");
    lv_label_set_long_mode(ui->screen_overview_label_power, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_overview_label_power, 5, 4);
    lv_obj_set_size(ui->screen_overview_label_power, 63, 12);

    //Write style for screen_overview_label_power, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_overview_label_power, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_overview_label_power, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_overview_label_power, lv_color_hex(0x9e9e9e), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_overview_label_power, &lv_font_Inter_Bold_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_overview_label_power, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_overview_label_power, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_overview_label_power, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_overview_label_power, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_overview_label_power, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_overview_label_power, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_overview_label_power, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_overview_label_power, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_overview_label_power, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_overview_label_power, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_overview_label_power_val
    ui->screen_overview_label_power_val = lv_label_create(ui->screen_overview_cont_POWER);
    lv_label_set_text(ui->screen_overview_label_power_val, "32.12");
    lv_label_set_long_mode(ui->screen_overview_label_power_val, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_overview_label_power_val, 2, 22);
    lv_obj_set_size(ui->screen_overview_label_power_val, 70, 26);

    //Write style for screen_overview_label_power_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_overview_label_power_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_overview_label_power_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_overview_label_power_val, lv_color_hex(0xfaa20d), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_overview_label_power_val, &lv_font_Inter_Bold_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_overview_label_power_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_overview_label_power_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_overview_label_power_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_overview_label_power_val, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_overview_label_power_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_overview_label_power_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_overview_label_power_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_overview_label_power_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_overview_label_power_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_overview_label_power_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_overview_cont_CURRENT
    ui->screen_overview_cont_CURRENT = lv_obj_create(ui->screen_overview);
    lv_obj_set_pos(ui->screen_overview_cont_CURRENT, 209, 11);
    lv_obj_set_size(ui->screen_overview_cont_CURRENT, 100, 55);
    lv_obj_set_scrollbar_mode(ui->screen_overview_cont_CURRENT, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_overview_cont_CURRENT, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_overview_cont_CURRENT, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_overview_cont_CURRENT, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_overview_cont_CURRENT, lv_color_hex(0xC9C9C9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_overview_cont_CURRENT, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_overview_cont_CURRENT, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_overview_cont_CURRENT, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_overview_cont_CURRENT, lv_color_hex(0x050505), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_overview_cont_CURRENT, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_overview_cont_CURRENT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_overview_cont_CURRENT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_overview_cont_CURRENT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_overview_cont_CURRENT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_overview_cont_CURRENT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_overview_label_CURRENT_UNIT
    ui->screen_overview_label_CURRENT_UNIT = lv_label_create(ui->screen_overview_cont_CURRENT);
    lv_label_set_text(ui->screen_overview_label_CURRENT_UNIT, "A");
    lv_label_set_long_mode(ui->screen_overview_label_CURRENT_UNIT, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_overview_label_CURRENT_UNIT, 78, 26);
    lv_obj_set_size(ui->screen_overview_label_CURRENT_UNIT, 16, 20);

    //Write style for screen_overview_label_CURRENT_UNIT, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_overview_label_CURRENT_UNIT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_overview_label_CURRENT_UNIT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_overview_label_CURRENT_UNIT, lv_color_hex(0xC5C5C5), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_overview_label_CURRENT_UNIT, &lv_font_Inter_Bold_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_overview_label_CURRENT_UNIT, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_overview_label_CURRENT_UNIT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_overview_label_CURRENT_UNIT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_overview_label_CURRENT_UNIT, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_overview_label_CURRENT_UNIT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_overview_label_CURRENT_UNIT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_overview_label_CURRENT_UNIT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_overview_label_CURRENT_UNIT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_overview_label_CURRENT_UNIT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_overview_label_CURRENT_UNIT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_overview_label_current
    ui->screen_overview_label_current = lv_label_create(ui->screen_overview_cont_CURRENT);
    lv_label_set_text(ui->screen_overview_label_current, "CURRENT");
    lv_label_set_long_mode(ui->screen_overview_label_current, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_overview_label_current, 5, 5);
    lv_obj_set_size(ui->screen_overview_label_current, 63, 12);

    //Write style for screen_overview_label_current, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_overview_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_overview_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_overview_label_current, lv_color_hex(0x9e9e9e), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_overview_label_current, &lv_font_Inter_Bold_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_overview_label_current, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_overview_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_overview_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_overview_label_current, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_overview_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_overview_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_overview_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_overview_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_overview_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_overview_label_current, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_overview_label_current_val
    ui->screen_overview_label_current_val = lv_label_create(ui->screen_overview_cont_CURRENT);
    lv_label_set_text(ui->screen_overview_label_current_val, "2.65");
    lv_label_set_long_mode(ui->screen_overview_label_current_val, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_overview_label_current_val, 3, 22);
    lv_obj_set_size(ui->screen_overview_label_current_val, 70, 26);

    //Write style for screen_overview_label_current_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_overview_label_current_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_overview_label_current_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_overview_label_current_val, lv_color_hex(0x4e99f4), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_overview_label_current_val, &lv_font_Inter_Bold_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_overview_label_current_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_overview_label_current_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_overview_label_current_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_overview_label_current_val, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_overview_label_current_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_overview_label_current_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_overview_label_current_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_overview_label_current_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_overview_label_current_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_overview_label_current_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_overview_cont_VOLTAGE
    ui->screen_overview_cont_VOLTAGE = lv_obj_create(ui->screen_overview);
    lv_obj_set_pos(ui->screen_overview_cont_VOLTAGE, 104, 11);
    lv_obj_set_size(ui->screen_overview_cont_VOLTAGE, 100, 55);
    lv_obj_set_scrollbar_mode(ui->screen_overview_cont_VOLTAGE, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_overview_cont_VOLTAGE, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_overview_cont_VOLTAGE, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_overview_cont_VOLTAGE, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_overview_cont_VOLTAGE, lv_color_hex(0xC9C9C9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_overview_cont_VOLTAGE, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_overview_cont_VOLTAGE, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_overview_cont_VOLTAGE, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_overview_cont_VOLTAGE, lv_color_hex(0x050505), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_overview_cont_VOLTAGE, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_overview_cont_VOLTAGE, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_overview_cont_VOLTAGE, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_overview_cont_VOLTAGE, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_overview_cont_VOLTAGE, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_overview_cont_VOLTAGE, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_overview_label_VOLTAGE_UNIT
    ui->screen_overview_label_VOLTAGE_UNIT = lv_label_create(ui->screen_overview_cont_VOLTAGE);
    lv_label_set_text(ui->screen_overview_label_VOLTAGE_UNIT, "V");
    lv_label_set_long_mode(ui->screen_overview_label_VOLTAGE_UNIT, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_overview_label_VOLTAGE_UNIT, 78, 26);
    lv_obj_set_size(ui->screen_overview_label_VOLTAGE_UNIT, 16, 20);

    //Write style for screen_overview_label_VOLTAGE_UNIT, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_overview_label_VOLTAGE_UNIT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_overview_label_VOLTAGE_UNIT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_overview_label_VOLTAGE_UNIT, lv_color_hex(0xC5C5C5), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_overview_label_VOLTAGE_UNIT, &lv_font_Inter_Bold_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_overview_label_VOLTAGE_UNIT, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_overview_label_VOLTAGE_UNIT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_overview_label_VOLTAGE_UNIT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_overview_label_VOLTAGE_UNIT, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_overview_label_VOLTAGE_UNIT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_overview_label_VOLTAGE_UNIT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_overview_label_VOLTAGE_UNIT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_overview_label_VOLTAGE_UNIT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_overview_label_VOLTAGE_UNIT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_overview_label_VOLTAGE_UNIT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_overview_label_voltage
    ui->screen_overview_label_voltage = lv_label_create(ui->screen_overview_cont_VOLTAGE);
    lv_label_set_text(ui->screen_overview_label_voltage, "VOLTAGE");
    lv_label_set_long_mode(ui->screen_overview_label_voltage, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_overview_label_voltage, 5, 5);
    lv_obj_set_size(ui->screen_overview_label_voltage, 63, 12);

    //Write style for screen_overview_label_voltage, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_overview_label_voltage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_overview_label_voltage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_overview_label_voltage, lv_color_hex(0x9e9e9e), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_overview_label_voltage, &lv_font_Inter_Bold_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_overview_label_voltage, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_overview_label_voltage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_overview_label_voltage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_overview_label_voltage, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_overview_label_voltage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_overview_label_voltage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_overview_label_voltage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_overview_label_voltage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_overview_label_voltage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_overview_label_voltage, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_overview_label_voltage_val
    ui->screen_overview_label_voltage_val = lv_label_create(ui->screen_overview_cont_VOLTAGE);
    lv_label_set_text(ui->screen_overview_label_voltage_val, "12.12");
    lv_label_set_long_mode(ui->screen_overview_label_voltage_val, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_overview_label_voltage_val, 3, 22);
    lv_obj_set_size(ui->screen_overview_label_voltage_val, 70, 26);

    //Write style for screen_overview_label_voltage_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_overview_label_voltage_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_overview_label_voltage_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_overview_label_voltage_val, lv_color_hex(0x42b655), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_overview_label_voltage_val, &lv_font_Inter_Bold_26, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_overview_label_voltage_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_overview_label_voltage_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_overview_label_voltage_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_overview_label_voltage_val, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_overview_label_voltage_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_overview_label_voltage_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_overview_label_voltage_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_overview_label_voltage_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_overview_label_voltage_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_overview_label_voltage_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_overview_label_indicator1
    ui->screen_overview_label_indicator1 = lv_label_create(ui->screen_overview);
    lv_label_set_text(ui->screen_overview_label_indicator1, "");
    lv_label_set_long_mode(ui->screen_overview_label_indicator1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_overview_label_indicator1, 416, 42);
    lv_obj_set_size(ui->screen_overview_label_indicator1, 10, 10);

    //Write style for screen_overview_label_indicator1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_overview_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_overview_label_indicator1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_overview_label_indicator1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_overview_label_indicator1, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_overview_label_indicator1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_overview_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_overview_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_overview_label_indicator1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_overview_label_indicator1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_overview_label_indicator1, lv_color_hex(0x51a8f9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_overview_label_indicator1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_overview_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_overview_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_overview_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_overview_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_overview_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_overview_label_indicator2
    ui->screen_overview_label_indicator2 = lv_label_create(ui->screen_overview);
    lv_label_set_text(ui->screen_overview_label_indicator2, "");
    lv_label_set_long_mode(ui->screen_overview_label_indicator2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_overview_label_indicator2, 418, 58);
    lv_obj_set_size(ui->screen_overview_label_indicator2, 6, 6);

    //Write style for screen_overview_label_indicator2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_overview_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_overview_label_indicator2, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_overview_label_indicator2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_overview_label_indicator2, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_overview_label_indicator2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_overview_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_overview_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_overview_label_indicator2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_overview_label_indicator2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_overview_label_indicator2, lv_color_hex(0xbcbcbc), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_overview_label_indicator2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_overview_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_overview_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_overview_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_overview_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_overview_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_overview_label_indicator3
    ui->screen_overview_label_indicator3 = lv_label_create(ui->screen_overview);
    lv_label_set_text(ui->screen_overview_label_indicator3, "");
    lv_label_set_long_mode(ui->screen_overview_label_indicator3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_overview_label_indicator3, 418, 70);
    lv_obj_set_size(ui->screen_overview_label_indicator3, 6, 6);

    //Write style for screen_overview_label_indicator3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_overview_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_overview_label_indicator3, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_overview_label_indicator3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_overview_label_indicator3, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_overview_label_indicator3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_overview_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_overview_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_overview_label_indicator3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_overview_label_indicator3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_overview_label_indicator3, lv_color_hex(0xbcbcbc), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_overview_label_indicator3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_overview_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_overview_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_overview_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_overview_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_overview_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_overview_label_indicator4
    ui->screen_overview_label_indicator4 = lv_label_create(ui->screen_overview);
    lv_label_set_text(ui->screen_overview_label_indicator4, "");
    lv_label_set_long_mode(ui->screen_overview_label_indicator4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_overview_label_indicator4, 418, 82);
    lv_obj_set_size(ui->screen_overview_label_indicator4, 6, 6);

    //Write style for screen_overview_label_indicator4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_overview_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_overview_label_indicator4, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_overview_label_indicator4, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_overview_label_indicator4, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_overview_label_indicator4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_overview_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_overview_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_overview_label_indicator4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_overview_label_indicator4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_overview_label_indicator4, lv_color_hex(0xbcbcbc), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_overview_label_indicator4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_overview_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_overview_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_overview_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_overview_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_overview_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_overview_label_indicator5
    ui->screen_overview_label_indicator5 = lv_label_create(ui->screen_overview);
    lv_label_set_text(ui->screen_overview_label_indicator5, "");
    lv_label_set_long_mode(ui->screen_overview_label_indicator5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_overview_label_indicator5, 418, 94);
    lv_obj_set_size(ui->screen_overview_label_indicator5, 6, 6);

    //Write style for screen_overview_label_indicator5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_overview_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_overview_label_indicator5, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_overview_label_indicator5, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_overview_label_indicator5, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_overview_label_indicator5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_overview_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_overview_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_overview_label_indicator5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_overview_label_indicator5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_overview_label_indicator5, lv_color_hex(0xbcbcbc), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_overview_label_indicator5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_overview_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_overview_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_overview_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_overview_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_overview_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_overview.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_overview);

}
