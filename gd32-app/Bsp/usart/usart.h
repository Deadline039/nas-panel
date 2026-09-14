/**
 * Copyright (c) 2026, Deadline039
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef USART_H
#define USART_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void usart0_init(void);

void usart0_send(void *data, size_t len);
size_t usart0_receive(void *buf, size_t buf_size);
int usart0_printf(const char *fmt, ...);

#ifdef DEBUG
#define USART0_DEBUG_READ(_buf, _size) usart0_receive((_buf), (_size))
#define USART0_DEBUG_PRINTF(...)       usart0_printf(__VA_ARGS__)
#else /* DEBUG */
#define USART0_DEBUG_READ(_buf, _size)
#define USART0_DEBUG_PRINTF(...)
#endif /* DEBUG */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* USART_H */
