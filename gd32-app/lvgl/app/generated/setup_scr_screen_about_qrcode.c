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



void setup_scr_screen_about_qrcode(lv_ui *ui)
{
    //Write codes screen_about_qrcode
    ui->screen_about_qrcode = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_about_qrcode, 428, 142);
    lv_obj_set_scrollbar_mode(ui->screen_about_qrcode, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_about_qrcode, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_about_qrcode, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_about_qrcode, lv_color_hex(0x090607), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_about_qrcode, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_about_qrcode_label_indicator1
    ui->screen_about_qrcode_label_indicator1 = lv_label_create(ui->screen_about_qrcode);
    lv_label_set_text(ui->screen_about_qrcode_label_indicator1, "");
    lv_label_set_long_mode(ui->screen_about_qrcode_label_indicator1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_about_qrcode_label_indicator1, 416, 92);
    lv_obj_set_size(ui->screen_about_qrcode_label_indicator1, 10, 10);

    //Write style for screen_about_qrcode_label_indicator1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_about_qrcode_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_about_qrcode_label_indicator1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_about_qrcode_label_indicator1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_about_qrcode_label_indicator1, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_about_qrcode_label_indicator1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_about_qrcode_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_about_qrcode_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_about_qrcode_label_indicator1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_about_qrcode_label_indicator1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_about_qrcode_label_indicator1, lv_color_hex(0x51a8f9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_about_qrcode_label_indicator1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_about_qrcode_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_about_qrcode_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_about_qrcode_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_about_qrcode_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_about_qrcode_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_about_qrcode_label_indicator2
    ui->screen_about_qrcode_label_indicator2 = lv_label_create(ui->screen_about_qrcode);
    lv_label_set_text(ui->screen_about_qrcode_label_indicator2, "");
    lv_label_set_long_mode(ui->screen_about_qrcode_label_indicator2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_about_qrcode_label_indicator2, 418, 80);
    lv_obj_set_size(ui->screen_about_qrcode_label_indicator2, 6, 6);

    //Write style for screen_about_qrcode_label_indicator2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_about_qrcode_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_about_qrcode_label_indicator2, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_about_qrcode_label_indicator2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_about_qrcode_label_indicator2, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_about_qrcode_label_indicator2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_about_qrcode_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_about_qrcode_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_about_qrcode_label_indicator2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_about_qrcode_label_indicator2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_about_qrcode_label_indicator2, lv_color_hex(0xbcbcbc), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_about_qrcode_label_indicator2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_about_qrcode_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_about_qrcode_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_about_qrcode_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_about_qrcode_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_about_qrcode_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_about_qrcode_label_indicator3
    ui->screen_about_qrcode_label_indicator3 = lv_label_create(ui->screen_about_qrcode);
    lv_label_set_text(ui->screen_about_qrcode_label_indicator3, "");
    lv_label_set_long_mode(ui->screen_about_qrcode_label_indicator3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_about_qrcode_label_indicator3, 418, 66);
    lv_obj_set_size(ui->screen_about_qrcode_label_indicator3, 6, 6);

    //Write style for screen_about_qrcode_label_indicator3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_about_qrcode_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_about_qrcode_label_indicator3, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_about_qrcode_label_indicator3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_about_qrcode_label_indicator3, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_about_qrcode_label_indicator3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_about_qrcode_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_about_qrcode_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_about_qrcode_label_indicator3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_about_qrcode_label_indicator3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_about_qrcode_label_indicator3, lv_color_hex(0xbcbcbc), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_about_qrcode_label_indicator3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_about_qrcode_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_about_qrcode_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_about_qrcode_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_about_qrcode_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_about_qrcode_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_about_qrcode_label_indicator4
    ui->screen_about_qrcode_label_indicator4 = lv_label_create(ui->screen_about_qrcode);
    lv_label_set_text(ui->screen_about_qrcode_label_indicator4, "");
    lv_label_set_long_mode(ui->screen_about_qrcode_label_indicator4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_about_qrcode_label_indicator4, 418, 54);
    lv_obj_set_size(ui->screen_about_qrcode_label_indicator4, 6, 6);

    //Write style for screen_about_qrcode_label_indicator4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_about_qrcode_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_about_qrcode_label_indicator4, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_about_qrcode_label_indicator4, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_about_qrcode_label_indicator4, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_about_qrcode_label_indicator4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_about_qrcode_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_about_qrcode_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_about_qrcode_label_indicator4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_about_qrcode_label_indicator4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_about_qrcode_label_indicator4, lv_color_hex(0xbcbcbc), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_about_qrcode_label_indicator4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_about_qrcode_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_about_qrcode_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_about_qrcode_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_about_qrcode_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_about_qrcode_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_about_qrcode_label_indicator5
    ui->screen_about_qrcode_label_indicator5 = lv_label_create(ui->screen_about_qrcode);
    lv_label_set_text(ui->screen_about_qrcode_label_indicator5, "");
    lv_label_set_long_mode(ui->screen_about_qrcode_label_indicator5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_about_qrcode_label_indicator5, 418, 42);
    lv_obj_set_size(ui->screen_about_qrcode_label_indicator5, 6, 6);

    //Write style for screen_about_qrcode_label_indicator5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_about_qrcode_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_about_qrcode_label_indicator5, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_about_qrcode_label_indicator5, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_about_qrcode_label_indicator5, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_about_qrcode_label_indicator5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_about_qrcode_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_about_qrcode_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_about_qrcode_label_indicator5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_about_qrcode_label_indicator5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_about_qrcode_label_indicator5, lv_color_hex(0xbcbcbc), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_about_qrcode_label_indicator5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_about_qrcode_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_about_qrcode_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_about_qrcode_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_about_qrcode_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_about_qrcode_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_about_qrcode_cont_ABOUT
    ui->screen_about_qrcode_cont_ABOUT = lv_obj_create(ui->screen_about_qrcode);
    lv_obj_set_pos(ui->screen_about_qrcode_cont_ABOUT, 8, 7);
    lv_obj_set_size(ui->screen_about_qrcode_cont_ABOUT, 210, 126);
    lv_obj_set_scrollbar_mode(ui->screen_about_qrcode_cont_ABOUT, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_about_qrcode_cont_ABOUT, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_about_qrcode_cont_ABOUT, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_about_qrcode_cont_ABOUT, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_about_qrcode_cont_ABOUT, lv_color_hex(0xC9C9c9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_about_qrcode_cont_ABOUT, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_about_qrcode_cont_ABOUT, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_about_qrcode_cont_ABOUT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_about_qrcode_cont_ABOUT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_about_qrcode_cont_ABOUT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_about_qrcode_cont_ABOUT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_about_qrcode_cont_ABOUT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_about_qrcode_cont_ABOUT, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_about_qrcode_label_fw_ver_val
    ui->screen_about_qrcode_label_fw_ver_val = lv_label_create(ui->screen_about_qrcode_cont_ABOUT);
    lv_label_set_text(ui->screen_about_qrcode_label_fw_ver_val, "v1.0");
    lv_label_set_long_mode(ui->screen_about_qrcode_label_fw_ver_val, LV_LABEL_LONG_SCROLL);
    lv_obj_set_pos(ui->screen_about_qrcode_label_fw_ver_val, 114, 13);
    lv_obj_set_size(ui->screen_about_qrcode_label_fw_ver_val, 80, 17);

    //Write style for screen_about_qrcode_label_fw_ver_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_about_qrcode_label_fw_ver_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_about_qrcode_label_fw_ver_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_about_qrcode_label_fw_ver_val, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_about_qrcode_label_fw_ver_val, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_about_qrcode_label_fw_ver_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_about_qrcode_label_fw_ver_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_about_qrcode_label_fw_ver_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_about_qrcode_label_fw_ver_val, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_about_qrcode_label_fw_ver_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_about_qrcode_label_fw_ver_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_about_qrcode_label_fw_ver_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_about_qrcode_label_fw_ver_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_about_qrcode_label_fw_ver_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_about_qrcode_label_fw_ver_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_about_qrcode_label_fw_ver
    ui->screen_about_qrcode_label_fw_ver = lv_label_create(ui->screen_about_qrcode_cont_ABOUT);
    lv_label_set_text(ui->screen_about_qrcode_label_fw_ver, "FW Version");
    lv_label_set_long_mode(ui->screen_about_qrcode_label_fw_ver, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_about_qrcode_label_fw_ver, 4, 13);
    lv_obj_set_size(ui->screen_about_qrcode_label_fw_ver, 100, 16);

    //Write style for screen_about_qrcode_label_fw_ver, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_about_qrcode_label_fw_ver, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_about_qrcode_label_fw_ver, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_about_qrcode_label_fw_ver, lv_color_hex(0x717171), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_about_qrcode_label_fw_ver, &lv_font_Inter_Regular_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_about_qrcode_label_fw_ver, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_about_qrcode_label_fw_ver, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_about_qrcode_label_fw_ver, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_about_qrcode_label_fw_ver, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_about_qrcode_label_fw_ver, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_about_qrcode_label_fw_ver, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_about_qrcode_label_fw_ver, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_about_qrcode_label_fw_ver, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_about_qrcode_label_fw_ver, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_about_qrcode_label_fw_ver, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_about_qrcode_label_build_time_val
    ui->screen_about_qrcode_label_build_time_val = lv_label_create(ui->screen_about_qrcode_cont_ABOUT);
    lv_label_set_text(ui->screen_about_qrcode_label_build_time_val, "June 20, 2026 14:42:21");
    lv_label_set_long_mode(ui->screen_about_qrcode_label_build_time_val, LV_LABEL_LONG_SCROLL);
    lv_obj_set_pos(ui->screen_about_qrcode_label_build_time_val, 114, 39);
    lv_obj_set_size(ui->screen_about_qrcode_label_build_time_val, 80, 17);

    //Write style for screen_about_qrcode_label_build_time_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_about_qrcode_label_build_time_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_about_qrcode_label_build_time_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_about_qrcode_label_build_time_val, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_about_qrcode_label_build_time_val, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_about_qrcode_label_build_time_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_about_qrcode_label_build_time_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_about_qrcode_label_build_time_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_about_qrcode_label_build_time_val, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_about_qrcode_label_build_time_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_about_qrcode_label_build_time_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_about_qrcode_label_build_time_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_about_qrcode_label_build_time_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_about_qrcode_label_build_time_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_about_qrcode_label_build_time_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_about_qrcode_label_build_time
    ui->screen_about_qrcode_label_build_time = lv_label_create(ui->screen_about_qrcode_cont_ABOUT);
    lv_label_set_text(ui->screen_about_qrcode_label_build_time, "Build time");
    lv_label_set_long_mode(ui->screen_about_qrcode_label_build_time, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_about_qrcode_label_build_time, 4, 41);
    lv_obj_set_size(ui->screen_about_qrcode_label_build_time, 100, 16);

    //Write style for screen_about_qrcode_label_build_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_about_qrcode_label_build_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_about_qrcode_label_build_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_about_qrcode_label_build_time, lv_color_hex(0x717171), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_about_qrcode_label_build_time, &lv_font_Inter_Regular_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_about_qrcode_label_build_time, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_about_qrcode_label_build_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_about_qrcode_label_build_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_about_qrcode_label_build_time, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_about_qrcode_label_build_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_about_qrcode_label_build_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_about_qrcode_label_build_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_about_qrcode_label_build_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_about_qrcode_label_build_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_about_qrcode_label_build_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_about_qrcode_label_upper_ver_val
    ui->screen_about_qrcode_label_upper_ver_val = lv_label_create(ui->screen_about_qrcode_cont_ABOUT);
    lv_label_set_text(ui->screen_about_qrcode_label_upper_ver_val, "v1.0");
    lv_label_set_long_mode(ui->screen_about_qrcode_label_upper_ver_val, LV_LABEL_LONG_SCROLL);
    lv_obj_set_pos(ui->screen_about_qrcode_label_upper_ver_val, 114, 67);
    lv_obj_set_size(ui->screen_about_qrcode_label_upper_ver_val, 80, 17);

    //Write style for screen_about_qrcode_label_upper_ver_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_about_qrcode_label_upper_ver_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_about_qrcode_label_upper_ver_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_about_qrcode_label_upper_ver_val, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_about_qrcode_label_upper_ver_val, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_about_qrcode_label_upper_ver_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_about_qrcode_label_upper_ver_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_about_qrcode_label_upper_ver_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_about_qrcode_label_upper_ver_val, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_about_qrcode_label_upper_ver_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_about_qrcode_label_upper_ver_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_about_qrcode_label_upper_ver_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_about_qrcode_label_upper_ver_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_about_qrcode_label_upper_ver_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_about_qrcode_label_upper_ver_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_about_qrcode_label_upper_ver
    ui->screen_about_qrcode_label_upper_ver = lv_label_create(ui->screen_about_qrcode_cont_ABOUT);
    lv_label_set_text(ui->screen_about_qrcode_label_upper_ver, "Upper Version");
    lv_label_set_long_mode(ui->screen_about_qrcode_label_upper_ver, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_about_qrcode_label_upper_ver, 4, 68);
    lv_obj_set_size(ui->screen_about_qrcode_label_upper_ver, 100, 16);

    //Write style for screen_about_qrcode_label_upper_ver, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_about_qrcode_label_upper_ver, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_about_qrcode_label_upper_ver, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_about_qrcode_label_upper_ver, lv_color_hex(0x717171), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_about_qrcode_label_upper_ver, &lv_font_Inter_Regular_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_about_qrcode_label_upper_ver, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_about_qrcode_label_upper_ver, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_about_qrcode_label_upper_ver, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_about_qrcode_label_upper_ver, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_about_qrcode_label_upper_ver, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_about_qrcode_label_upper_ver, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_about_qrcode_label_upper_ver, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_about_qrcode_label_upper_ver, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_about_qrcode_label_upper_ver, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_about_qrcode_label_upper_ver, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_about_qrcode_label_LICENSE_INFO
    ui->screen_about_qrcode_label_LICENSE_INFO = lv_label_create(ui->screen_about_qrcode_cont_ABOUT);
    lv_label_set_text(ui->screen_about_qrcode_label_LICENSE_INFO, "MIT License Copyright (c) Deadline039");
    lv_label_set_long_mode(ui->screen_about_qrcode_label_LICENSE_INFO, LV_LABEL_LONG_SCROLL);
    lv_obj_set_pos(ui->screen_about_qrcode_label_LICENSE_INFO, 114, 95);
    lv_obj_set_size(ui->screen_about_qrcode_label_LICENSE_INFO, 80, 17);

    //Write style for screen_about_qrcode_label_LICENSE_INFO, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_about_qrcode_label_LICENSE_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_about_qrcode_label_LICENSE_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_about_qrcode_label_LICENSE_INFO, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_about_qrcode_label_LICENSE_INFO, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_about_qrcode_label_LICENSE_INFO, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_about_qrcode_label_LICENSE_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_about_qrcode_label_LICENSE_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_about_qrcode_label_LICENSE_INFO, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_about_qrcode_label_LICENSE_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_about_qrcode_label_LICENSE_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_about_qrcode_label_LICENSE_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_about_qrcode_label_LICENSE_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_about_qrcode_label_LICENSE_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_about_qrcode_label_LICENSE_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_about_qrcode_label_LICENSE
    ui->screen_about_qrcode_label_LICENSE = lv_label_create(ui->screen_about_qrcode_cont_ABOUT);
    lv_label_set_text(ui->screen_about_qrcode_label_LICENSE, "LICENSE");
    lv_label_set_long_mode(ui->screen_about_qrcode_label_LICENSE, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_about_qrcode_label_LICENSE, 4, 97);
    lv_obj_set_size(ui->screen_about_qrcode_label_LICENSE, 100, 16);

    //Write style for screen_about_qrcode_label_LICENSE, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_about_qrcode_label_LICENSE, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_about_qrcode_label_LICENSE, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_about_qrcode_label_LICENSE, lv_color_hex(0x717171), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_about_qrcode_label_LICENSE, &lv_font_Inter_Regular_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_about_qrcode_label_LICENSE, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_about_qrcode_label_LICENSE, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_about_qrcode_label_LICENSE, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_about_qrcode_label_LICENSE, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_about_qrcode_label_LICENSE, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_about_qrcode_label_LICENSE, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_about_qrcode_label_LICENSE, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_about_qrcode_label_LICENSE, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_about_qrcode_label_LICENSE, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_about_qrcode_label_LICENSE, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_about_qrcode_qrcode_1
    ui->screen_about_qrcode_qrcode_1 = lv_qrcode_create(ui->screen_about_qrcode, 80, lv_color_hex(0x2C3224), lv_color_hex(0xffffff));
    const char * screen_about_qrcode_qrcode_1_data = "https://github.com/Deadline039/nas-panel";
    lv_qrcode_update(ui->screen_about_qrcode_qrcode_1, screen_about_qrcode_qrcode_1_data, 40);
    lv_obj_set_pos(ui->screen_about_qrcode_qrcode_1, 283, 48);
    lv_obj_set_size(ui->screen_about_qrcode_qrcode_1, 80, 80);

    //Write codes screen_about_qrcode_label_qr_code_info
    ui->screen_about_qrcode_label_qr_code_info = lv_label_create(ui->screen_about_qrcode);
    lv_label_set_text(ui->screen_about_qrcode_label_qr_code_info, "(1 of 3)Source code");
    lv_label_set_long_mode(ui->screen_about_qrcode_label_qr_code_info, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_about_qrcode_label_qr_code_info, 232, 9);
    lv_obj_set_size(ui->screen_about_qrcode_label_qr_code_info, 180, 16);

    //Write style for screen_about_qrcode_label_qr_code_info, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_about_qrcode_label_qr_code_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_about_qrcode_label_qr_code_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_about_qrcode_label_qr_code_info, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_about_qrcode_label_qr_code_info, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_about_qrcode_label_qr_code_info, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_about_qrcode_label_qr_code_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_about_qrcode_label_qr_code_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_about_qrcode_label_qr_code_info, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_about_qrcode_label_qr_code_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_about_qrcode_label_qr_code_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_about_qrcode_label_qr_code_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_about_qrcode_label_qr_code_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_about_qrcode_label_qr_code_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_about_qrcode_label_qr_code_info, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_about_qrcode_label_qrcode_val
    ui->screen_about_qrcode_label_qrcode_val = lv_label_create(ui->screen_about_qrcode);
    lv_label_set_text(ui->screen_about_qrcode_label_qrcode_val, "https://github.com/Deadline039/nas-panel");
    lv_label_set_long_mode(ui->screen_about_qrcode_label_qrcode_val, LV_LABEL_LONG_SCROLL);
    lv_obj_set_pos(ui->screen_about_qrcode_label_qrcode_val, 232, 25);
    lv_obj_set_size(ui->screen_about_qrcode_label_qrcode_val, 180, 17);

    //Write style for screen_about_qrcode_label_qrcode_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_about_qrcode_label_qrcode_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_about_qrcode_label_qrcode_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_about_qrcode_label_qrcode_val, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_about_qrcode_label_qrcode_val, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_about_qrcode_label_qrcode_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_about_qrcode_label_qrcode_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_about_qrcode_label_qrcode_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_about_qrcode_label_qrcode_val, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_about_qrcode_label_qrcode_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_about_qrcode_label_qrcode_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_about_qrcode_label_qrcode_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_about_qrcode_label_qrcode_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_about_qrcode_label_qrcode_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_about_qrcode_label_qrcode_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_about_qrcode.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_about_qrcode);

}
