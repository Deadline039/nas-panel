/**
 * Copyright (c) 2026, Deadline039
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef UI_SCR_UPDATE_H
#define UI_SCR_UPDATE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief Clear USB values and show that the current page is waiting for data.
 * @param page Current screen identifier.
 */
void update_scr_loading(uint8_t page);

void update_scr_overview(void);
void update_scr_network(void);
void update_scr_sys_info(void);
void update_scr_storage(void);
void update_scr_about_qrcode(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* UI_SCR_UPDATE_H */
