/**
* Copyright (c) 2026, Deadline039
 *
 * SPDX-License-Identifier: MIT
 */

#include "gd32f30x.h"
#include "delay.h"

volatile static uint32_t tick_cnt = 0;

/**
 * @brief configure systick
 */
void systick_config(void)
{
    /* setup systick timer for 1000Hz interrupts */
    if (SysTick_Config(SystemCoreClock / 1000U)) {
        /* capture error */
        while (1) {
        }
    }
    /* configure the systick handler priority */
    NVIC_SetPriority(SysTick_IRQn, 0x00U);
}

/**
 * @brief Increment tick counter
 */
void systick_inc(void)
{
    tick_cnt++;
}

/**
 * @brief Get tick counter
 * @return tick counter
 */
uint32_t systick_get(void)
{
    return tick_cnt;
}

/**
 * @brief Initialize delay using DWT
 */
void delay_init(void)
{
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CYCCNT = 0;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

/**
 * @brief delay a time in milliseconds
 * @param count count in milliseconds
 */
void delay_ms(uint32_t count)
{
    while (count--) {
        delay_us(1000);
    }
}

/**
 * @brief delay a time in microseconds
 * @param count count in microseconds
 */
void delay_us(uint32_t count)
{
    uint32_t start = DWT->CYCCNT;

    uint32_t ticks = count * (SystemCoreClock / 1000000);

    while ((DWT->CYCCNT - start) < ticks) {
    }
}
