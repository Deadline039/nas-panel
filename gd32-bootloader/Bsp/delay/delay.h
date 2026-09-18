/**
* Copyright (c) 2026, Deadline039
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __DELAY_H
#define __DELAY_H

#include <stdint.h>

#define DELAY_MAX_MS UINT32_MAX

void systick_config(void);
void systick_inc(void);
uint32_t systick_get(void);

void delay_init(void);
void delay_ms(uint32_t count);
void delay_us(uint32_t count);

#endif /* __DELAY_H */