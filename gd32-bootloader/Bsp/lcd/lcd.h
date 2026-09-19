/**
 * Copyright (c) 2026, Deadline039
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef LCD_H
#define LCD_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define LCD_DISPLAY_DIRECTION 2

#if (LCD_DISPLAY_DIRECTION == 0 || LCD_DISPLAY_DIRECTION == 1)
#define LCD_WIDTH  142
#define LCD_HEIGHT 428
#elif (LCD_DISPLAY_DIRECTION == 2 || LCD_DISPLAY_DIRECTION == 3)
#define LCD_WIDTH  428
#define LCD_HEIGHT 142
#endif /* LCD_DISPLAY_DIRECTION */

#define LCD_USE_TE        0
#define LCD_USE_DMA       0

#define WHITE             0xFFFF
#define BLACK             0x0000
#define RED               0xF800
#define GREEN             0x07E0
#define BLUE              0x001F
#define MAGENTA           0xF81F
#define YELLOW            0xFFE0
#define CYAN              0x07FF

#define BROWN             0xBC40
#define BRRED             0xFC07
#define GRAY              0x8430
#define DARKBLUE          0x01CF
#define LIGHTBLUE         0x7D7C
#define GRAYBLUE          0x5458
#define LIGHTGREEN        0x841F
#define LGRAY             0xC618
#define LGRAYBLUE         0xA651
#define LBBLUE            0x2B12

#define LCD_RST_GPIO_PORT GPIOA
#define LCD_RST_GPIO_PIN  GPIO_PIN_1
#define LCD_TE_GPIO_PORT  GPIOA
#define LCD_TE_GPIO_PIN   GPIO_PIN_2
#define LCD_BK_GPIO_PORT  GPIOA
#define LCD_BK_GPIO_PIN   GPIO_PIN_3
#define LCD_CS_GPIO_PORT  GPIOA
#define LCD_CS_GPIO_PIN   GPIO_PIN_4
#define LCD_DC_GPIO_PORT  GPIOA
#define LCD_DC_GPIO_PIN   GPIO_PIN_6

void lcd_init(void);
void lcd_test(void);
void lcd_draw_point(uint16_t x, uint16_t y, uint16_t color);
void lcd_clear(uint16_t color);
void lcd_fill_region(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey,
                     uint16_t color);
void lcd_color_region(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey,
                      uint16_t *color_buf);

void lcd_backlight_ctrl(uint8_t state);
void lcd_reset(void);

void lcd_show_char(uint16_t x, uint16_t y, char chr, uint8_t size, uint8_t mode,
                   uint16_t color);
void lcd_show_string(uint16_t x, uint16_t y, uint16_t width, uint16_t height,
                     uint8_t size, const char *p, uint16_t color);
void lcd_show_num(uint16_t x, uint16_t y, uint32_t num, uint8_t len,
                  uint8_t size, uint16_t color);

#if LCD_USE_DMA
void lcd_color_region_dma(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey,
                          uint16_t *color_buf);
void lcd_flush_dma_done(void);
#endif /* LCD_USE_DMA */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LCD_H */
