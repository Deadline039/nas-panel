/**
 * Copyright (c) 2026, Deadline039
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef KEY_H
#define KEY_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void key_init(void);
bool key_enter_bootloader(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* KEY_H */
