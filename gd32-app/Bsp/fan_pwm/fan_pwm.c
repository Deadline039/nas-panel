/**
 * Copyright (c) 2026, Deadline039
 *
 * SPDX-License-Identifier: MIT
 */

#include "fan_pwm.h"

#include <gd32f30x_rcu.h>
#include <gd32f30x_gpio.h>
#include <gd32f30x_timer.h>

void fan_pwm_init(void)
{
    timer_oc_parameter_struct timer_ocintpara;
    timer_parameter_struct timer_initpara;

    rcu_periph_clock_enable(RCU_GPIOB);
    gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_8 | GPIO_PIN_9);

    rcu_periph_clock_enable(RCU_TIMER3);
    timer_deinit(TIMER3);

    timer_initpara.prescaler = 47;
    timer_initpara.alignedmode = TIMER_COUNTER_EDGE;
    timer_initpara.counterdirection = TIMER_COUNTER_UP;
    timer_initpara.period = 100;
    timer_initpara.clockdivision = TIMER_CKDIV_DIV1;
    timer_initpara.repetitioncounter = 0;
    timer_init(TIMER3, &timer_initpara);

    timer_ocintpara.outputstate = TIMER_CCX_ENABLE;
    timer_ocintpara.outputnstate = TIMER_CCXN_DISABLE;
    timer_ocintpara.ocpolarity = TIMER_OC_POLARITY_HIGH;
    timer_ocintpara.ocnpolarity = TIMER_OCN_POLARITY_HIGH;
    timer_ocintpara.ocidlestate = TIMER_OC_IDLE_STATE_LOW;
    timer_ocintpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;

    timer_channel_output_config(TIMER3, TIMER_CH_2, &timer_ocintpara);
    timer_channel_output_pulse_value_config(TIMER3, TIMER_CH_2, 0);
    timer_channel_output_mode_config(TIMER3, TIMER_CH_2, TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER3, TIMER_CH_2, TIMER_OC_SHADOW_DISABLE);

    timer_channel_output_config(TIMER3, TIMER_CH_3, &timer_ocintpara);
    timer_channel_output_pulse_value_config(TIMER3, TIMER_CH_3, 0);
    timer_channel_output_mode_config(TIMER3, TIMER_CH_3, TIMER_OC_MODE_PWM0);
    timer_channel_output_shadow_config(TIMER3, TIMER_CH_3, TIMER_OC_SHADOW_DISABLE);

    timer_auto_reload_shadow_enable(TIMER3);
    timer_enable(TIMER3);
}

void fan_hdd_set(uint32_t precent)
{
    timer_channel_output_pulse_value_config(TIMER3, TIMER_CH_2, precent);
}

void fan_cpu_set(uint32_t precent)
{
    timer_channel_output_pulse_value_config(TIMER3, TIMER_CH_3, precent);
}
