/**
 * Copyright (c) 2026, Deadline039
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef FAN_PWM_H
#define FAN_PWM_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void fan_pwm_init(void);

void fan_hdd_set(uint8_t percent);
void fan_cpu_set(uint8_t percent);

uint8_t fan_cpu_get_percent(void);
uint8_t fan_hdd_get_percent(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* FAN_PWM_H */
