/**
 * Copyright (c) 2026, Deadline039
 * SPDX-License-Identifier: MIT
 */

#include <FreeRTOS.h>
#include <task.h>
#include <string.h>

#include <bsp.h>
#include <custom_hid_core.h>
#include <usbd_hw.h>

#include <usb_data.h>

#include <custom.h>

#define REPORT_REQUEST_PERIOD_MS   pdMS_TO_TICKS(1000U)
#define REPORT_RESPONSE_TIMEOUT_MS pdMS_TO_TICKS(1000U)
#define POWER_SAMPLE_PERIOD_MS     pdMS_TO_TICKS(100U)

usb_dev usbd_custom_hid;
TaskHandle_t usb_task_handle;

static uint8_t calc_crc8(uint8_t *p, uint8_t len);

#if 0
/**
 * @brief Validate reply identity, size, and values before updating the snapshot.
 * @param frame Complete reply.
 * @param page Requested page.
 * @param item_idx Requested item index.
 * @param sequence Request sequence number.
 * @param data Snapshot to update.
 * @return True on success, or false for an invalid reply.
 */
bool usb_data_accept_response(const usb_data_frame_t *frame, uint8_t page,
                           uint8_t item_idx, uint32_t sequence, usb_data_shared_t *data)
{
    if (frame == NULL || data == NULL || page >= UDATA_PAGE_COUNT) {
        return false;
    }
    if (frame->version != UDATA_PROTOCOL_VERSION || frame->type != UDATA_RESPONSE ||
        frame->reserved != 0 || frame->page != page || frame->sequence != sequence ||
        frame->length != usb_data_response_size(page)) {
        return false;
    }
    const usb_data_resp_t *reply = (const void *)frame->payload;
    void *response = usb_data_response_data(data, page);
    if (response == NULL || reply->page != page) {
        return false;
    }
    switch (page) {
        case UDATA_PAGE_OVERVIEW: {
            const usb_data_overview_t *value = (const void *)reply->data;
            if (value->cpu_load > 100 || value->mem_load > 100) {
                return false;
            }
            break;
        }
        case UDATA_PAGE_NETWORK: {
            const usb_data_network_t *value = (const void *)reply->data;
            if (value->idx != item_idx) {
                return false;
            }
            if (value->status > NETWORK_CONNECTED) {
                return false;
            }
            /* Check raw bits so fast-math cannot discard NaN and infinity validation. */
            for (size_t offset = 17; offset < 33; offset += sizeof(uint32_t)) {
                uint32_t bits;
                memcpy(&bits, frame->payload + offset, sizeof(bits));
                if ((bits & 0x7f800000U) == 0x7f800000U || (bits & 0x80000000U) != 0) {
                    return false;
                }
            }
            break;
        }
        case UDATA_PAGE_STORAGE: {
            const usb_data_disk_t *value = (const void *)reply->data;
            if (value->used > 100 || value->status > DISK_STATUS_ERROR ||
                value->idx != item_idx) {
                return false;
            }
            break;
        }
        case UDATA_PAGE_SYS_INFO: {
            break;
        }
        case UDATA_PAGE_SERVER_INFO: {
            const usb_data_about_qrcode_t *value = (const void *)reply->data;
            if (value->idx != item_idx) {
                return false;
            }
            break;
        }
        default:
            return false;
    }
    memcpy(response, reply->data, usb_data_response_size(page) - sizeof(usb_data_resp_t));
    data->reply = *reply;
    data->valid[page] = true;
    data->online = true;
    return true;
}
#else

