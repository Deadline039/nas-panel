/**
 * Copyright (c) 2026, Deadline039
 *
 * SPDX-License-Identifier: MIT
 */

#include "lcd.h"

#include <gd32f30x_spi.h>
#include <gd32f30x_dma.h>
#include <gd32f30x_gpio.h>

#include "delay/delay.h"

#define LCD_CS_ON()           (GPIO_BC(LCD_CS_GPIO_PORT) = LCD_CS_GPIO_PIN)
#define LCD_CS_OFF()          (GPIO_BOP(LCD_CS_GPIO_PORT) = LCD_CS_GPIO_PIN)

#define LCD_DC_CMD()          (GPIO_BC(LCD_DC_GPIO_PORT) = LCD_DC_GPIO_PIN)
#define LCD_DC_DATA()         (GPIO_BOP(LCD_DC_GPIO_PORT) = LCD_DC_GPIO_PIN)

#define LCD_DC_SWITCH_TIME_US 85

/**
 * @brief LCD write command
 * @param cmd command
 */
static void lcd_write_cmd(uint8_t cmd)
{
    LCD_DC_CMD();
    /* wait for cmd ready */
    delay_us(LCD_DC_SWITCH_TIME_US);
    while (RESET == spi_i2s_flag_get(SPI0, SPI_FLAG_TBE))
        ;
    spi_i2s_data_transmit(SPI0, cmd);
    while (SET == spi_i2s_flag_get(SPI0, SPI_FLAG_TRANS))
        ;
}

/**
 * @brief LCD write command and a serial of data
 *
 * @param cmd command
 * @param data data
 * @param size data length
 */
static void lcd_write_cmd_data(uint8_t cmd, uint8_t *data, uint16_t size)
{
    LCD_DC_CMD();
    while (RESET == spi_i2s_flag_get(SPI0, SPI_FLAG_TBE))
        ;
    spi_i2s_data_transmit(SPI0, cmd);
    while (SET == spi_i2s_flag_get(SPI0, SPI_FLAG_TRANS))
        ;

    LCD_DC_DATA();
    while (size > 0U) {
        while (RESET == spi_i2s_flag_get(SPI0, SPI_FLAG_TBE))
            ;
        spi_i2s_data_transmit(SPI0, *data);
        data++;
        size--;
    }
    while (SET == spi_i2s_flag_get(SPI0, SPI_FLAG_TRANS))
        ;
}

/**
 * @brief LCD write 8bit data
 *
 * @param data data
 */
static void lcd_write_data8(uint8_t data)
{
    LCD_DC_DATA();
    while (RESET == spi_i2s_flag_get(SPI0, SPI_FLAG_TBE))
        ;
    spi_i2s_data_transmit(SPI0, data);
    while (SET == spi_i2s_flag_get(SPI0, SPI_FLAG_TRANS))
        ;
}

/**
 * @brief LCD SPI initialize
 */
static void lcd_spi_init(void)
{
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_SPI0);

    /* LCD_SCL -> SPI0_SCK */
    gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_MAX, GPIO_PIN_5);
    /* LCD_SDA -> SPI0_MOSI */
    gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_MAX, GPIO_PIN_7);

#ifdef LCD_RST_GPIO_PORT
    gpio_init(LCD_RST_GPIO_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, LCD_RST_GPIO_PIN);
#endif /* LCD_RST_GPIO_PORT */

#ifdef LCD_TE_GPIO_PORT
    gpio_init(LCD_TE_GPIO_PORT, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, LCD_TE_GPIO_PIN);
#endif /* LCD_TE_GPIO_PORT */

#ifdef LCD_BK_GPIO_PORT
    gpio_init(LCD_BK_GPIO_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, LCD_BK_GPIO_PIN);
#endif /* LCD_BK_GPIO_PORT */

    gpio_init(LCD_CS_GPIO_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_MAX, LCD_CS_GPIO_PIN);
    gpio_init(LCD_DC_GPIO_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_MAX, LCD_DC_GPIO_PIN);

