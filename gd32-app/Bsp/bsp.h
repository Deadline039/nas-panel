/**
 * Copyright (c) 2026, Deadline039
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BSP_H
#define BSP_H

#include <stdint.h>
#include "gd32f30x_libopt.h"

#include "delay/delay.h"
#include "ina219/ina219.h"
#include "lcd/lcd.h"
#include "usart/usart.h"
#include "hc595/hc595.h"
#include "fan_pwm/fan_pwm.h"
#include "key/key.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern ina219_handle_t *p_ina219_handle;
void ina219_dev_init(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* BSP_H */
