/**
 * Copyright (c) 2026, Deadline039
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef USB_INFO_H
#define USB_INFO_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define NETWORK_DISCONNECTED    0U
#define NETWORK_GETTING_ADDRESS 1U
#define NETWORK_CONNECTED       2U

#define DISK_STATUS_OK          0
#define DISK_STATUS_WARNING     1
#define DISK_STATUS_ERROR       2

typedef struct __attribute__((packed)) {
    uint8_t page;          /**< which page is in shown? */
    float voltage;         /**< voltage (Unit: V) */
    float current;         /**< current (Unit: A) */
    uint8_t cpu_fan_speed; /**< Local CPU fan PWM percentage. */
    uint8_t hdd_fan_speed; /**< Local disk fan PWM percentage. */
    uint8_t item_idx;      /**< Zero-based item selected by the panel. */
} usb_data_report_t;

typedef struct __attribute__((packed)) {
    /**< frame type, 0:page data, 1:setting */
    uint8_t type;
    /**<
     * frame valid flag, 0:invalid, 1: valid
     * It will set to invalid when USB disconnected,
     * and it's always valid in USB response
     */
    uint8_t valid;
    /**< page index, or setting item index */
    uint8_t page_set;
    uint8_t cpu_temperature; /**< CPU temperature in degrees Celsius. */
    uint8_t hdd_temperature; /**< Highest disk temperature in degrees Celsius. */
    /**< Convert to the matching usb_data_xxx_t by page, or parsing in setting */
    void *data;
} usb_data_resp_t;

typedef struct __attribute__((packed)) {
    uint32_t running_time; /**< Runtime in minute. */
    uint8_t cpu_load;
    uint8_t mem_load;
} usb_data_overview_t;

typedef struct __attribute__((packed)) {
    uint8_t idx;
    uint8_t total;
    uint8_t status; /**< Network status */
    char name[12];

    float up_rate;
    float up_total;
    float down_rate;
    float down_total;

    char ip_addr[16];
    char netmask[16];
    char gateway[16];
} usb_data_network_t;

typedef struct __attribute__((packed)) {
    uint8_t idx;
    uint8_t total;
    char path[12];

    uint64_t capacity; /**< Capacity in bytes. */
    uint8_t used;

    uint8_t status;
    uint8_t temperature;
    uint32_t time;
    uint32_t cycles;
} usb_data_disk_t;

typedef struct __attribute__((packed)) {
    char name[12];
    char os_name[80];
    char cpu_name[50];
    char mem_name[50];
} usb_data_sys_info_t;

typedef struct __attribute__((packed)) {
    uint8_t idx;
    uint8_t total;

    char web_addr[50];
    char server_version[10];
} usb_data_about_qrcode_t;

/* `page` and `item_idx` set by UI */
extern usb_data_report_t g_usb_data_report;
extern usb_data_resp_t g_usb_data_resp;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* USB_INFO_H */