#if LCD_USE_DMA
    rcu_periph_clock_enable(RCU_DMA0);
    dma_parameter_struct dma_init_struct;
    dma_struct_para_init(&dma_init_struct);

    /* configure SPI0 transmit DMA: DMA_CH2 */
    dma_deinit(DMA0, DMA_CH2);
    dma_init_struct.periph_addr = (uint32_t)&SPI_DATA(SPI0);
    dma_init_struct.memory_addr = 0;
    dma_init_struct.direction = DMA_MEMORY_TO_PERIPHERAL;
    dma_init_struct.memory_width = DMA_MEMORY_WIDTH_16BIT;
    dma_init_struct.periph_width = DMA_PERIPHERAL_WIDTH_16BIT;
    dma_init_struct.priority = DMA_PRIORITY_LOW;
    dma_init_struct.number = 0;
    dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
    dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
    dma_init(DMA0, DMA_CH2, &dma_init_struct);
    /* configure DMA mode */
    dma_circulation_disable(DMA0, DMA_CH2);
    dma_memory_to_memory_disable(DMA0, DMA_CH2);
    nvic_irq_enable(DMA0_Channel2_IRQn, 5, 0);
#endif /* LCD_USE_DMA */

    spi_parameter_struct spi_init_struct;
    /* deinitialize SPI and the parameters */
    spi_i2s_deinit(SPI0);
    spi_struct_para_init(&spi_init_struct);

    /* configure SPI0 parameter */
    spi_init_struct.trans_mode = SPI_TRANSMODE_BDTRANSMIT;
    spi_init_struct.device_mode = SPI_MASTER;
    spi_init_struct.frame_size = SPI_FRAMESIZE_8BIT;
    spi_init_struct.clock_polarity_phase = SPI_CK_PL_HIGH_PH_2EDGE;
    spi_init_struct.nss = SPI_NSS_SOFT;
    spi_init_struct.prescale = SPI_PSC_2;
    spi_init_struct.endian = SPI_ENDIAN_MSB;
    spi_init(SPI0, &spi_init_struct);

    LCD_CS_OFF();
    spi_enable(SPI0);
}

/**
 * @brief initialize LCD
 */
