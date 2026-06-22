/**
 * Copyright (c) 2026, Deadline039
 *
 * SPDX-License-Identifier: MIT
 */

#include <gd32f30x.h>
#include <bsp.h>

extern void rtos_start(void);

/**
 * @brief main function
 * @return None
 */
int main(void)
{
    nvic_priority_group_set(NVIC_PRIGROUP_PRE4_SUB0);
    systick_config();
    delay_init();
    usart0_init();
    fan_pwm_init();

    ina219_dev_init();
    hc595_init();

    rtos_start();

    return 0;
}