void usb_data_check(usb_data_frame_t *frame, TickType_t *resp_tick, uint32_t sequence)
{
    if (frame->version > USB_DATA_PROTOCOL_VERSION) {
        return;
    }
    if (frame->type != USB_DATA_TYPE_RESPONSE) {
        return;
    }
    if (frame->sequence != sequence) {
        return;
    }
    if (frame->length > sizeof(frame->payload)) {
        return;
    }
    if (calc_crc8(frame->payload, frame->length) != frame->crc8) {
        return;
    }

    usb_data_resp_t *resp = (usb_data_resp_t *)frame->payload;

    if (resp->type == 0 && resp->page_set != g_usb_data_report.page) {
        return;
    }
    memcpy(&g_usb_data_resp, resp, sizeof(usb_data_resp_t));
    g_usb_data_resp.data = (void *)((uint8_t *)resp + offsetof(usb_data_resp_t, data));

    *resp_tick = xTaskGetTickCount();
}

#endif

/**
 * @brief Sample voltage, current and FAN PWM percent in the USB task.
 * @param report Request data to update.
 */
static void sample_power_fan(usb_data_report_t *report)
{
    uint16_t voltage_raw;
    int16_t current_raw;
    float voltage;
    float current;
    if (ina219_read_bus_voltage(p_ina219_handle, &voltage_raw, &voltage) == 0) {
        report->voltage = voltage / 1000.0f;
    }
    if (ina219_read_current(p_ina219_handle, &current_raw, &current) == 0) {
        report->current = current / 1000.0f;
    }
    report->cpu_fan_speed = fan_cpu_get_percent();
    report->hdd_fan_speed = fan_hdd_get_percent();
}

/**
 * @brief Request page data every second and publish matching replies to the UI task.
 * @param args Unused task argument.
 */
__NO_RETURN void usb_task(void *args)
{
    (void)args;

    static usb_data_frame_t tx_frame;
    static usb_data_frame_t rx_frame;

    tx_frame.version = USB_DATA_PROTOCOL_VERSION;
    tx_frame.type = USB_DATA_TYPE_REQUEST;
    tx_frame.length = sizeof(usb_data_report_t);

    usb_rcu_config();
    usb_gpio_config();
    usbd_init(&usbd_custom_hid, &custom_hid_desc, &custom_hid_class);
    usb_nvic_config();
    usbd_connect(&usbd_custom_hid);

    TickType_t last_tick = xTaskGetTickCount();
    TickType_t last_request = xTaskGetTickCount();
    TickType_t last_response = xTaskGetTickCount();
    TickType_t last_power_sample = xTaskGetTickCount();

    while (1) {
        TickType_t now = xTaskGetTickCount();
        if (now - last_power_sample > POWER_SAMPLE_PERIOD_MS) {
            sample_power_fan(&g_usb_data_report);
            last_power_sample = now;
        }

        if (usbd_custom_hid.cur_status != USBD_CONFIGURED) {
            g_usb_data_resp.valid = 0;
            /* reset to 0 when disconnect */
            tx_frame.sequence = 0;
            vTaskDelayUntil(&last_tick, pdMS_TO_TICKS(10));
            continue;
        }

        taskENTER_CRITICAL();
        bool received = custom_hid_report_read(&usbd_custom_hid, &rx_frame);
        taskEXIT_CRITICAL();

        if (received == true) {
            usb_data_check(&rx_frame, &last_response, tx_frame.sequence);
        }

        if (last_request - last_response >= REPORT_RESPONSE_TIMEOUT_MS) {
            taskENTER_CRITICAL();
            custom_hid_report_send(&usbd_custom_hid, (uint8_t *)&tx_frame, sizeof(tx_frame));
            taskEXIT_CRITICAL();
        } else if (now - last_request >= REPORT_REQUEST_PERIOD_MS) {
            tx_frame.sequence++;
            memcpy(tx_frame.payload, &g_usb_data_report, sizeof(g_usb_data_report));
            tx_frame.crc8 = calc_crc8(tx_frame.payload, tx_frame.length);

            taskENTER_CRITICAL();
            custom_hid_report_send(&usbd_custom_hid, (uint8_t *)&tx_frame, sizeof(tx_frame));
            taskEXIT_CRITICAL();
        }

        vTaskDelayUntil(&last_tick, pdMS_TO_TICKS(10));
    }
}

