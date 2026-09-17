/**
 * Copyright (c) 2026, Deadline039
 *
 * SPDX-License-Identifier: MIT
 */

#include "bootloader.h"
#include "dfu_core.h"
#include "usbd_hw.h"
#include "usbd_lld_int.h"

#include "delay/delay.h"
#include "fan_pwm/fan_pwm.h"
#include "lcd/lcd.h"
#include "key/key.h"

usb_dev usb_dfu;

/**
 * @brief Start the application or expose the USB DFU updater.
 * @return Does not return during normal operation.
 */
int main(void)
{
    nvic_priority_group_set(NVIC_PRIGROUP_PRE4_SUB0);
    if (bootloader_should_start_application() == true &&
        key_enter_bootloader() == true) {
        bootloader_start_application();
    }

    delay_init();
    systick_config();
    fan_full_speed_init();
    rcu_config();
    gpio_config();
    usbd_init(&usb_dfu, &dfu_desc, &dfu_class);
    nvic_config();
    usbd_connect(&usb_dfu);
    lcd_init();
    bootloader_update_reset();
    bootloader_update_show_waiting();

    while (true) {
        bootloader_update_poll();
    }
}
