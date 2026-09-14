/**
 * Copyright (c) 2026, Deadline039
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef FAN_CONTROL_H
#define FAN_CONTROL_H

#include <stdint.h>

uint8_t fan_ctrl_percent(uint8_t temperature);
void fan_ctrl_init(void);

#endif /* FAN_CONTROL_H */
