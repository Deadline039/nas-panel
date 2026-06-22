/*
 * Copyright 2023 NXP
 * NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
 * accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
 * terms, then you may not retain, install, activate or otherwise use the software.
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "lvgl.h"
#include "custom.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**
 * Create a demo application
 */
void custom_init(lv_ui *ui)
{
    /* Add your codes here */
}

typedef struct {
    lv_obj_t **scr;           /** screen object */
    bool *scr_del;            /** screen deleted flag */
    ui_setup_scr_t setup_scr; /** setup screen function */
} screen_param_t;

static const screen_param_t screen_param_table[LV_SCREEN_RESERVE] = {
    [LV_SCREEN_OVERVIEW] = { &guider_ui.screen_overview, &guider_ui.screen_overview_del, setup_scr_screen_overview },
    [LV_SCREEN_NETWORK] = { &guider_ui.screen_network, &guider_ui.screen_network_del, setup_scr_screen_network },
    [LV_SCREEN_STORAGE] = { &guider_ui.screen_storage, &guider_ui.screen_storage_del, setup_scr_screen_storage },
    [LV_SCREEN_SYS_INFO] = { &guider_ui.screen_sys_info, &guider_ui.screen_sys_info_del, setup_scr_screen_sys_info },
    [LV_SCREEN_ABOUT_QRCODE] = { &guider_ui.screen_about_qrcode, &guider_ui.screen_about_qrcode_del, setup_scr_screen_about_qrcode },
};

void lv_ui_change_screen(lv_ui_screen_t old_scr, lv_ui_screen_t new_scr)
{
    ui_load_scr_animation(&guider_ui,
                          screen_param_table[new_scr].scr,
                          *screen_param_table[new_scr].scr_del,
                          screen_param_table[old_scr].scr_del,
                          screen_param_table[new_scr].setup_scr,
                          LV_SCR_LOAD_ANIM_NONE,
                          0,
                          0,
                          false,
                          true);
}
