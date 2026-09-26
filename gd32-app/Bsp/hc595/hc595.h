/**
 * Copyright (c) 2026, Deadline039
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef HC595_H
#define HC595_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void hc595_init(void);
void hc595_send_byte(uint8_t byte);
void hc595_set_led(uint8_t pos, uint8_t color0, uint8_t color1);
void hc595_set_led_off(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* HC595_H */
