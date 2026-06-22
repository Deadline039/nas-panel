/**
 * Copyright (c) 2026, Deadline039
 *
 * SPDX-License-Identifier: MIT
 */

#include <FreeRTOS.h>
#include <task.h>

#include <bsp.h>

#include <custom_hid_core.h>
#include <usbd_hw.h>

usb_dev usbd_custom_hid;

TaskHandle_t usb_task_handle;

__NO_RETURN void usb_task(void *args)
{
    usb_rcu_config();
    usb_gpio_config();
    custom_hid_itfop_register(&usbd_custom_hid, NULL);
    usbd_init(&usbd_custom_hid, &custom_hid_desc, &custom_hid_class);
    usb_nvic_config();
    uint32_t pulse = 0;

    usbd_connect(&usbd_custom_hid);

    while (1) {
        fan_cpu_set(50);
        fan_hdd_set(50);
        vTaskDelay(3000);
        fan_cpu_set(100);
        fan_hdd_set(100);
        vTaskDelay(3000);
    }
}