void lcd_init(void)
{
    lcd_spi_init();
    lcd_backlight_ctrl(0);
    lcd_reset();

    LCD_CS_ON();

    lcd_write_cmd(0xff);
    lcd_write_data8(0xa5);
    lcd_write_cmd(0x9a);
    lcd_write_data8(0x08);
    lcd_write_cmd(0x9b);
    lcd_write_data8(0x08);
    lcd_write_cmd(0x9c);
    lcd_write_data8(0xb0);
    lcd_write_cmd(0x9d);
    lcd_write_data8(0x16);
    lcd_write_cmd(0x9e);
    lcd_write_data8(0xc4);
    lcd_write_cmd(0x8f);
    lcd_write_data8(0x55);
    lcd_write_data8(0x04);
    lcd_write_cmd(0x84);
    lcd_write_data8(0x90);
    lcd_write_cmd(0x83);
    lcd_write_data8(0x7b);
    lcd_write_cmd(0x85);
    lcd_write_data8(0x33);
    lcd_write_cmd(0x60);
    lcd_write_data8(0x00);
    lcd_write_cmd(0x70);
    lcd_write_data8(0x00);
    lcd_write_cmd(0x61);
    lcd_write_data8(0x02);
    lcd_write_cmd(0x71);
    lcd_write_data8(0x02);
    lcd_write_cmd(0x62);
    lcd_write_data8(0x04);
    lcd_write_cmd(0x72);
    lcd_write_data8(0x04);
    lcd_write_cmd(0x6c);
    lcd_write_data8(0x29);
    lcd_write_cmd(0x7c);
    lcd_write_data8(0x29);
    lcd_write_cmd(0x6d);
    lcd_write_data8(0x31);
    lcd_write_cmd(0x7d);
    lcd_write_data8(0x31);
    lcd_write_cmd(0x6e);
    lcd_write_data8(0x0f);
    lcd_write_cmd(0x7e);
    lcd_write_data8(0x0f);
    lcd_write_cmd(0x66);
    lcd_write_data8(0x21);
    lcd_write_cmd(0x76);
    lcd_write_data8(0x21);
    lcd_write_cmd(0x68);
    lcd_write_data8(0x3A);
    lcd_write_cmd(0x78);
    lcd_write_data8(0x3A);
    lcd_write_cmd(0x63);
    lcd_write_data8(0x07);
    lcd_write_cmd(0x73);
    lcd_write_data8(0x07);
    lcd_write_cmd(0x64);
    lcd_write_data8(0x05);
    lcd_write_cmd(0x74);
    lcd_write_data8(0x05);
    lcd_write_cmd(0x65);
    lcd_write_data8(0x02);
    lcd_write_cmd(0x75);
    lcd_write_data8(0x02);
    lcd_write_cmd(0x67);
    lcd_write_data8(0x23);
    lcd_write_cmd(0x77);
    lcd_write_data8(0x23);
    lcd_write_cmd(0x69);
    lcd_write_data8(0x08);
    lcd_write_cmd(0x79);
    lcd_write_data8(0x08);
    lcd_write_cmd(0x6a);
    lcd_write_data8(0x13);
    lcd_write_cmd(0x7a);
    lcd_write_data8(0x13);
    lcd_write_cmd(0x6b);
    lcd_write_data8(0x13);
    lcd_write_cmd(0x7b);
    lcd_write_data8(0x13);
    lcd_write_cmd(0x6f);
    lcd_write_data8(0x00);
    lcd_write_cmd(0x7f);
    lcd_write_data8(0x00);
    lcd_write_cmd(0x50);
    lcd_write_data8(0x00);
    lcd_write_cmd(0x52);
    lcd_write_data8(0xd6);
    lcd_write_cmd(0x53);
    lcd_write_data8(0x08);
    lcd_write_cmd(0x54);
    lcd_write_data8(0x08);
    lcd_write_cmd(0x55);
    lcd_write_data8(0x1e);
    lcd_write_cmd(0x56);
    lcd_write_data8(0x1c);
    /* goa map_sel */
    lcd_write_cmd(0xa0);
    lcd_write_data8(0x2b);
    lcd_write_data8(0x24);
    lcd_write_data8(0x00);
    lcd_write_cmd(0xa1);
    lcd_write_data8(0x87);
    lcd_write_cmd(0xa2);
    lcd_write_data8(0x86);
    lcd_write_cmd(0xa5);
    lcd_write_data8(0x00);
    lcd_write_cmd(0xa6);
    lcd_write_data8(0x00);
    lcd_write_cmd(0xa7);
    lcd_write_data8(0x00);
    lcd_write_cmd(0xa8);
    lcd_write_data8(0x36);
    lcd_write_cmd(0xa9);
    lcd_write_data8(0x7e);
    lcd_write_cmd(0xaa);
    lcd_write_data8(0x7e);
    lcd_write_cmd(0xB9);
    lcd_write_data8(0x85);
    lcd_write_cmd(0xBA);
    lcd_write_data8(0x84);
    lcd_write_cmd(0xBB);
    lcd_write_data8(0x83);
    lcd_write_cmd(0xBC);
    lcd_write_data8(0x82);
    lcd_write_cmd(0xBD);
    lcd_write_data8(0x81);
    lcd_write_cmd(0xBE);
    lcd_write_data8(0x80);
    lcd_write_cmd(0xBF);
    lcd_write_data8(0x01);
    lcd_write_cmd(0xC0);
    lcd_write_data8(0x02);
    lcd_write_cmd(0xc1);
    lcd_write_data8(0x00);
    lcd_write_cmd(0xc2);
    lcd_write_data8(0x00);
    lcd_write_cmd(0xc3);
    lcd_write_data8(0x00);
    lcd_write_cmd(0xc4);
    lcd_write_data8(0x33);
    lcd_write_cmd(0xc5);
    lcd_write_data8(0x7e);
    lcd_write_cmd(0xc6);
    lcd_write_data8(0x7e);
    lcd_write_cmd(0xC8);
    lcd_write_data8(0x33);
    lcd_write_data8(0x33);
    lcd_write_cmd(0xC9);
    lcd_write_data8(0x68);
    lcd_write_cmd(0xCA);
    lcd_write_data8(0x69);
    lcd_write_cmd(0xCB);
    lcd_write_data8(0x6a);
    lcd_write_cmd(0xCC);
    lcd_write_data8(0x6b);
    lcd_write_cmd(0xCD);
    lcd_write_data8(0x33);
    lcd_write_data8(0x33);
    lcd_write_cmd(0xCE);
    lcd_write_data8(0x6c);
    lcd_write_cmd(0xCF);
    lcd_write_data8(0x6d);
    lcd_write_cmd(0xD0);
    lcd_write_data8(0x6e);
    lcd_write_cmd(0xD1);
    lcd_write_data8(0x6f);
    lcd_write_cmd(0xAB);
    lcd_write_data8(0x03);
    lcd_write_data8(0x67);
    lcd_write_cmd(0xAC);
    lcd_write_data8(0x03);
    lcd_write_data8(0x6b);
    lcd_write_cmd(0xAD);
    lcd_write_data8(0x03);
    lcd_write_data8(0x68);
    lcd_write_cmd(0xAE);
    lcd_write_data8(0x03);
    lcd_write_data8(0x6c);
    lcd_write_cmd(0xb3);
    lcd_write_data8(0x00);
    lcd_write_cmd(0xb4);
    lcd_write_data8(0x00);
    lcd_write_cmd(0xb5);
    lcd_write_data8(0x00);
    lcd_write_cmd(0xB6);
    lcd_write_data8(0x32);
    lcd_write_cmd(0xB7);
    lcd_write_data8(0x7e);
    lcd_write_cmd(0xB8);
    lcd_write_data8(0x7e);
    lcd_write_cmd(0xe0);
    lcd_write_data8(0x00);
    lcd_write_cmd(0xe1);
    lcd_write_data8(0x03);
    lcd_write_data8(0x0f);
    lcd_write_cmd(0xe2);
    lcd_write_data8(0x04);
    lcd_write_cmd(0xe3);
    lcd_write_data8(0x01);
    lcd_write_cmd(0xe4);
    lcd_write_data8(0x0e);
    lcd_write_cmd(0xe5);
    lcd_write_data8(0x01);
    lcd_write_cmd(0xe6);
    lcd_write_data8(0x19);
    lcd_write_cmd(0xe7);
    lcd_write_data8(0x10);
    lcd_write_cmd(0xe8);
    lcd_write_data8(0x10);
    lcd_write_cmd(0xea);
    lcd_write_data8(0x12);
    lcd_write_cmd(0xeb);
    lcd_write_data8(0xd0);
    lcd_write_cmd(0xec);
    lcd_write_data8(0x04);
    lcd_write_cmd(0xed);
    lcd_write_data8(0x07);
    lcd_write_cmd(0xee);
    lcd_write_data8(0x07);
    lcd_write_cmd(0xef);
    lcd_write_data8(0x09);
    lcd_write_cmd(0xf0);
    lcd_write_data8(0xd0);
    lcd_write_cmd(0xf1);
    lcd_write_data8(0x0e);

    // lcd_write_cmd(0xF9);
    // lcd_write_data8(0x17);
    // lcd_write_cmd(0xf2);
    // lcd_write_data8(0x2e);
    // lcd_write_data8(0x1b);
    // lcd_write_data8(0x0b);
    // lcd_write_data8(0x20);
    // lcd_write_cmd(0xF9);
    lcd_write_data8(0x17);
    lcd_write_cmd(0xf2);
    lcd_write_data8(0x2c);
    lcd_write_data8(0x1b);
    lcd_write_data8(0x0b);
    lcd_write_data8(0x20);
    /* 1 dot */
    lcd_write_cmd(0xe9);
    lcd_write_data8(0x29);
    lcd_write_cmd(0xec);
    lcd_write_data8(0x04);

    /* TE */
    lcd_write_cmd(0x35);
    lcd_write_data8(0x00);
    lcd_write_cmd(0x44);
    lcd_write_data8(0x00);
    lcd_write_data8(0x10);
    lcd_write_cmd(0x46);
    lcd_write_data8(0x10);
    lcd_write_cmd(0xff);
    lcd_write_data8(0x00);
    lcd_write_cmd(0x3a);
    lcd_write_data8(0x05);
    lcd_write_cmd(0x36); /* Memory Access Control */

#if (LCD_DISPLAY_DIRECTION == 0)
    lcd_write_data8(0x00);
#elif (LCD_DISPLAY_DIRECTION == 1)
    lcd_write_data8(0xC0);
#elif (LCD_DISPLAY_DIRECTION == 2)
    lcd_write_data8(0x60);
#elif (LCD_DISPLAY_DIRECTION == 3)
    lcd_write_data8(0xA0);
#else /* LCD_DISPLAY_DIRECTION */
#error "Unknow display direction!"
#endif /* LCD_DISPLAY_DIRECTION */

    lcd_write_cmd(0x11);
    delay_ms(220);
    lcd_write_cmd(0x29);
    delay_ms(200);

    LCD_CS_OFF();

    // spi_disable(SPI0);
    // uint32_t reg = SPI_CTL0(SPI0);
    // reg |= SPI_PSC_2;
    // SPI_CTL0(SPI0) = reg;
    // spi_enable(SPI0);

    lcd_clear(BLACK);
    lcd_backlight_ctrl(1);
}

