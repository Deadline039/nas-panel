/**
 * Copyright (c) 2026, Deadline039
 *
 * SPDX-License-Identifier: MIT
 */

#include "key.h"

#include "delay/delay.h"
#include <gd32f30x_rcu.h>
#include <gd32f30x_gpio.h>

#define UP_KEY_PORT     GPIOB
#define UP_KEY_PIN      GPIO_PIN_3

#define DOWN_KEY_PORT   GPIOB
#define DOWN_KEY_PIN    GPIO_PIN_4

#define PWR_STATE_PORT  GPIOB
#define PWR_STATE_PIN   GPIO_PIN_11

#define KEY_DEBOUNCE_MS 10

typedef struct
{
    uint8_t state;        /** current state */
    uint8_t last_raw;     /** last state */
    uint32_t change_tick; /** GPIO changed tick */
    uint16_t debounce_ms; /** debounce times */
    uint8_t trigger;      /** triggered flag */
} gpio_scan_t;

static void gpio_scan_update(gpio_scan_t *obj,
                             uint8_t raw_state,
                             uint32_t tick)
{
    obj->trigger = 0;

    if (raw_state != obj->last_raw) {
        obj->last_raw = raw_state;
        obj->change_tick = tick;
    }

    if ((tick - obj->change_tick) >= obj->debounce_ms) {
        if (obj->state != raw_state) {
            obj->state = raw_state;
            if (raw_state == 0) {
                obj->trigger = 1;
            }
        }
    }
}

static gpio_scan_t s_key_scan[2];

/**
 * @brief initialize key and power state detect
 */
void key_init(void)
{
    rcu_periph_clock_enable(RCU_GPIOB);
    gpio_pin_remap_config(GPIO_SWJ_SWDPENABLE_REMAP, ENABLE);

    gpio_init(UP_KEY_PORT, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_2MHZ, UP_KEY_PIN);
    gpio_init(DOWN_KEY_PORT, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_2MHZ, DOWN_KEY_PIN);
    gpio_init(PWR_STATE_PORT, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_2MHZ, PWR_STATE_PIN);
    s_key_scan[0].debounce_ms = KEY_DEBOUNCE_MS;
    s_key_scan[1].debounce_ms = KEY_DEBOUNCE_MS;
}

/**
 * @brief get UP key state
 * @return UP key state
 *  @retval true pressed
 *  @retval false not press
 */
bool key_up_get(void)
{
    gpio_scan_update(&s_key_scan[0], gpio_input_bit_get(UP_KEY_PORT, UP_KEY_PIN), systick_get());
    return s_key_scan[0].trigger;
}

/**
 * @brief get DOWN key state
 * @return DOWN key state
 *  @retval true pressed
 *  @retval false not press
 */
bool key_down_get(void)
{
    gpio_scan_update(&s_key_scan[1], gpio_input_bit_get(DOWN_KEY_PORT, DOWN_KEY_PIN), systick_get());
    return s_key_scan[1].trigger;
}

/**
 * @brief get power state
 * @return power state
 *  @retval true Power ON
 *  @retval false Power OFF
 */
bool pwr_get_state(void)
{
    return (SET == gpio_input_bit_get(PWR_STATE_PORT, PWR_STATE_PIN)) ? true : false;
}
