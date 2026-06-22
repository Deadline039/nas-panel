/**
 * Copyright (c) 2026, Deadline039
 *
 * SPDX-License-Identifier: MIT
 */

#include "hc595.h"

#include <gd32f30x_spi.h>
#include <gd32f30x_gpio.h>

#define HC595_RCLK_GPIO_PORT GPIOB
#define HC595_RCLK_GPIO_PIN  GPIO_PIN_12

#define HC595_RCLK_HIGH()    gpio_bit_set(GPIOB, GPIO_PIN_12)
#define HC595_RCLK_LOW()     gpio_bit_reset(GPIOB, GPIO_PIN_12)

/**
 * @brief HC595 SPI initialize
 */
void hc595_init(void)
{
    rcu_periph_clock_enable(RCU_SPI1);
    rcu_periph_clock_enable(RCU_GPIOB);
    /* HC595_SRCLK -> SPI1_SCK */
    gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_2MHZ, GPIO_PIN_13);
    /* HC595_SER -> SPI1_MOSI */
    gpio_init(GPIOB, GPIO_MODE_AF_PP, GPIO_OSPEED_2MHZ, GPIO_PIN_15);
    gpio_init(HC595_RCLK_GPIO_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_2MHZ, HC595_RCLK_GPIO_PIN);

    spi_parameter_struct spi_init_struct;
    /* deinitialize SPI and the parameters */
    spi_i2s_deinit(SPI1);
    spi_struct_para_init(&spi_init_struct);
    /* configure SPI1 parameter */
    spi_init_struct.trans_mode = SPI_TRANSMODE_BDTRANSMIT;
    spi_init_struct.device_mode = SPI_MASTER;
    spi_init_struct.frame_size = SPI_FRAMESIZE_8BIT;
    spi_init_struct.clock_polarity_phase = SPI_CK_PL_LOW_PH_1EDGE;
    spi_init_struct.nss = SPI_NSS_SOFT;
    spi_init_struct.prescale = SPI_PSC_64;
    spi_init_struct.endian = SPI_ENDIAN_MSB;
    spi_init(SPI1, &spi_init_struct);

    HC595_RCLK_LOW();
    spi_enable(SPI1);
}

/**
 * @brief HC595 send a byte
 * @param byte byte
 */
void hc595_send_byte(uint8_t byte)
{
    while (RESET == spi_i2s_flag_get(SPI1, SPI_FLAG_TBE))
        ;
    spi_i2s_data_transmit(SPI1, byte);
    while (SET == spi_i2s_flag_get(SPI1, SPI_FLAG_TRANS))
        ;
    HC595_RCLK_LOW();
    HC595_RCLK_HIGH();
    HC595_RCLK_LOW();
}

static uint8_t led_state;

/**
 * @brief HC595 set led
 * @param pos led position, 0~3
 * @param red red led status
 * @param blue blue led status
 */
void hc595_set_led(uint8_t pos, uint8_t red, uint8_t blue)
{
    if (pos >= 4) {
        return;
    }

    if (red) {
        led_state |= 1U << (pos * 2);
    } else {
        led_state &= ~(1U << (pos * 2));
    }

    if (blue) {
        led_state |= 1U << (pos * 2 + 1);
    } else {
        led_state &= ~(1U << (pos * 2 + 1));
    }
    hc595_send_byte(led_state);
}

/**
 * @brief set all led off
 */
void hc595_set_led_off(void)
{
    led_state = 0;
    hc595_send_byte(led_state);
}