/**
 * @brief test lcd color
 */
void lcd_test(void)
{
    while (1) {
        lcd_clear(RED);
        delay_ms(1000);
        lcd_clear(BLUE);
        delay_ms(1000);
        lcd_clear(GREEN);
        delay_ms(1000);
        lcd_clear(WHITE);
        delay_ms(1000);
    }
}

/**
 * @brief Set display window
 *
 * @param x0 Start x coordinate
 * @param y0 Start y coordinate
 * @param x1 End x coordinate
 * @param y1 End y coordinate
 */
void lcd_set_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    static uint16_t old_x0 = 0xFFFF, old_x1 = 0xFFFF, old_y0 = 0xFFFF,
                    old_y1 = 0xFFFF;

    uint8_t buf[4];
    if (x1 >= LCD_WIDTH) {
        x1 = LCD_WIDTH - 1;
    }
    if (y1 >= LCD_HEIGHT) {
        y1 = LCD_HEIGHT - 1;
    }

#if (LCD_DISPLAY_DIRECTION == 0)
    x0 += 12;
    x1 += 12;
#elif (LCD_DISPLAY_DIRECTION == 1)
    x0 += 14;
    x1 += 14;
#elif (LCD_DISPLAY_DIRECTION == 2)
    y0 += 14;
    y1 += 14;
