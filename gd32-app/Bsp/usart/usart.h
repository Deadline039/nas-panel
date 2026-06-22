/**
 * Copyright (c) 2026, Deadline039
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef USART_H
#define USART_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void usart0_init(void);

void usart0_send(void *data, size_t len);
size_t usart0_receive(void *buf, size_t buf_size);
int usart0_printf(const char* fmt, ...);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* USART_H */
