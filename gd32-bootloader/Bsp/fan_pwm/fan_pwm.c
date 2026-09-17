/**
 * Copyright (c) 2026, Deadline039
 *
 * SPDX-License-Identifier: MIT
 */

#include "fan_pwm.h"
#include <gd32f30x.h>

/**
 * @brief Hold both fan control pins high for a continuous 100 percent duty cycle.
 */
void fan_full_speed_init(void)
{
    rcu_periph_clock_enable(RCU_GPIOB);
    gpio_bit_set(GPIOB, GPIO_PIN_8 | GPIO_PIN_9);
    gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_8 | GPIO_PIN_9);
}
