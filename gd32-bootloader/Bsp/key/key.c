/**
 * Copyright (c) 2026, Deadline039
 *
 * SPDX-License-Identifier: MIT
 */

#include "key.h"

#include "delay/delay.h"
#include <gd32f30x_rcu.h>
#include <gd32f30x_gpio.h>

#define UP_KEY_PORT       GPIOB
#define UP_KEY_PIN        GPIO_PIN_3

#define DOWN_KEY_PORT     GPIOB
#define DOWN_KEY_PIN      GPIO_PIN_4

#define KEY_LONG_PRESS_MS 3000U

/**
 * @brief initialize key and power state detect
 */
void key_init(void)
{
    rcu_periph_clock_enable(RCU_GPIOB);
    gpio_pin_remap_config(GPIO_SWJ_SWDPENABLE_REMAP, ENABLE);

    gpio_init(UP_KEY_PORT, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_2MHZ, UP_KEY_PIN);
    gpio_init(DOWN_KEY_PORT, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_2MHZ, DOWN_KEY_PIN);
}

bool key_enter_bootloader(void)
{
    uint32_t start_tick = systick_get();
    while (gpio_input_bit_get(UP_KEY_PORT, UP_KEY_PIN) == RESET &&
           gpio_input_bit_get(DOWN_KEY_PORT, DOWN_KEY_PIN) == RESET) {
        if (systick_get() - start_tick > KEY_LONG_PRESS_MS) {
            return true;
        }
    }
    return false;
}
