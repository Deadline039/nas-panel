/*!
    \file    custom_hid_core.c
    \brief   custom HID class driver

    \version 2026-2-6, V3.0.3, firmware for GD32F30x
*/

/*
    Copyright (c) 2025, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

#include "usbd_transc.h"
#include "custom_hid_core.h"

#include <string.h>

#define USBD_VID 0x3939U
#define USBD_PID 0x0831U

/* Note:it should use the C99 standard when compiling the below codes */
/* USB standard device descriptor */
usb_desc_dev custom_hid_dev_desc = {
    .header = {
        .bLength = USB_DEV_DESC_LEN,
        .bDescriptorType = USB_DESCTYPE_DEV },
    .bcdUSB = 0x0200U,
    .bDeviceClass = 0x00U,
    .bDeviceSubClass = 0x00U,
    .bDeviceProtocol = 0x00U,
    .bMaxPacketSize0 = USBD_EP0_MAX_SIZE,
    .idVendor = USBD_VID,
    .idProduct = USBD_PID,
    .bcdDevice = 0x0100U,
    .iManufacturer = STR_IDX_MFC,
    .iProduct = STR_IDX_PRODUCT,
    .iSerialNumber = STR_IDX_SERIAL,
    .bNumberConfigurations = USBD_CFG_MAX_NUM
};

/* USB device configure descriptor */
usb_hid_desc_config_set custom_hid_config_desc = {
    .config = {
        .header = {
            .bLength = sizeof(usb_desc_config),
            .bDescriptorType = USB_DESCTYPE_CONFIG },
        .wTotalLength = DESC_LEN_CONFIG,
        .bNumInterfaces = 0x01U,
        .bConfigurationValue = 0x01U,
        .iConfiguration = 0x00U,
        .bmAttributes = 0x80U,
        .bMaxPower = 0x32U },

    .hid_itf = { .header = { .bLength = sizeof(usb_desc_itf), .bDescriptorType = USB_DESCTYPE_ITF }, .bInterfaceNumber = 0x00U, .bAlternateSetting = 0x00U, .bNumEndpoints = 0x02U, .bInterfaceClass = USB_HID_CLASS, .bInterfaceSubClass = 0x00U, .bInterfaceProtocol = 0x00U, .iInterface = 0x00U },

    .hid_vendor = { .header = { .bLength = sizeof(usb_desc_hid), .bDescriptorType = USB_DESCTYPE_HID }, .bcdHID = 0x0111U, .bCountryCode = 0x00U, .bNumDescriptors = 0x01U, .bDescriptorType = USB_DESCTYPE_REPORT, .wDescriptorLength = DESC_LEN_REPORT },

    .hid_epin = { .header = { .bLength = sizeof(usb_desc_ep), .bDescriptorType = USB_DESCTYPE_EP }, .bEndpointAddress = CUSTOMHID_IN_EP, .bmAttributes = USB_EP_ATTR_INT, .wMaxPacketSize = CUSTOMHID_IN_PACKET, .bInterval = 0x01U },

    .hid_epout = { .header = { .bLength = sizeof(usb_desc_ep), .bDescriptorType = USB_DESCTYPE_EP }, .bEndpointAddress = CUSTOMHID_OUT_EP, .bmAttributes = USB_EP_ATTR_INT, .wMaxPacketSize = CUSTOMHID_OUT_PACKET, .bInterval = 0x01U }
};

/* USB language ID descriptor */
static usb_desc_LANGID usbd_language_id_desc = {
    .header = {
        .bLength = sizeof(usb_desc_LANGID),
        .bDescriptorType = USB_DESCTYPE_STR },
    .wLANGID = ENG_LANGID
};

/* USB manufacture string */
static usb_desc_str manufacturer_string = {
    .header = {
        .bLength = USB_STRING_LEN(11U),
        .bDescriptorType = USB_DESCTYPE_STR },
    .unicode_string = { 'D', 'e', 'a', 'd', 'l', 'i', 'n', 'e', '0', '3', '9' }
};

/* USB product string */
static usb_desc_str product_string = {
    .header = {
        .bLength = USB_STRING_LEN(14U),
        .bDescriptorType = USB_DESCTYPE_STR },
    .unicode_string = { 'N', 'A', 'S', '-', 'P', 'A', 'N', 'E', 'L', '-', 'm', 'a', 'i', 'n' }
};

/* USB serial string */
static usb_desc_str serial_string = {
    .header = {
        .bLength = USB_STRING_LEN(12U),
        .bDescriptorType = USB_DESCTYPE_STR }
};

/* USB string descriptor set */
static uint8_t *usbd_hid_strings[] = {
    [STR_IDX_LANGID] = (uint8_t *)&usbd_language_id_desc,
    [STR_IDX_MFC] = (uint8_t *)&manufacturer_string,
    [STR_IDX_PRODUCT] = (uint8_t *)&product_string,
    [STR_IDX_SERIAL] = (uint8_t *)&serial_string
};

usb_desc custom_hid_desc = {
    .dev_desc = (uint8_t *)&custom_hid_dev_desc,
    .config_desc = (uint8_t *)&custom_hid_config_desc,
    .strings = usbd_hid_strings
};