static const uint8_t crc8_table[256] = {
    0x00, 0x4d, 0x9a, 0xd7, 0x79, 0x34, 0xe3, 0xae, 0xf2, 0xbf, 0x68, 0x25,
    0x8b, 0xc6, 0x11, 0x5c, 0xa9, 0xe4, 0x33, 0x7e, 0xd0, 0x9d, 0x4a, 0x07,
    0x5b, 0x16, 0xc1, 0x8c, 0x22, 0x6f, 0xb8, 0xf5, 0x1f, 0x52, 0x85, 0xc8,
    0x66, 0x2b, 0xfc, 0xb1, 0xed, 0xa0, 0x77, 0x3a, 0x94, 0xd9, 0x0e, 0x43,
    0xb6, 0xfb, 0x2c, 0x61, 0xcf, 0x82, 0x55, 0x18, 0x44, 0x09, 0xde, 0x93,
    0x3d, 0x70, 0xa7, 0xea, 0x3e, 0x73, 0xa4, 0xe9, 0x47, 0x0a, 0xdd, 0x90,
    0xcc, 0x81, 0x56, 0x1b, 0xb5, 0xf8, 0x2f, 0x62, 0x97, 0xda, 0x0d, 0x40,
    0xee, 0xa3, 0x74, 0x39, 0x65, 0x28, 0xff, 0xb2, 0x1c, 0x51, 0x86, 0xcb,
    0x21, 0x6c, 0xbb, 0xf6, 0x58, 0x15, 0xc2, 0x8f, 0xd3, 0x9e, 0x49, 0x04,
    0xaa, 0xe7, 0x30, 0x7d, 0x88, 0xc5, 0x12, 0x5f, 0xf1, 0xbc, 0x6b, 0x26,
    0x7a, 0x37, 0xe0, 0xad, 0x03, 0x4e, 0x99, 0xd4, 0x7c, 0x31, 0xe6, 0xab,
    0x05, 0x48, 0x9f, 0xd2, 0x8e, 0xc3, 0x14, 0x59, 0xf7, 0xba, 0x6d, 0x20,
    0xd5, 0x98, 0x4f, 0x02, 0xac, 0xe1, 0x36, 0x7b, 0x27, 0x6a, 0xbd, 0xf0,
    0x5e, 0x13, 0xc4, 0x89, 0x63, 0x2e, 0xf9, 0xb4, 0x1a, 0x57, 0x80, 0xcd,
    0x91, 0xdc, 0x0b, 0x46, 0xe8, 0xa5, 0x72, 0x3f, 0xca, 0x87, 0x50, 0x1d,
    0xb3, 0xfe, 0x29, 0x64, 0x38, 0x75, 0xa2, 0xef, 0x41, 0x0c, 0xdb, 0x96,
    0x42, 0x0f, 0xd8, 0x95, 0x3b, 0x76, 0xa1, 0xec, 0xb0, 0xfd, 0x2a, 0x67,
    0xc9, 0x84, 0x53, 0x1e, 0xeb, 0xa6, 0x71, 0x3c, 0x92, 0xdf, 0x08, 0x45,
    0x19, 0x54, 0x83, 0xce, 0x60, 0x2d, 0xfa, 0xb7, 0x5d, 0x10, 0xc7, 0x8a,
    0x24, 0x69, 0xbe, 0xf3, 0xaf, 0xe2, 0x35, 0x78, 0xd6, 0x9b, 0x4c, 0x01,
    0xf4, 0xb9, 0x6e, 0x23, 0x8d, 0xc0, 0x17, 0x5a, 0x06, 0x4b, 0x9c, 0xd1,
    0x7f, 0x32, 0xe5, 0xa8
};

/**
 * @brief CRC8 calculate
 *
 * @param p data
 * @param len data length
 * @return CRC8 value
 */
static uint8_t calc_crc8(uint8_t *p, uint8_t len)
{
    uint8_t crc = 0;
    for (int i = 0; i < len; i++) {
        crc = crc8_table[(crc ^ *p++) & 0xff];
    }
    return crc;
}