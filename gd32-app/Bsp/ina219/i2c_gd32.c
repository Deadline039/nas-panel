/**
 * Copyright (c) 2026, Deadline039
 *
 * SPDX-License-Identifier: MIT
 */

#include "ina219.h"
#include <gd32f30x_i2c.h>

#include "delay/delay.h"

#include <time.h>

ina219_handle_t *p_ina219_handle;

#define I2C_TIMEOUT 50000

#define WAIT_FLAG_UNTIL_TIMEOUT(CONDITION, TIMEOUT) \
    (TIMEOUT) = I2C_TIMEOUT;                        \
    do {                                            \
        if (--(TIMEOUT) == 0) {                     \
            return 1;                               \
        }                                           \
    } while (CONDITION)

/**
 * @brief initialize the I2C0
 */
static void i2c0_init(void)
{
    /* enable GPIOB clock */
    rcu_periph_clock_enable(RCU_GPIOB);
    /* enable I2C0 clock */
    rcu_periph_clock_enable(RCU_I2C0);
    gpio_init(GPIOB, GPIO_MODE_AF_OD, GPIO_OSPEED_50MHZ, GPIO_PIN_6 | GPIO_PIN_7);

    /* cofigure I2C clock */
    i2c_clock_config(I2C0, 50000, I2C_DTCY_2);
    /* cofigure I2C address */
    i2c_mode_addr_config(I2C0, I2C_I2CMODE_ENABLE, I2C_ADDFORMAT_7BITS, 0x00);
    /* enable I2C0 */
    i2c_enable(I2C0);
    /* enable acknowledge */
    i2c_ack_config(I2C0, I2C_ACK_ENABLE);
}

static uint8_t i2c0_read(ina219_i2c_param_t *param)
{
    uint32_t timeout;

    i2c_ack_config(I2C0, I2C_ACK_ENABLE);
    WAIT_FLAG_UNTIL_TIMEOUT(i2c_flag_get(I2C0, I2C_FLAG_I2CBSY), timeout);

    i2c_start_on_bus(I2C0);
    WAIT_FLAG_UNTIL_TIMEOUT(!i2c_flag_get(I2C0, I2C_FLAG_SBSEND), timeout);

    i2c_master_addressing(I2C0, param->address, I2C_TRANSMITTER);
    WAIT_FLAG_UNTIL_TIMEOUT(!i2c_flag_get(I2C0, I2C_FLAG_ADDSEND), timeout);
    i2c_flag_clear(I2C0, I2C_FLAG_ADDSEND);

    WAIT_FLAG_UNTIL_TIMEOUT(!i2c_flag_get(I2C0, I2C_FLAG_TBE), timeout);
    i2c_data_transmit(I2C0, param->reg);
    WAIT_FLAG_UNTIL_TIMEOUT(!i2c_flag_get(I2C0, I2C_FLAG_BTC), timeout);

    i2c_start_on_bus(I2C0);
    WAIT_FLAG_UNTIL_TIMEOUT(!i2c_flag_get(I2C0, I2C_FLAG_SBSEND), timeout);
    i2c_master_addressing(I2C0, param->address, I2C_RECEIVER);
    WAIT_FLAG_UNTIL_TIMEOUT(!i2c_flag_get(I2C0, I2C_FLAG_ADDSEND), timeout);
    i2c_ack_config(I2C0, I2C_ACK_ENABLE);
    i2c_flag_clear(I2C0, I2C_FLAG_ADDSEND);
    uint8_t buf[2];

    WAIT_FLAG_UNTIL_TIMEOUT(!i2c_flag_get(I2C0, I2C_FLAG_RBNE), timeout);
    i2c_ack_config(I2C0, I2C_ACK_DISABLE);
    i2c_stop_on_bus(I2C0);
    buf[0] = i2c_data_receive(I2C0);

    WAIT_FLAG_UNTIL_TIMEOUT(!i2c_flag_get(I2C0, I2C_FLAG_RBNE), timeout);
    buf[1] = i2c_data_receive(I2C0);

    param->data = (buf[0] << 8) | buf[1];

    return 0;
}

static uint8_t i2c0_write(const ina219_i2c_param_t *param)
{
    uint32_t timeout;

    i2c_ack_config(I2C0, I2C_ACK_ENABLE);
    WAIT_FLAG_UNTIL_TIMEOUT(i2c_flag_get(I2C0, I2C_FLAG_I2CBSY), timeout);

    i2c_start_on_bus(I2C0);
    WAIT_FLAG_UNTIL_TIMEOUT(!i2c_flag_get(I2C0, I2C_FLAG_SBSEND), timeout);

    i2c_master_addressing(I2C0, param->address, I2C_TRANSMITTER);
    WAIT_FLAG_UNTIL_TIMEOUT(!i2c_flag_get(I2C0, I2C_FLAG_ADDSEND), timeout);
    i2c_flag_clear(I2C0, I2C_FLAG_ADDSEND);

    WAIT_FLAG_UNTIL_TIMEOUT(!i2c_flag_get(I2C0, I2C_FLAG_TBE), timeout);
    i2c_data_transmit(I2C0, param->reg);

    WAIT_FLAG_UNTIL_TIMEOUT(!i2c_flag_get(I2C0, I2C_FLAG_TBE), timeout);
    i2c_data_transmit(I2C0, param->data >> 8);
    WAIT_FLAG_UNTIL_TIMEOUT(!i2c_flag_get(I2C0, I2C_FLAG_TBE), timeout);
    i2c_data_transmit(I2C0, param->data & 0xFF);

    WAIT_FLAG_UNTIL_TIMEOUT(!i2c_flag_get(I2C0, I2C_FLAG_BTC), timeout);

    i2c_stop_on_bus(I2C0);

    return 0;
}

void ina219_dev_init(void)
{
    i2c0_init();
    ina219_init(&p_ina219_handle, i2c0_read, i2c0_write, INA219_ADDRESS_0, 0.001l);
    if (p_ina219_handle == NULL) {
        return;
    }

    uint16_t cali_value;
    ina219_set_pga(p_ina219_handle, INA219_PGA_40_MV);
    ina219_set_bus_voltage_range(p_ina219_handle, INA219_BUS_VOLTAGE_RANGE_16V);
    ina219_set_mode(p_ina219_handle, INA219_MODE_SHUNT_BUS_VOLTAGE_CONTINUOUS);
    ina219_set_bus_voltage_adc_mode(p_ina219_handle, INA219_ADC_MODE_12_BIT_16_SAMPLES);
    ina219_set_shunt_voltage_adc_mode(p_ina219_handle, INA219_ADC_MODE_12_BIT_16_SAMPLES);
    ina219_calculate_calibration(p_ina219_handle, &cali_value);
    ina219_set_calibration(p_ina219_handle, cali_value);
}

void ina219_delay_ms(uint32_t ms)
{
    delay_ms(ms);
}