/* local function prototypes ('static') */
static uint8_t custom_hid_init(usb_dev *udev, uint8_t config_index);
static uint8_t custom_hid_deinit(usb_dev *udev, uint8_t config_index);
static uint8_t custom_hid_req_handler(usb_dev *udev, usb_req *req);
static void custom_hid_data_in(usb_dev *udev, uint8_t ep_num);
static void custom_hid_data_out(usb_dev *udev, uint8_t ep_num);
static uint8_t custom_hid_control_out(usb_dev *udev);

usb_class custom_hid_class = {
    .req_cmd = 0xFFU,

    .init = custom_hid_init,
    .deinit = custom_hid_deinit,
    .req_process = custom_hid_req_handler,
    .data_in = custom_hid_data_in,
    .ctlx_out = custom_hid_control_out,
    .data_out = custom_hid_data_out
};

/* Reports have no ID and contain 256 bytes, transferred in 64-byte endpoint packets. */
const uint8_t customhid_report_descriptor[DESC_LEN_REPORT] = {
    0x06, 0x00, 0xff,
    0x09, 0x01,
    0xa1, 0x01,
    0x15, 0x00,
    0x26, 0xff, 0x00,
    0x75, 0x08,
    0x96, 0x00, 0x01,
    0x09, 0x02,
    0x81, 0x02,
    0x09, 0x03,
    0x91, 0x02,
    0xc0
};

/*!
    \brief      register HID interface operation functions
    \param[in]  udev: pointer to USB device instance
    \param[in]  hid_fop: HID operation functions structure
    \param[out] none
    \retval     USB device operation status
*/
uint8_t custom_hid_itfop_register(usb_dev *udev, hid_fop_handler *hid_fop)
{
    if (NULL != hid_fop) {
        udev->user_data = hid_fop;

        return USBD_OK;
    }

    return USBD_FAIL;
}

/**
 * @brief Send from a task critical section and retain a private buffer until completion.
 * @param udev USB device.
 * @param report Complete report.
 * @param len Report length.
 * @return USBD_OK if queued, otherwise USBD_FAIL.
 */
uint8_t custom_hid_report_send(usb_dev *udev, uint8_t *report, uint16_t len)
{
    custom_hid_handler *hid = udev->class_data[CUSTOM_HID_INTERFACE];
    if (udev->cur_status != USBD_CONFIGURED || hid == NULL || report == NULL ||
        len != UDATA_FRAME_SIZE || hid->tx_busy == true) {
        return USBD_FAIL;
    }
    memcpy(hid->transmit, report, len);
    hid->tx_busy = true;
    usbd_ep_send(udev, CUSTOMHID_IN_EP, hid->transmit, len);
    return USBD_OK;
}

/**
 * @brief Initialize HID endpoints and report buffers.
 * @param udev USB device.
 * @param config_index Configuration index.
 * @return USB operation status.
 */
static uint8_t custom_hid_init(usb_dev *udev, uint8_t config_index)
{
    static custom_hid_handler hid_handler;

    memset((void *)&hid_handler, 0U, sizeof(custom_hid_handler));

    /* Initialize data endpoints. */
    usbd_ep_init(udev, EP_BUF_SNG, HID_TX_ADDR, &(custom_hid_config_desc.hid_epin));
    usbd_ep_init(udev, EP_BUF_SNG, HID_RX_ADDR, &(custom_hid_config_desc.hid_epout));

    usbd_ep_recev(udev, CUSTOMHID_OUT_EP, hid_handler.data, UDATA_FRAME_SIZE);

    udev->ep_transc[EP_ID(CUSTOMHID_IN_EP)][TRANSC_IN] = custom_hid_class.data_in;
    udev->ep_transc[EP_ID(CUSTOMHID_OUT_EP)][TRANSC_OUT] = custom_hid_class.data_out;

    udev->class_data[CUSTOM_HID_INTERFACE] = (void *)&hid_handler;

    if (NULL != udev->user_data) {
        for (uint8_t i = 0U; i < MAX_PERIPH_NUM; i++) {
            if (NULL != ((hid_fop_handler *)udev->user_data)->periph_config[i]) {
                ((hid_fop_handler *)udev->user_data)->periph_config[i]();
            }
        }
    }

    return USBD_OK;
}

/**
 * @brief Close HID endpoints and clear transfer state.
 * @param udev USB device.
 * @param config_index Configuration index.
 * @return USB operation status.
 */
static uint8_t custom_hid_deinit(usb_dev *udev, uint8_t config_index)
{
    custom_hid_handler *hid = udev->class_data[CUSTOM_HID_INTERFACE];
    if (hid != NULL) {
        hid->tx_busy = false;
        hid->rx_ready = false;
    }
    /* Close data endpoints. */
    usbd_ep_deinit(udev, CUSTOMHID_IN_EP);
    usbd_ep_deinit(udev, CUSTOMHID_OUT_EP);

    return USBD_OK;
}

/**
 * @brief Handle HID descriptors, idle configuration, and bounded output reports.
 * @param udev USB device.
 * @param req Control request.
 * @return REQ_SUPP if supported, otherwise REQ_NOTSUPP.
 */
