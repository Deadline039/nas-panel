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

typedef enum {
    KEY_EVENT_NONE = 0,
    KEY_EVENT_PRESSED,
    KEY_EVENT_SHORT_PRESS,
    KEY_EVENT_LONG_PRESS,
} key_event_t;

void key_init(void);
key_event_t key_up_get(void);
key_event_t key_down_get(void);
bool pwr_get_state(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* KEY_H */