#elif (LCD_DISPLAY_DIRECTION == 3)
    y0 += 12;
    y1 += 12;
#endif /* LCD_DISPLAY_DIRECTION */

    if (x0 != old_x0 || x1 != old_x1) {
        buf[0] = x0 >> 8;
        buf[1] = x0 & 0xFF;
        buf[2] = x1 >> 8;
        buf[3] = x1 & 0xFF;
        LCD_CS_ON();
        lcd_write_cmd_data(0x2A, buf, 4);
        old_x0 = x0;
        old_x1 = x1;
    }
    if (y0 != old_y0 || y1 != old_y1) {
        buf[0] = y0 >> 8;
        buf[1] = y0 & 0xFF;
        buf[2] = y1 >> 8;
        buf[3] = y1 & 0xFF;
        LCD_CS_ON();
        lcd_write_cmd_data(0x2B, buf, 4);
        old_y0 = y0;
        old_y1 = y1;
    }
    LCD_CS_OFF();
}

/**
 * @brief Draw a point
 * @param x x coordinate
 * @param y y coordinate
 * @param color color
 */
void lcd_draw_point(uint16_t x, uint16_t y, uint16_t color)
{
    if (x >= LCD_WIDTH || y >= LCD_HEIGHT) {
        return;
    }
    uint8_t color_buf[2];
    color_buf[0] = color >> 8;
    color_buf[1] = color & 0xFF;
    lcd_set_window(x, y, x, y);
    LCD_CS_ON();
    lcd_write_cmd_data(0x2C, color_buf, 2);
    LCD_CS_OFF();
}

