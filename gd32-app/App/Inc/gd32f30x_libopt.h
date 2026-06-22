/*!
    \file    gd32f30x_libopt.h
    \brief   library optional for gd32f30x

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

#ifndef GD32F30X_LIBOPT_H
#define GD32F30X_LIBOPT_H

/* CMSIS compiler specific defines */
#ifndef __ASM
#define __ASM __asm
#endif
#ifndef __INLINE
#define __INLINE inline
#endif
#ifndef __STATIC_INLINE
#define __STATIC_INLINE static inline
#endif
#ifndef __STATIC_FORCEINLINE
#define __STATIC_FORCEINLINE __attribute__((always_inline)) static inline
#endif
#ifndef __NO_RETURN
#define __NO_RETURN __attribute__((__noreturn__))
#endif
#ifndef __USED
#define __USED __attribute__((used))
#endif
#ifndef __WEAK
#define __WEAK __attribute__((weak))
#endif
#ifndef __PACKED
#define __PACKED __attribute__((packed, aligned(1)))
#endif
#ifndef __PACKED_STRUCT
#define __PACKED_STRUCT struct __attribute__((packed, aligned(1)))
#endif
#ifndef __PACKED_UNION
#define __PACKED_UNION union __attribute__((packed, aligned(1)))
#endif
#ifndef __UNALIGNED_UINT32 /* deprecated */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpacked"
#pragma GCC diagnostic ignored "-Wattributes"
struct __attribute__((packed)) T_UINT32 {
    uint32_t v;
};
#pragma GCC diagnostic pop
#define __UNALIGNED_UINT32(x) (((struct T_UINT32 *)(x))->v)
#endif
#ifndef __UNALIGNED_UINT16_WRITE
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpacked"
#pragma GCC diagnostic ignored "-Wattributes"
__PACKED_STRUCT T_UINT16_WRITE
{
    uint16_t v;
};
#pragma GCC diagnostic pop
#define __UNALIGNED_UINT16_WRITE(addr, val) (void)((((struct T_UINT16_WRITE *)(void *)(addr))->v) = (val))
#endif
#ifndef __UNALIGNED_UINT16_READ
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpacked"
#pragma GCC diagnostic ignored "-Wattributes"
__PACKED_STRUCT T_UINT16_READ
{
    uint16_t v;
};
#pragma GCC diagnostic pop
#define __UNALIGNED_UINT16_READ(addr) (((const struct T_UINT16_READ *)(const void *)(addr))->v)
#endif
#ifndef __UNALIGNED_UINT32_WRITE
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpacked"
#pragma GCC diagnostic ignored "-Wattributes"
__PACKED_STRUCT T_UINT32_WRITE
{
    uint32_t v;
};
#pragma GCC diagnostic pop
#define __UNALIGNED_UINT32_WRITE(addr, val) (void)((((struct T_UINT32_WRITE *)(void *)(addr))->v) = (val))
#endif
#ifndef __UNALIGNED_UINT32_READ
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpacked"
#pragma GCC diagnostic ignored "-Wattributes"
__PACKED_STRUCT T_UINT32_READ
{
    uint32_t v;
};
#pragma GCC diagnostic pop
#define __UNALIGNED_UINT32_READ(addr) (((const struct T_UINT32_READ *)(const void *)(addr))->v)
#endif
#ifndef __ALIGNED
#define __ALIGNED(x) __attribute__((aligned(x)))
#endif
#ifndef __RESTRICT
#define __RESTRICT __restrict
#endif

#include "gd32f30x_rcu.h"
#include "gd32f30x_adc.h"
#include "gd32f30x_can.h"
#include "gd32f30x_crc.h"
#include "gd32f30x_ctc.h"
#include "gd32f30x_dac.h"
#include "gd32f30x_dbg.h"
#include "gd32f30x_dma.h"
#include "gd32f30x_exti.h"
#include "gd32f30x_fmc.h"
#include "gd32f30x_fwdgt.h"
#include "gd32f30x_gpio.h"
#include "gd32f30x_i2c.h"
#include "gd32f30x_pmu.h"
#include "gd32f30x_bkp.h"
#include "gd32f30x_rtc.h"
#include "gd32f30x_sdio.h"
#include "gd32f30x_spi.h"
#include "gd32f30x_timer.h"
#include "gd32f30x_usart.h"
#include "gd32f30x_wwdgt.h"
#include "gd32f30x_misc.h"
#include "gd32f30x_enet.h"
#include "gd32f30x_exmc.h"

#endif /* GD32F30X_LIBOPT_H */
