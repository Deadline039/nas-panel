/**
 * Copyright (c) 2026, Deadline039
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef USB_INFO_H
#define USB_INFO_H
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define DISK_STATUS_OK      0
#define DISK_STATUS_WARNING 1
#define DISK_STATUS_ERROR   2

typedef struct __attribute__((packed)) {
    uint8_t page;  /** which page is in shown? */
    float voltage; /** voltage */
    float current; /** current */
} udata_report_t;

typedef struct __attribute__((packed)) {
    char running_time[10];
    uint8_t cpu_load;
    uint8_t mem_load;
} udata_overview_t;

typedef struct __attribute__((packed)) {
    uint8_t idx;
    uint8_t total;
    char name[12];

    float up_rate;
    float up_total;
    float down_rate;
    float down_total;

    char ip_addr[16];
    char netmask[16];
    char gateway[16];
} udata_network_t;

typedef struct __attribute__((packed)) {
    uint8_t idx;
    uint8_t total;
    char path[12];

    uint32_t capacity;
    uint8_t used;

    uint8_t status;
    uint8_t temperature;
    uint32_t time;
    uint32_t cycles;
} udata_disk_t;

typedef struct __attribute__((packed)) {
    char name[12];
    char os_name[80];
    char cpu_name[50];
    char mem_name[50];

    uint8_t cpu_temperature;
    uint8_t cpu_fan_speed;
    uint8_t hdd_fan_speed;
} udata_sys_info_t;

typedef struct __attribute__((packed)) {
    uint8_t idx;
    uint8_t total;

    char web_addr[50];
    char server_version[10];
} udata_server_info_t;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* USB_INFO_H */