/**
 * @brief LCD full screen fill
 * @param color color
 */
void lcd_clear(uint16_t color)
{
    uint8_t color_buf[2];
    color_buf[0] = color >> 8;
    color_buf[1] = color & 0xFF;

    lcd_set_window(0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1);

    LCD_CS_ON();
    lcd_write_cmd(0x2C);
    for (uint32_t i = 0; i < LCD_WIDTH * LCD_HEIGHT; i++) {
        lcd_write_data8(color_buf[0]);
        lcd_write_data8(color_buf[1]);
    }
    LCD_CS_OFF();
}

/**
 * @brief LCD region fill
 * @param sx Start x coordinate
 * @param sy Start y coordinate
 * @param ex End x coordinate
 * @param ey End y coordinate
 * @param color color
 */
void lcd_fill_region(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey,
                     uint16_t color)
{
    uint8_t color_buf[2];
    uint32_t size = (ex - sx + 1) * (ey - sy + 1) * sizeof(uint16_t);
    color_buf[0] = color >> 8;
    color_buf[1] = color & 0xFF;

    lcd_set_window(sx, sy, ex, ey);
    LCD_CS_ON();
    lcd_write_cmd(0x2C);
    for (uint32_t i = 0; i < size; i++) {
        lcd_write_data8(color_buf[0]);
        lcd_write_data8(color_buf[1]);
    }
    LCD_CS_OFF();
}

/**
 * @brief LCD region fill
 * @param sx Start x coordinate
 * @param sy Start y coordinate
 * @param ex End x coordinate
 * @param ey End y coordinate
 * @param color_buf Color array
 * @note Write length is `(ex - sx + 1) * (ey - sy + 1)`, little-endian
 */
void lcd_color_region(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey,
                      uint16_t *color_buf)
{
    uint32_t size = (ex - sx + 1) * (ey - sy + 1);
    lcd_set_window(sx, sy, ex, ey);
    LCD_CS_ON();
    lcd_write_cmd(0x2C);
    spi_i2s_data_frame_format_config(SPI0, SPI_FRAMESIZE_16BIT);
    LCD_DC_DATA();
    while (size > 0U) {
        spi_i2s_data_transmit(SPI0, *color_buf);
        color_buf++;
        size--;
        while (RESET == spi_i2s_flag_get(SPI0, SPI_FLAG_TBE))
            ;
    }
    while (SET == spi_i2s_flag_get(SPI0, SPI_FLAG_TRANS))
        ;

    LCD_CS_OFF();
    spi_i2s_data_frame_format_config(SPI0, SPI_FRAMESIZE_8BIT);
}

/**
 * @brief LCD backlight control
 * @param state Backlight state
 *  @arg - 1: On
 *  @arg - 0: Off
 */
