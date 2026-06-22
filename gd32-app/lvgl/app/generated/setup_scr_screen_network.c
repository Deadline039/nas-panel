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



void setup_scr_screen_network(lv_ui *ui)
{
    //Write codes screen_network
    ui->screen_network = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_network, 428, 142);
    lv_obj_set_scrollbar_mode(ui->screen_network, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_network, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_network, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_network, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_network, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_network_cont_INFO
    ui->screen_network_cont_INFO = lv_obj_create(ui->screen_network);
    lv_obj_set_pos(ui->screen_network_cont_INFO, 289, 10);
    lv_obj_set_size(ui->screen_network_cont_INFO, 120, 122);
    lv_obj_set_scrollbar_mode(ui->screen_network_cont_INFO, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_network_cont_INFO, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_network_cont_INFO, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_network_cont_INFO, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_network_cont_INFO, lv_color_hex(0xC9C9C9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_network_cont_INFO, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_network_cont_INFO, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_network_cont_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_network_cont_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_network_cont_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_network_cont_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_network_cont_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_network_cont_INFO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_network_label_gateway_val
    ui->screen_network_label_gateway_val = lv_label_create(ui->screen_network_cont_INFO);
    lv_label_set_text(ui->screen_network_label_gateway_val, "0.0.0.0");
    lv_label_set_long_mode(ui->screen_network_label_gateway_val, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_network_label_gateway_val, 9, 98);
    lv_obj_set_size(ui->screen_network_label_gateway_val, 80, 16);

    //Write style for screen_network_label_gateway_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_network_label_gateway_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_network_label_gateway_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_network_label_gateway_val, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_network_label_gateway_val, &lv_font_Inter_Bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_network_label_gateway_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_network_label_gateway_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_network_label_gateway_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_network_label_gateway_val, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_network_label_gateway_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_network_label_gateway_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_network_label_gateway_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_network_label_gateway_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_network_label_gateway_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_network_label_gateway_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_network_label_gateway
    ui->screen_network_label_gateway = lv_label_create(ui->screen_network_cont_INFO);
    lv_label_set_text(ui->screen_network_label_gateway, "Gateway:");
    lv_label_set_long_mode(ui->screen_network_label_gateway, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_network_label_gateway, 9, 80);
    lv_obj_set_size(ui->screen_network_label_gateway, 65, 13);

    //Write style for screen_network_label_gateway, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_network_label_gateway, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_network_label_gateway, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_network_label_gateway, lv_color_hex(0x8e8e8e), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_network_label_gateway, &lv_font_Inter_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_network_label_gateway, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_network_label_gateway, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_network_label_gateway, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_network_label_gateway, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_network_label_gateway, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_network_label_gateway, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_network_label_gateway, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_network_label_gateway, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_network_label_gateway, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_network_label_gateway, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_network_label_subnet_mask
    ui->screen_network_label_subnet_mask = lv_label_create(ui->screen_network_cont_INFO);
    lv_label_set_text(ui->screen_network_label_subnet_mask, "0.0.0.0");
    lv_label_set_long_mode(ui->screen_network_label_subnet_mask, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_network_label_subnet_mask, 9, 61);
    lv_obj_set_size(ui->screen_network_label_subnet_mask, 80, 16);

    //Write style for screen_network_label_subnet_mask, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_network_label_subnet_mask, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_network_label_subnet_mask, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_network_label_subnet_mask, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_network_label_subnet_mask, &lv_font_Inter_Bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_network_label_subnet_mask, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_network_label_subnet_mask, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_network_label_subnet_mask, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_network_label_subnet_mask, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_network_label_subnet_mask, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_network_label_subnet_mask, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_network_label_subnet_mask, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_network_label_subnet_mask, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_network_label_subnet_mask, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_network_label_subnet_mask, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_network_label_subnet
    ui->screen_network_label_subnet = lv_label_create(ui->screen_network_cont_INFO);
    lv_label_set_text(ui->screen_network_label_subnet, "Subnet mask:");
    lv_label_set_long_mode(ui->screen_network_label_subnet, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_network_label_subnet, 9, 43);
    lv_obj_set_size(ui->screen_network_label_subnet, 100, 12);

    //Write style for screen_network_label_subnet, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_network_label_subnet, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_network_label_subnet, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_network_label_subnet, lv_color_hex(0x8e8e8e), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_network_label_subnet, &lv_font_Inter_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_network_label_subnet, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_network_label_subnet, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_network_label_subnet, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_network_label_subnet, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_network_label_subnet, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_network_label_subnet, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_network_label_subnet, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_network_label_subnet, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_network_label_subnet, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_network_label_subnet, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_network_label_ip_addr
    ui->screen_network_label_ip_addr = lv_label_create(ui->screen_network_cont_INFO);
    lv_label_set_text(ui->screen_network_label_ip_addr, "0.0.0.0");
    lv_label_set_long_mode(ui->screen_network_label_ip_addr, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_network_label_ip_addr, 9, 24);
    lv_obj_set_size(ui->screen_network_label_ip_addr, 80, 16);

    //Write style for screen_network_label_ip_addr, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_network_label_ip_addr, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_network_label_ip_addr, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_network_label_ip_addr, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_network_label_ip_addr, &lv_font_Inter_Bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_network_label_ip_addr, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_network_label_ip_addr, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_network_label_ip_addr, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_network_label_ip_addr, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_network_label_ip_addr, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_network_label_ip_addr, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_network_label_ip_addr, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_network_label_ip_addr, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_network_label_ip_addr, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_network_label_ip_addr, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_network_label_ip
    ui->screen_network_label_ip = lv_label_create(ui->screen_network_cont_INFO);
    lv_label_set_text(ui->screen_network_label_ip, "IP Address:");
    lv_label_set_long_mode(ui->screen_network_label_ip, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_network_label_ip, 8, 7);
    lv_obj_set_size(ui->screen_network_label_ip, 65, 12);

    //Write style for screen_network_label_ip, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_network_label_ip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_network_label_ip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_network_label_ip, lv_color_hex(0x8e8e8e), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_network_label_ip, &lv_font_Inter_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_network_label_ip, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_network_label_ip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_network_label_ip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_network_label_ip, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_network_label_ip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_network_label_ip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_network_label_ip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_network_label_ip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_network_label_ip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_network_label_ip, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_network_cont_SPEED
    ui->screen_network_cont_SPEED = lv_obj_create(ui->screen_network);
    lv_obj_set_pos(ui->screen_network_cont_SPEED, 161, 10);
    lv_obj_set_size(ui->screen_network_cont_SPEED, 125, 122);
    lv_obj_set_scrollbar_mode(ui->screen_network_cont_SPEED, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_network_cont_SPEED, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_network_cont_SPEED, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_network_cont_SPEED, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_network_cont_SPEED, lv_color_hex(0xc9c9c9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_network_cont_SPEED, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_network_cont_SPEED, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_network_cont_SPEED, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_network_cont_SPEED, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_network_cont_SPEED, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_network_cont_SPEED, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_network_cont_SPEED, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_network_cont_SPEED, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_network_label_up_total_val
    ui->screen_network_label_up_total_val = lv_label_create(ui->screen_network_cont_SPEED);
    lv_label_set_text(ui->screen_network_label_up_total_val, "0");
    lv_label_set_long_mode(ui->screen_network_label_up_total_val, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_network_label_up_total_val, 42, 35);
    lv_obj_set_size(ui->screen_network_label_up_total_val, 40, 14);

    //Write style for screen_network_label_up_total_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_network_label_up_total_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_network_label_up_total_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_network_label_up_total_val, lv_color_hex(0x28994e), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_network_label_up_total_val, &lv_font_Inter_Bold_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_network_label_up_total_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_network_label_up_total_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_network_label_up_total_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_network_label_up_total_val, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_network_label_up_total_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_network_label_up_total_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_network_label_up_total_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_network_label_up_total_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_network_label_up_total_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_network_label_up_total_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_network_label_up_total_unit
    ui->screen_network_label_up_total_unit = lv_label_create(ui->screen_network_cont_SPEED);
    lv_label_set_text(ui->screen_network_label_up_total_unit, "KB");
    lv_label_set_long_mode(ui->screen_network_label_up_total_unit, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_network_label_up_total_unit, 88, 36);
    lv_obj_set_size(ui->screen_network_label_up_total_unit, 30, 12);

    //Write style for screen_network_label_up_total_unit, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_network_label_up_total_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_network_label_up_total_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_network_label_up_total_unit, lv_color_hex(0xC5C5C5), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_network_label_up_total_unit, &lv_font_Inter_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_network_label_up_total_unit, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_network_label_up_total_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_network_label_up_total_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_network_label_up_total_unit, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_network_label_up_total_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_network_label_up_total_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_network_label_up_total_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_network_label_up_total_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_network_label_up_total_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_network_label_up_total_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_network_label_up_spd_unit
    ui->screen_network_label_up_spd_unit = lv_label_create(ui->screen_network_cont_SPEED);
    lv_label_set_text(ui->screen_network_label_up_spd_unit, "KB/s");
    lv_label_set_long_mode(ui->screen_network_label_up_spd_unit, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_network_label_up_spd_unit, 88, 16);
    lv_obj_set_size(ui->screen_network_label_up_spd_unit, 30, 12);

    //Write style for screen_network_label_up_spd_unit, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_network_label_up_spd_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_network_label_up_spd_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_network_label_up_spd_unit, lv_color_hex(0xC5C5C5), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_network_label_up_spd_unit, &lv_font_Inter_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_network_label_up_spd_unit, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_network_label_up_spd_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_network_label_up_spd_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_network_label_up_spd_unit, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_network_label_up_spd_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_network_label_up_spd_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_network_label_up_spd_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_network_label_up_spd_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_network_label_up_spd_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_network_label_up_spd_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_network_label_up_spd_val
    ui->screen_network_label_up_spd_val = lv_label_create(ui->screen_network_cont_SPEED);
    lv_label_set_text(ui->screen_network_label_up_spd_val, "0");
    lv_label_set_long_mode(ui->screen_network_label_up_spd_val, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_network_label_up_spd_val, 27, 14);
    lv_obj_set_size(ui->screen_network_label_up_spd_val, 55, 16);

    //Write style for screen_network_label_up_spd_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_network_label_up_spd_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_network_label_up_spd_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_network_label_up_spd_val, lv_color_hex(0x39c12c), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_network_label_up_spd_val, &lv_font_Inter_Bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_network_label_up_spd_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_network_label_up_spd_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_network_label_up_spd_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_network_label_up_spd_val, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_network_label_up_spd_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_network_label_up_spd_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_network_label_up_spd_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_network_label_up_spd_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_network_label_up_spd_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_network_label_up_spd_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_network_img_UP_LOGO
    ui->screen_network_img_UP_LOGO = lv_img_create(ui->screen_network_cont_SPEED);
    lv_obj_add_flag(ui->screen_network_img_UP_LOGO, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_network_img_UP_LOGO, &_upload_alpha_20x35);
    lv_img_set_pivot(ui->screen_network_img_UP_LOGO, 50,50);
    lv_img_set_angle(ui->screen_network_img_UP_LOGO, 0);
    lv_obj_set_pos(ui->screen_network_img_UP_LOGO, 4, 13);
    lv_obj_set_size(ui->screen_network_img_UP_LOGO, 20, 35);

    //Write style for screen_network_img_UP_LOGO, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_network_img_UP_LOGO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_network_img_UP_LOGO, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_network_img_UP_LOGO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_network_img_UP_LOGO, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_network_label_down_total_val
    ui->screen_network_label_down_total_val = lv_label_create(ui->screen_network_cont_SPEED);
    lv_label_set_text(ui->screen_network_label_down_total_val, "0");
    lv_label_set_long_mode(ui->screen_network_label_down_total_val, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_network_label_down_total_val, 42, 92);
    lv_obj_set_size(ui->screen_network_label_down_total_val, 40, 14);

    //Write style for screen_network_label_down_total_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_network_label_down_total_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_network_label_down_total_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_network_label_down_total_val, lv_color_hex(0x3f6db1), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_network_label_down_total_val, &lv_font_Inter_Bold_14, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_network_label_down_total_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_network_label_down_total_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_network_label_down_total_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_network_label_down_total_val, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_network_label_down_total_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_network_label_down_total_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_network_label_down_total_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_network_label_down_total_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_network_label_down_total_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_network_label_down_total_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_network_label_down_total_unit
    ui->screen_network_label_down_total_unit = lv_label_create(ui->screen_network_cont_SPEED);
    lv_label_set_text(ui->screen_network_label_down_total_unit, "KB");
    lv_label_set_long_mode(ui->screen_network_label_down_total_unit, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_network_label_down_total_unit, 88, 93);
    lv_obj_set_size(ui->screen_network_label_down_total_unit, 30, 12);

    //Write style for screen_network_label_down_total_unit, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_network_label_down_total_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_network_label_down_total_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_network_label_down_total_unit, lv_color_hex(0xC5C5C5), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_network_label_down_total_unit, &lv_font_Inter_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_network_label_down_total_unit, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_network_label_down_total_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_network_label_down_total_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_network_label_down_total_unit, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_network_label_down_total_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_network_label_down_total_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_network_label_down_total_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_network_label_down_total_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_network_label_down_total_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_network_label_down_total_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_network_label_down_spd_unit
    ui->screen_network_label_down_spd_unit = lv_label_create(ui->screen_network_cont_SPEED);
    lv_label_set_text(ui->screen_network_label_down_spd_unit, "KB/s");
    lv_label_set_long_mode(ui->screen_network_label_down_spd_unit, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_network_label_down_spd_unit, 88, 70);
    lv_obj_set_size(ui->screen_network_label_down_spd_unit, 30, 12);

    //Write style for screen_network_label_down_spd_unit, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_network_label_down_spd_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_network_label_down_spd_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_network_label_down_spd_unit, lv_color_hex(0xC5C5C5), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_network_label_down_spd_unit, &lv_font_Inter_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_network_label_down_spd_unit, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_network_label_down_spd_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_network_label_down_spd_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_network_label_down_spd_unit, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_network_label_down_spd_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_network_label_down_spd_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_network_label_down_spd_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_network_label_down_spd_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_network_label_down_spd_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_network_label_down_spd_unit, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_network_label_down_spd_val
    ui->screen_network_label_down_spd_val = lv_label_create(ui->screen_network_cont_SPEED);
    lv_label_set_text(ui->screen_network_label_down_spd_val, "0");
    lv_label_set_long_mode(ui->screen_network_label_down_spd_val, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_network_label_down_spd_val, 27, 69);
    lv_obj_set_size(ui->screen_network_label_down_spd_val, 55, 16);

    //Write style for screen_network_label_down_spd_val, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_network_label_down_spd_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_network_label_down_spd_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_network_label_down_spd_val, lv_color_hex(0x508fed), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_network_label_down_spd_val, &lv_font_Inter_Bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_network_label_down_spd_val, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_network_label_down_spd_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_network_label_down_spd_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_network_label_down_spd_val, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_network_label_down_spd_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_network_label_down_spd_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_network_label_down_spd_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_network_label_down_spd_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_network_label_down_spd_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_network_label_down_spd_val, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_network_img_DOWN_LOGO
    ui->screen_network_img_DOWN_LOGO = lv_img_create(ui->screen_network_cont_SPEED);
    lv_obj_add_flag(ui->screen_network_img_DOWN_LOGO, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_network_img_DOWN_LOGO, &_download_alpha_20x35);
    lv_img_set_pivot(ui->screen_network_img_DOWN_LOGO, 50,50);
    lv_img_set_angle(ui->screen_network_img_DOWN_LOGO, 0);
    lv_obj_set_pos(ui->screen_network_img_DOWN_LOGO, 4, 72);
    lv_obj_set_size(ui->screen_network_img_DOWN_LOGO, 20, 35);

    //Write style for screen_network_img_DOWN_LOGO, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_network_img_DOWN_LOGO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_network_img_DOWN_LOGO, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_network_img_DOWN_LOGO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_network_img_DOWN_LOGO, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_network_cont_ETH_NAME
    ui->screen_network_cont_ETH_NAME = lv_obj_create(ui->screen_network);
    lv_obj_set_pos(ui->screen_network_cont_ETH_NAME, 8, 10);
    lv_obj_set_size(ui->screen_network_cont_ETH_NAME, 150, 122);
    lv_obj_set_scrollbar_mode(ui->screen_network_cont_ETH_NAME, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_network_cont_ETH_NAME, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_network_cont_ETH_NAME, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_network_cont_ETH_NAME, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_network_cont_ETH_NAME, lv_color_hex(0xC9C9c9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_network_cont_ETH_NAME, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_network_cont_ETH_NAME, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_network_cont_ETH_NAME, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_network_cont_ETH_NAME, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_network_cont_ETH_NAME, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_network_cont_ETH_NAME, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_network_cont_ETH_NAME, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_network_cont_ETH_NAME, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_network_led_eth_state
    ui->screen_network_led_eth_state = lv_led_create(ui->screen_network_cont_ETH_NAME);
    lv_led_set_brightness(ui->screen_network_led_eth_state, 255);
    lv_led_set_color(ui->screen_network_led_eth_state, lv_color_hex(0x2FDA64));
    lv_obj_set_pos(ui->screen_network_led_eth_state, 18, 74);
    lv_obj_set_size(ui->screen_network_led_eth_state, 13, 13);

    //Write codes screen_network_label_eth_state
    ui->screen_network_label_eth_state = lv_label_create(ui->screen_network_cont_ETH_NAME);
    lv_label_set_text(ui->screen_network_label_eth_state, "DISCONNECTED");
    lv_label_set_long_mode(ui->screen_network_label_eth_state, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_network_label_eth_state, 41, 75);
    lv_obj_set_size(ui->screen_network_label_eth_state, 100, 12);

    //Write style for screen_network_label_eth_state, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_network_label_eth_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_network_label_eth_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_network_label_eth_state, lv_color_hex(0x2FDA64), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_network_label_eth_state, &lv_font_Inter_Bold_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_network_label_eth_state, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_network_label_eth_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_network_label_eth_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_network_label_eth_state, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_network_label_eth_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_network_label_eth_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_network_label_eth_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_network_label_eth_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_network_label_eth_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_network_label_eth_state, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_network_label_eth_name
    ui->screen_network_label_eth_name = lv_label_create(ui->screen_network_cont_ETH_NAME);
    lv_label_set_text(ui->screen_network_label_eth_name, "enp1s0");
    lv_label_set_long_mode(ui->screen_network_label_eth_name, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_network_label_eth_name, 52, 21);
    lv_obj_set_size(ui->screen_network_label_eth_name, 80, 16);

    //Write style for screen_network_label_eth_name, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_network_label_eth_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_network_label_eth_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_network_label_eth_name, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_network_label_eth_name, &lv_font_Inter_Bold_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_network_label_eth_name, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_network_label_eth_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_network_label_eth_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_network_label_eth_name, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_network_label_eth_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_network_label_eth_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_network_label_eth_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_network_label_eth_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_network_label_eth_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_network_label_eth_name, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_network_img_ETH_LOGO
    ui->screen_network_img_ETH_LOGO = lv_img_create(ui->screen_network_cont_ETH_NAME);
    lv_obj_add_flag(ui->screen_network_img_ETH_LOGO, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_network_img_ETH_LOGO, &_network_green_alpha_35x35);
    lv_img_set_pivot(ui->screen_network_img_ETH_LOGO, 50,50);
    lv_img_set_angle(ui->screen_network_img_ETH_LOGO, 0);
    lv_obj_set_pos(ui->screen_network_img_ETH_LOGO, 8, 21);
    lv_obj_set_size(ui->screen_network_img_ETH_LOGO, 35, 35);

    //Write style for screen_network_img_ETH_LOGO, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_network_img_ETH_LOGO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_network_img_ETH_LOGO, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_network_img_ETH_LOGO, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_network_img_ETH_LOGO, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_network_label_eth_idx
    ui->screen_network_label_eth_idx = lv_label_create(ui->screen_network_cont_ETH_NAME);
    lv_label_set_text(ui->screen_network_label_eth_idx, "Ethernet 1 of 2");
    lv_label_set_long_mode(ui->screen_network_label_eth_idx, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_network_label_eth_idx, 52, 43);
    lv_obj_set_size(ui->screen_network_label_eth_idx, 90, 12);

    //Write style for screen_network_label_eth_idx, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_network_label_eth_idx, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_network_label_eth_idx, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_network_label_eth_idx, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_network_label_eth_idx, &lv_font_Inter_Regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_network_label_eth_idx, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_network_label_eth_idx, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_network_label_eth_idx, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_network_label_eth_idx, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_network_label_eth_idx, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_network_label_eth_idx, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_network_label_eth_idx, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_network_label_eth_idx, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_network_label_eth_idx, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_network_label_eth_idx, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_network_label_indicator1
    ui->screen_network_label_indicator1 = lv_label_create(ui->screen_network);
    lv_label_set_text(ui->screen_network_label_indicator1, "");
    lv_label_set_long_mode(ui->screen_network_label_indicator1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_network_label_indicator1, 418, 42);
    lv_obj_set_size(ui->screen_network_label_indicator1, 6, 6);

    //Write style for screen_network_label_indicator1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_network_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_network_label_indicator1, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_network_label_indicator1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_network_label_indicator1, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_network_label_indicator1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_network_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_network_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_network_label_indicator1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_network_label_indicator1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_network_label_indicator1, lv_color_hex(0xbcbcbc), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_network_label_indicator1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_network_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_network_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_network_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_network_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_network_label_indicator1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_network_label_indicator2
    ui->screen_network_label_indicator2 = lv_label_create(ui->screen_network);
    lv_label_set_text(ui->screen_network_label_indicator2, "");
    lv_label_set_long_mode(ui->screen_network_label_indicator2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_network_label_indicator2, 416, 54);
    lv_obj_set_size(ui->screen_network_label_indicator2, 10, 10);

    //Write style for screen_network_label_indicator2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_network_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_network_label_indicator2, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_network_label_indicator2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_network_label_indicator2, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_network_label_indicator2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_network_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_network_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_network_label_indicator2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_network_label_indicator2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_network_label_indicator2, lv_color_hex(0x51a8f9), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_network_label_indicator2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_network_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_network_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_network_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_network_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_network_label_indicator2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_network_label_indicator3
    ui->screen_network_label_indicator3 = lv_label_create(ui->screen_network);
    lv_label_set_text(ui->screen_network_label_indicator3, "");
    lv_label_set_long_mode(ui->screen_network_label_indicator3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_network_label_indicator3, 418, 70);
    lv_obj_set_size(ui->screen_network_label_indicator3, 6, 6);

    //Write style for screen_network_label_indicator3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_network_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_network_label_indicator3, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_network_label_indicator3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_network_label_indicator3, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_network_label_indicator3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_network_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_network_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_network_label_indicator3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_network_label_indicator3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_network_label_indicator3, lv_color_hex(0xbcbcbc), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_network_label_indicator3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_network_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_network_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_network_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_network_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_network_label_indicator3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_network_label_indicator4
    ui->screen_network_label_indicator4 = lv_label_create(ui->screen_network);
    lv_label_set_text(ui->screen_network_label_indicator4, "");
    lv_label_set_long_mode(ui->screen_network_label_indicator4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_network_label_indicator4, 418, 82);
    lv_obj_set_size(ui->screen_network_label_indicator4, 6, 6);

    //Write style for screen_network_label_indicator4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_network_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_network_label_indicator4, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_network_label_indicator4, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_network_label_indicator4, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_network_label_indicator4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_network_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_network_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_network_label_indicator4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_network_label_indicator4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_network_label_indicator4, lv_color_hex(0xbcbcbc), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_network_label_indicator4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_network_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_network_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_network_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_network_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_network_label_indicator4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_network_label_indicator5
    ui->screen_network_label_indicator5 = lv_label_create(ui->screen_network);
    lv_label_set_text(ui->screen_network_label_indicator5, "");
    lv_label_set_long_mode(ui->screen_network_label_indicator5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_network_label_indicator5, 418, 94);
    lv_obj_set_size(ui->screen_network_label_indicator5, 6, 6);

    //Write style for screen_network_label_indicator5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_network_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_network_label_indicator5, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_network_label_indicator5, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_network_label_indicator5, &lv_font_Inter_Regular_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_network_label_indicator5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_network_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_network_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_network_label_indicator5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_network_label_indicator5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_network_label_indicator5, lv_color_hex(0xbcbcbc), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_network_label_indicator5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_network_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_network_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_network_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_network_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_network_label_indicator5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_network.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_network);

}
