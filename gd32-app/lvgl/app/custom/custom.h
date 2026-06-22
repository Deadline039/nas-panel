/*
 * Copyright 2023 NXP
 * NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
 * accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
 * terms, then you may not retain, install, activate or otherwise use the software.
 */

#ifndef __CUSTOM_H_
#define __CUSTOM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"

typedef enum {
    LV_SCREEN_OVERVIEW = 0,
    LV_SCREEN_NETWORK,
    LV_SCREEN_STORAGE,
    LV_SCREEN_SYS_INFO,
    LV_SCREEN_ABOUT_QRCODE,
    LV_SCREEN_RESERVE
} lv_ui_screen_t;

void custom_init(lv_ui *ui);
void lv_ui_change_screen(lv_ui_screen_t old_scr, lv_ui_screen_t new_scr);

#ifdef __cplusplus
}
#endif
#endif /* __CUSTOM_H_ */
