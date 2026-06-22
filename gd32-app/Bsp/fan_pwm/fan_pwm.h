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

void fan_hdd_set(uint32_t precent);
void fan_cpu_set(uint32_t precent);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* FAN_PWM_H */
