/**
 * Copyright (c) 2026, Deadline039
 *
 * SPDX-License-Identifier: MIT
 */

#include "usart.h"

#include <gd32f30x.h>

#include <FreeRTOS.h>
#include <semphr.h>
#include <stdio.h>
#include <stdarg.h>

#define USART0_DATA_ADDRESS ((uint32_t)&USART_DATA(USART0))

static SemaphoreHandle_t tx_sem;
static SemaphoreHandle_t rx_sem;

void usart0_init(void)
{
    dma_parameter_struct dma_init_struct;
    /* enable DMA0 */
    rcu_periph_clock_enable(RCU_DMA0);
    /* initialize USART */
    /* enable GPIO clock */
    rcu_periph_clock_enable(RCU_GPIOA);

    /* enable USART clock */
    rcu_periph_clock_enable(RCU_USART0);

    /* connect port to USARTx_Tx */
    gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);

    /* connect port to USARTx_Rx */
    gpio_init(GPIOA, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, GPIO_PIN_10);

    /* USART configure */
    usart_deinit(USART0);
    usart_baudrate_set(USART0, 115200U);
    usart_receive_config(USART0, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
    usart_enable(USART0);

    /*configure DMA0 interrupt*/
    nvic_irq_enable(DMA0_Channel3_IRQn, 15, 0);
    nvic_irq_enable(DMA0_Channel4_IRQn, 15, 0);
    nvic_irq_enable(USART0_IRQn, 15, 0);

    /* deinitialize DMA channel3(USART0 tx) */
    dma_deinit(DMA0, DMA_CH3);
    dma_struct_para_init(&dma_init_struct);

    dma_init_struct.direction = DMA_MEMORY_TO_PERIPHERAL;
    dma_init_struct.memory_addr = 0;
    dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
    dma_init_struct.memory_width = DMA_MEMORY_WIDTH_8BIT;
    dma_init_struct.number = 0;
    dma_init_struct.periph_addr = USART0_DATA_ADDRESS;
    dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
    dma_init_struct.periph_width = DMA_PERIPHERAL_WIDTH_8BIT;
    dma_init_struct.priority = DMA_PRIORITY_LOW;
    dma_init(DMA0, DMA_CH3, &dma_init_struct);

    /* deinitialize DMA channel4 (USART0 rx) */
    dma_deinit(DMA0, DMA_CH4);
    dma_struct_para_init(&dma_init_struct);

    dma_init_struct.direction = DMA_PERIPHERAL_TO_MEMORY;
    dma_init_struct.memory_addr = 0;
    dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;
    dma_init_struct.memory_width = DMA_MEMORY_WIDTH_8BIT;
    dma_init_struct.number = 0;
    dma_init_struct.periph_addr = USART0_DATA_ADDRESS;
    dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;
    dma_init_struct.periph_width = DMA_PERIPHERAL_WIDTH_8BIT;
    dma_init_struct.priority = DMA_PRIORITY_LOW;
    dma_init(DMA0, DMA_CH4, &dma_init_struct);

    /* configure DMA mode */
    dma_circulation_disable(DMA0, DMA_CH3);
    dma_memory_to_memory_disable(DMA0, DMA_CH3);
    dma_circulation_disable(DMA0, DMA_CH4);
    dma_memory_to_memory_disable(DMA0, DMA_CH4);

    /* enable USART DMA for reception */
    usart_dma_receive_config(USART0, USART_RECEIVE_DMA_ENABLE);
    usart_dma_transmit_config(USART0, USART_TRANSMIT_DMA_ENABLE);

    tx_sem = xSemaphoreCreateBinary();
    xSemaphoreGive(tx_sem);
    rx_sem = xSemaphoreCreateBinary();
}

/**
 * @brief USART0 send data
 * @param data data
 * @param len data length
 */
void usart0_send(void *data, size_t len)
{
    /* wait last transfer complete */
    xSemaphoreTake(tx_sem, portMAX_DELAY);
    /* disable DMA0 Channel3 first */
    dma_channel_disable(DMA0, DMA_CH3);
    /* set address and size */
    dma_memory_address_config(DMA0, DMA_CH3, (uint32_t)data);
    dma_transfer_number_config(DMA0, DMA_CH3, len);
    /* enable DMA0 channel3 transfer complete interrupt */
    dma_interrupt_enable(DMA0, DMA_CH3, DMA_INT_FTF);
    /* enable DMA0 channel3 */
    dma_channel_enable(DMA0, DMA_CH3);
}

size_t usart0_receive(void *buf, size_t buf_size)
{
    /* disable DMA0 channel4 */
    dma_channel_disable(DMA0, DMA_CH4);
    /* set address and size */
    dma_memory_address_config(DMA0, DMA_CH4, (uint32_t)buf);
    dma_transfer_number_config(DMA0, DMA_CH4, buf_size);
    /* enable DMA0 channel4 transfer complete interrupt */
    dma_interrupt_enable(DMA0, DMA_CH4, DMA_INT_FTF);
    /* enable DMA0 channel4 */
    dma_channel_enable(DMA0, DMA_CH4);
    /* enable USART0 IDLE interrupt */
    usart_interrupt_enable(USART0, USART_INT_IDLE);

    /* wait for receive */
    xSemaphoreTake(rx_sem, portMAX_DELAY);
    /* number of data received */
    size_t rx_count = 256 - (dma_transfer_number_get(DMA0, DMA_CH4));
    return rx_count;
}

/**
 * @brief thread safety printf with USART0
 * @param fmt format
 * @param ... args
 * @return the string length transmitted
 */
int usart0_printf(const char *fmt, ...)
{
    static char printf_buf[256];
    va_list ap;
    va_start(ap, fmt);
    int len = vsnprintf(printf_buf, sizeof(printf_buf), fmt, ap);
    va_end(ap);
    usart0_send(printf_buf, len);
    return len;
}

/**
 * @brief this function handles DMA0_Channel3_IRQHandler interrupt
 */
void DMA0_Channel3_IRQHandler(void)
{
    if (dma_interrupt_flag_get(DMA0, DMA_CH3, DMA_INT_FLAG_FTF)) {
        dma_interrupt_flag_clear(DMA0, DMA_CH3, DMA_INT_FLAG_G);
        xSemaphoreGiveFromISR(tx_sem, NULL);
    }
}

/**
 * @brief this function handles DMA0_Channel4_IRQHandler interrupt
 */
void DMA0_Channel4_IRQHandler(void)
{
    if (dma_interrupt_flag_get(DMA0, DMA_CH4, DMA_INT_FLAG_FTF)) {
        dma_interrupt_flag_clear(DMA0, DMA_CH4, DMA_INT_FLAG_G);
        xSemaphoreGiveFromISR(rx_sem, NULL);
    }
}

/**
 * @brief this function handles USART interrupt request
 */
void USART0_IRQHandler(void)
{
    if (RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_IDLE)) {
        /* clear IDLE flag */
        usart_data_receive(USART0);

        /* disable DMA and reconfigure */
        dma_channel_disable(DMA0, DMA_CH4);
        dma_transfer_number_config(DMA0, DMA_CH4, 256);
        dma_channel_enable(DMA0, DMA_CH4);

        xSemaphoreGiveFromISR(rx_sem, NULL);
    }
}