static uint8_t custom_hid_req_handler(usb_dev *udev, usb_req *req)
{
    custom_hid_handler *hid = udev->class_data[CUSTOM_HID_INTERFACE];
    if (req->wIndex != CUSTOM_HID_INTERFACE) {
        return REQ_NOTSUPP;
    }
    if (req->bRequest == USB_GET_DESCRIPTOR && req->bmRequestType == 0x81U) {
        if (USB_DESCTYPE_REPORT == (req->wValue >> 8)) {
            usb_transc_config(&udev->transc_in[0], (uint8_t *)customhid_report_descriptor,
                              USB_MIN(DESC_LEN_REPORT, req->wLength), 0U);
            return REQ_SUPP;
        }
        if (USB_DESCTYPE_HID == (req->wValue >> 8)) {
            usb_transc_config(&udev->transc_in[0], (uint8_t *)&custom_hid_config_desc.hid_vendor,
                              USB_MIN(9U, req->wLength), 0U);
            return REQ_SUPP;
        }
        return REQ_NOTSUPP;
    }
    if (hid == NULL || udev->cur_status != USBD_CONFIGURED) {
        return REQ_NOTSUPP;
    }
    if (req->bRequest == SET_REPORT && req->bmRequestType == 0x21U &&
        req->wValue == 0x0200U && req->wLength == UDATA_FRAME_SIZE) {
        /* Some hosts send output reports over EP0; use a separate bounded buffer. */
        usb_transc_config(&udev->transc_out[0], hid->control, UDATA_FRAME_SIZE, 0U);
        return REQ_SUPP;
    }
    if (req->bRequest == GET_IDLE && req->bmRequestType == 0xa1U &&
        req->wLength == 1U && req->wValue == 0U) {
        usb_transc_config(&udev->transc_in[0], &hid->idlestate, 1U, 0U);
        return REQ_SUPP;
    }
    if (req->bRequest == SET_IDLE && req->bmRequestType == 0x21U &&
        req->wLength == 0U && (req->wValue & 0xffU) == 0U) {
        hid->idlestate = (uint8_t)(req->wValue >> 8);
        return REQ_SUPP;
    }
    return REQ_NOTSUPP;
}

/**
 * @brief Release the transmit buffer after the entire report is sent.
 * @param udev USB device.
 * @param ep_num Endpoint number.
 */
static void custom_hid_data_in(usb_dev *udev, uint8_t ep_num)
{
    custom_hid_handler *hid = udev->class_data[CUSTOM_HID_INTERFACE];
    if (ep_num == EP_ID(CUSTOMHID_IN_EP) && hid != NULL) {
        hid->tx_busy = false;
    }
}

/**
 * @brief Publish complete reports to the mailbox, discard short reports, and rearm reception.
 * @param udev USB device.
 * @param ep_num Endpoint number.
 */
static void custom_hid_data_out(usb_dev *udev, uint8_t ep_num)
{
    custom_hid_handler *hid = udev->class_data[CUSTOM_HID_INTERFACE];
    if (ep_num != EP_ID(CUSTOMHID_OUT_EP) || hid == NULL) {
        return;
    }
    if (udev->transc_out[ep_num].xfer_count == UDATA_FRAME_SIZE && hid->rx_ready == false) {
        memcpy(hid->received, hid->data, UDATA_FRAME_SIZE);
        hid->rx_ready = true;
    }
    usbd_ep_recev(udev, CUSTOMHID_OUT_EP, hid->data, UDATA_FRAME_SIZE);
}

/**
 * @brief Read an interrupt-published report from a task critical section.
 * @param udev USB device.
 * @param report Destination report buffer.
 * @return True if a report was read, otherwise false.
 */
bool custom_hid_report_read(usb_dev *udev, udata_frame_t *report)
{
    custom_hid_handler *hid = udev->class_data[CUSTOM_HID_INTERFACE];
    if (udev->cur_status != USBD_CONFIGURED || hid == NULL || report == NULL || hid->rx_ready == false) {
        return false;
    }
    memcpy(report, hid->received, UDATA_FRAME_SIZE);
    hid->rx_ready = false;
    return true;
}

/**
 * @brief Publish a complete control output report to the shared receive mailbox.
 * @param udev USB device.
 * @return USB operation status.
 */
static uint8_t custom_hid_control_out(usb_dev *udev)
{
    custom_hid_handler *hid = udev->class_data[CUSTOM_HID_INTERFACE];
    const usb_req *req = &udev->control.req;
    if (hid == NULL || udev->control.ctl_state != USBD_CTL_DATA_OUT ||
        req->bRequest != SET_REPORT || req->bmRequestType != 0x21U ||
        req->wValue != 0x0200U || req->wLength != UDATA_FRAME_SIZE ||
        udev->transc_out[0].xfer_count != UDATA_FRAME_SIZE) {
        return USBD_FAIL;
    }
    if (hid->rx_ready == false) {
        memcpy(hid->received, hid->control, UDATA_FRAME_SIZE);
        hid->rx_ready = true;
    }
    return USBD_OK;
}