void lcd_backlight_ctrl(uint8_t state)
{
#ifdef LCD_BK_GPIO_PORT
    if (state) {
        gpio_bit_set(LCD_BK_GPIO_PORT, LCD_BK_GPIO_PIN);
    } else {
        gpio_bit_reset(LCD_BK_GPIO_PORT, LCD_BK_GPIO_PIN);
    }
#else  /* LCD_BK_GPIO_PORT */
    (void)state;
#endif /* LCD_BK_GPIO_PORT */
}

/**
 * @brief LCD reset
 */
void lcd_reset(void)
{
#ifdef LCD_RST_GPIO_PORT
    gpio_bit_reset(LCD_RST_GPIO_PORT, LCD_RST_GPIO_PIN);
    delay_ms(100);
    gpio_bit_set(LCD_RST_GPIO_PORT, LCD_RST_GPIO_PIN);
#endif /* LCD_RST_GPIO_PORT */
}

#if LCD_USE_DMA

/**
 * @brief LCD region fill
 * @param sx Start x coordinate
 * @param sy Start y coordinate
 * @param ex End x coordinate
 * @param ey End y coordinate
 * @param color_buf Color array
 * @note Write length is `(ex - sx + 1) * (ey - sy + 1)`, little-endian
 */
void lcd_color_region_dma(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey,
                          uint16_t *color_buf)
{
    uint32_t len = (ex - sx + 1) * (ey - sy + 1);
    lcd_set_window(sx, sy, ex, ey);
    LCD_CS_ON();
    lcd_write_cmd(0x2C);
    /* Set SPI to 16 bit Mode */
    spi_i2s_data_frame_format_config(SPI0, SPI_FRAMESIZE_16BIT);

    LCD_DC_DATA();
    spi_disable(SPI0);
    dma_channel_disable(DMA0, DMA_CH2);

    /* Set DMA length */
    dma_transfer_number_config(DMA0, DMA_CH2, len);
    /* Set source address */
    dma_memory_address_config(DMA0, DMA_CH2, (uint32_t)color_buf);

    /* Disable transfer half complete interrupt */
    dma_interrupt_disable(DMA0, DMA_CH2, DMA_INT_HTF);
    /* Enable the transfer complete interrupt */
    dma_interrupt_enable(DMA0, DMA_CH2, DMA_INT_FTF);
    dma_interrupt_enable(DMA0, DMA_CH2, DMA_INT_ERR);

    /* Enable the peripherals*/
    spi_dma_enable(SPI0, SPI_DMA_TRANSMIT);
    dma_channel_enable(DMA0, DMA_CH2);
    spi_enable(SPI0);
}

/**
 * @brief this function handles DMA0_Channel2_IRQHandler interrupt
 */
void DMA0_Channel2_IRQHandler(void)
{
    if (dma_flag_get(DMA0, DMA_CH2, DMA_FLAG_FTF)) {
        dma_interrupt_disable(DMA0, DMA_CH2, DMA_INT_FTF);
        dma_interrupt_disable(DMA0, DMA_CH2, DMA_INT_ERR);

        dma_flag_clear(DMA0, DMA_CH2, DMA_FLAG_FTF);
        dma_flag_clear(DMA0, DMA_CH2, DMA_FLAG_ERR);

        LCD_CS_OFF();
        lcd_flush_dma_done();
        spi_i2s_data_frame_format_config(SPI0, SPI_FRAMESIZE_8BIT);
    } else if (dma_flag_get(DMA0, DMA_CH2, DMA_FLAG_ERR)) {
        dma_interrupt_disable(DMA0, DMA_CH2, DMA_INT_FTF);
        dma_interrupt_disable(DMA0, DMA_CH2, DMA_INT_ERR);

        dma_flag_clear(DMA0, DMA_CH2, DMA_FLAG_FTF);
        dma_flag_clear(DMA0, DMA_CH2, DMA_FLAG_ERR);
    }
}

/**
 * @brief LCD DMA flush done callback
 */
__attribute__((weak)) void lcd_flush_dma_done(void)
{
}

#endif /* LCD_USE_DMA */
