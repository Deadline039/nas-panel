/**
 * Copyright (c) 2026, Deadline039
 *
 * SPDX-License-Identifier: MIT
 */

#include "bootloader.h"

#include <gd32f30x.h>

/**
 * @brief Enter the USB bootloader after the next reset.
 */
void bootloader_request_update(void)
{
    rcu_periph_clock_enable(RCU_PMU);
    rcu_periph_clock_enable(RCU_BKPI);
    pmu_backup_write_enable();
    bkp_write_data(BKP_DATA_0, 0xB007U);
    __DSB();
    NVIC_SystemReset();
}
