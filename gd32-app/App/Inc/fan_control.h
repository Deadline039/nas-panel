/**
 * Copyright (c) 2026, Deadline039
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef FAN_CONTROL_H
#define FAN_CONTROL_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define FAN_CURVE_POINTS          20U
#define FAN_CURVE_COUNT           2U
#define FAN_CURVE_BYTES           (FAN_CURVE_POINTS * FAN_CURVE_COUNT)
#define FAN_CURVE_MIN_TEMPERATURE 25U
#define FAN_CURVE_MAX_TEMPERATURE 100U

/**
 * @brief Validate, persist, and activate CPU and HDD fan curves.
 * @param curves Raw CPU curve followed by the raw HDD curve.
 * @param length Curve data length in bytes.
 * @return True when the curves are valid and stored successfully.
 */
bool fan_ctrl_set_curves(const uint8_t *curves, size_t length);

/**
 * @brief Load stored fan curves and create the control task.
 */
void fan_ctrl_init(void);

#endif /* FAN_CONTROL_H */
