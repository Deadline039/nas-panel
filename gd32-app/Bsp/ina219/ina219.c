/**
 * Copyright (c) 2026, Deadline039
 *
 * SPDX-License-Identifier: MIT
 */

#include "ina219.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

/**
 * @brief ina219 handle structure definition
 */
struct ina219_handle_s {
    uint8_t i2c_addr;                       /**< i2c device address */
    double r;                               /**< resistance */
    double current_lsb;                     /**< current lsb */
    ina219_i2c_param_t i2c_param;           /**< I2C read/write parameters */
    ina219_i2c_read_func_t i2c_read_func;   /**< I2C read interface */
    ina219_i2c_write_func_t i2c_write_func; /**< I2C write interface */

    uint8_t inited; /**< inited flag */
};

#define I2C_READ(handle)  handle->i2c_read_func(&handle->i2c_param)
#define I2C_WRITE(handle) handle->i2c_write_func(&handle->i2c_param)

/**
 * @brief     set the resistance
 * @param     handle pointer to an ina219 handle structure
 * @param     resistance current sampling resistance value
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t ina219_set_resistance(ina219_handle_t *handle, double resistance)
{
    if (handle == NULL) {
        return 2;
    }

    handle->r = resistance;

    return 0;
}

/**
 * @brief      get the resistance
 * @param      handle pointer to an ina219 handle structure
 * @param[out] resistance pointer to a current sampling resistance value buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t ina219_get_resistance(ina219_handle_t *handle, double *resistance)
{
    if (handle == NULL) {
        return 2;
    }

    *resistance = handle->r;

    return 0;
}

/**
 * @brief     set the i2c address pin
 * @param     handle pointer to an ina219 handle structure
 * @param     addr_pin address pin
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t ina219_set_addr_pin(ina219_handle_t *handle, ina219_address_t addr_pin)
{
    if (handle == NULL) {
        return 2;
    }

    handle->i2c_addr = (uint8_t)addr_pin; /* set pin */

    return 0;
}

/**
 * @brief      get the i2c address pin
 * @param      handle pointer to an ina219 handle structure
 * @param[out] addr_pin pointer to an address pin buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t ina219_get_addr_pin(ina219_handle_t *handle, ina219_address_t *addr_pin)
{
    if (handle == NULL) {
        return 2;
    }

    *addr_pin = (ina219_address_t)(handle->i2c_addr); /* get pin */

    return 0;
}

/**
 * @brief     soft reset the chip
 * @param     handle pointer to an ina219 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 soft reset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ina219_soft_reset(ina219_handle_t *handle)
{
    uint8_t res;
    uint16_t prev;

    if (handle == NULL) {
        return 2;
    }
    if (handle->inited != 1) {
        return 3;
    }

    handle->i2c_param.reg = INA219_REG_CONF;
    res = I2C_READ(handle);
    prev = handle->i2c_param.data;
    if (res != 0) {
        return 1;
    }

    prev &= ~(1 << 15); /* clear soft reset */
    prev |= 1 << 15;    /* set soft reset */
    handle->i2c_param.data = prev;
    return I2C_WRITE(handle);
}

/**
 * @brief     set the bus voltage range
 * @param     handle pointer to an ina219 handle structure
 * @param     range bus voltage range
 * @return    status code
 *            - 0 success
 *            - 1 set bus voltage range failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ina219_set_bus_voltage_range(ina219_handle_t *handle, ina219_bus_voltage_range_t range)
{
    uint8_t res;
    uint16_t prev;

    if (handle == NULL) {
        return 2;
    }
    if (handle->inited != 1) {
        return 3;
    }

    handle->i2c_param.reg = INA219_REG_CONF;
    res = I2C_READ(handle);
    prev = handle->i2c_param.data;
    if (res != 0) {
        return 1;
    }
    prev &= ~(1 << 13);  /* clear range bit */
    prev |= range << 13; /* set range bit */
    handle->i2c_param.data = prev;
    return I2C_WRITE(handle);
}

/**
 * @brief      get the bus voltage range
 * @param      handle pointer to an ina219 handle structure
 * @param[out] *range pointer to a bus voltage range buffer
 * @return     status code
 *             - 0 success
 *             - 1 get bus voltage range failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ina219_get_bus_voltage_range(ina219_handle_t *handle, ina219_bus_voltage_range_t *range)
{
    uint8_t res;
    uint16_t prev;

    if (handle == NULL) {
        return 2;
    }
    if (handle->inited != 1) {
        return 3;
    }

    handle->i2c_param.reg = INA219_REG_CONF;
    res = I2C_READ(handle);
    prev = handle->i2c_param.data;
    if (res != 0) {
        return 1;
    }
    *range = (ina219_bus_voltage_range_t)((prev >> 13) & 0x01); /* get range */

    return 0;
}

/**
 * @brief     set the pga
 * @param     handle pointer to an ina219 handle structure
 * @param     pga adc pga
 * @return    status code
 *            - 0 success
 *            - 1 set pga failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ina219_set_pga(ina219_handle_t *handle, ina219_pga_t pga)
{
    uint8_t res;
    uint16_t prev;

    if (handle == NULL) {
        return 2;
    }
    if (handle->inited != 1) {
        return 3;
    }

    handle->i2c_param.reg = INA219_REG_CONF;
    res = I2C_READ(handle);
    prev = handle->i2c_param.data;
    if (res != 0) {
        return 1;
    }
    prev &= ~(3 << 11); /* clear pga bit */
    prev |= pga << 11;  /* set pga bit */
    handle->i2c_param.data = prev;
    return I2C_WRITE(handle);
}

/**
 * @brief      get the pga
 * @param      handle pointer to an ina219 handle structure
 * @param[out] *pga pointer to an adc pga buffer
 * @return     status code
 *             - 0 success
 *             - 1 get pga failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ina219_get_pga(ina219_handle_t *handle, ina219_pga_t *pga)
{
    uint8_t res;
    uint16_t prev;

    if (handle == NULL) {
        return 2;
    }
    if (handle->inited != 1) {
        return 3;
    }

    handle->i2c_param.reg = INA219_REG_CONF;
    res = I2C_READ(handle);
    prev = handle->i2c_param.data;
    if (res != 0) {
        return 1;
    }
    *pga = (ina219_pga_t)((prev >> 11) & 0x03); /* get pga */

    return 0;
}

/**
 * @brief     set the bus voltage adc mode
 * @param     handle pointer to an ina219 handle structure
 * @param     mode adc mode
 * @return    status code
 *            - 0 success
 *            - 1 set bus voltage adc mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ina219_set_bus_voltage_adc_mode(ina219_handle_t *handle, ina219_adc_mode_t mode)
{
    uint8_t res;
    uint16_t prev;

    if (handle == NULL) {
        return 2;
    }
    if (handle->inited != 1) {
        return 3;
    }

    handle->i2c_param.reg = INA219_REG_CONF;
    res = I2C_READ(handle);
    prev = handle->i2c_param.data;
    if (res != 0) {
        return 1;
    }
    prev &= ~(0xF << 7); /* clear mode bit */
    prev |= mode << 7;   /* set mode bit */
    handle->i2c_param.data = prev;
    return I2C_WRITE(handle);
}

/**
 * @brief      get the bus voltage adc mode
 * @param      handle pointer to an ina219 handle structure
 * @param[out] mode pointer to an adc mode buffer
 * @return     status code
 *             - 0 success
 *             - 1 get bus voltage adc mode failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ina219_get_bus_voltage_adc_mode(ina219_handle_t *handle, ina219_adc_mode_t *mode)
{
    uint8_t res;
    uint16_t prev;

    if (handle == NULL) {
        return 2;
    }
    if (handle->inited != 1) {
        return 3;
    }

    handle->i2c_param.reg = INA219_REG_CONF;
    res = I2C_READ(handle);
    prev = handle->i2c_param.data;
    if (res != 0) {
        return 1;
    }
    *mode = (ina219_adc_mode_t)((prev >> 7) & 0xF); /* get mode */

    return 0;
}

/**
 * @brief     set the shunt voltage adc mode
 * @param     handle pointer to an ina219 handle structure
 * @param     mode adc mode
 * @return    status code
 *            - 0 success
 *            - 1 set shunt voltage adc mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ina219_set_shunt_voltage_adc_mode(ina219_handle_t *handle, ina219_adc_mode_t mode)
{
    uint8_t res;
    uint16_t prev;

    if (handle == NULL) {
        return 2;
    }
    if (handle->inited != 1) {
        return 3;
    }

    handle->i2c_param.reg = INA219_REG_CONF;
    res = I2C_READ(handle);
    prev = handle->i2c_param.data;
    if (res != 0) {
        return 1;
    }
    prev &= ~(0xF << 3); /* clear mode bit */
    prev |= mode << 3;   /* set mode bit */
    handle->i2c_param.data = prev;
    return I2C_WRITE(handle);
}

/**
 * @brief      get the shunt voltage adc mode
 * @param      handle pointer to an ina219 handle structure
 * @param[out] *mode pointer to an adc mode buffer
 * @return     status code
 *             - 0 success
 *             - 1 get shunt voltage adc mode failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ina219_get_shunt_voltage_adc_mode(ina219_handle_t *handle, ina219_adc_mode_t *mode)
{
    uint8_t res;
    uint16_t prev;

    if (handle == NULL) {
        return 2;
    }
    if (handle->inited != 1) {
        return 3;
    }

    handle->i2c_param.reg = INA219_REG_CONF;
    res = I2C_READ(handle);
    prev = handle->i2c_param.data;
    if (res != 0) {
        return 1;
    }
    *mode = (ina219_adc_mode_t)((prev >> 3) & 0xF); /* get mode */

    return 0;
}

/**
 * @brief     set the mode
 * @param     handle pointer to an ina219 handle structure
 * @param     mode chip mode
 * @return    status code
 *            - 0 success
 *            - 1 set mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ina219_set_mode(ina219_handle_t *handle, ina219_mode_t mode)
{
    uint8_t res;
    uint16_t prev;

    if (handle == NULL) {
        return 2;
    }
    if (handle->inited != 1) {
        return 3;
    }
    handle->i2c_param.reg = INA219_REG_CONF;
    res = I2C_READ(handle);
    prev = handle->i2c_param.data;
    if (res != 0) {
        return 1;
    }
    prev &= ~(0x7 << 0); /* clear mode bit */
    prev |= mode << 0;   /* set mode bit */
    handle->i2c_param.data = prev;
    res = I2C_WRITE(handle);
    if (res != 0) {
        return 1;
    }

    if ((mode >= INA219_MODE_SHUNT_VOLTAGE_TRIGGERED) &&
        (mode <= INA219_MODE_SHUNT_BUS_VOLTAGE_TRIGGERED)) {
        /* check mode */
        uint8_t m, mode1, mode2, t;

        mode1 = (prev >> 3) & 0xF;           /* get shunt adc mode */
        mode2 = (prev >> 7) & 0xF;           /* get bus adc mode */
        m = (mode1 > mode2) ? mode1 : mode2; /* get max mode */
        if (m <= 8)                          /* check mode */
        {
            ina219_delay_ms(1);
        } else {
            t = (uint8_t)(0.532 * pow(2, m - 8)) + 1; /* get time */
            ina219_delay_ms(t);
        }

        return 0;
    }
    return 0;
}

/**
 * @brief      get the mode
 * @param      handle pointer to an ina219 handle structure
 * @param[out] *mode pointer to a chip mode buffer
 * @return     status code
 *             - 0 success
 *             - 1 get mode failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ina219_get_mode(ina219_handle_t *handle, ina219_mode_t *mode)
{
    uint8_t res;
    uint16_t prev;

    if (handle == NULL) {
        return 2;
    }
    if (handle->inited != 1) {
        return 3;
    }

    handle->i2c_param.reg = INA219_REG_CONF;
    res = I2C_READ(handle);
    prev = handle->i2c_param.data;
    if (res != 0) {
        return 1;
    }
    *mode = (ina219_mode_t)((prev >> 0) & 0x7); /* get mode */

    return 0;
}

/**
 * @brief      read the shunt voltage
 * @param      handle pointer to an ina219 handle structure
 * @param[out] *raw pointer to raw data buffer
 * @param[out] *mV pointer to converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read shunt voltage failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ina219_read_shunt_voltage(ina219_handle_t *handle, int16_t *raw, float *mV)
{
    uint8_t res;
    union {
        uint16_t u;
        int16_t s;
    } u;

    if (handle == NULL) {
        return 2;
    }
    if (handle->inited != 1) {
        return 3;
    }

    handle->i2c_param.reg = INA219_REG_SHUNT_VOLTAGE;
    res = I2C_READ(handle);
    u.u = handle->i2c_param.data;
    if (res != 0) {
        return 1;
    }
    *raw = u.s;                   /* set the raw */
    *mV = (float)(*raw) / 100.0f; /* set the converted data */

    return 0;
}

/**
 * @brief      read the bus voltage
 * @param      handle pointer to an ina219 handle structure
 * @param[out] *raw pointer to raw data buffer
 * @param[out] *mV pointer to converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read bus voltage failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 math overflow
 *             - 5 conversion not ready
 * @note       none
 */
uint8_t ina219_read_bus_voltage(ina219_handle_t *handle, uint16_t *raw, float *mV)
{
    uint8_t res;

    if (handle == NULL) {
        return 2;
    }
    if (handle->inited != 1) {
        return 3;
    }

    handle->i2c_param.reg = INA219_REG_BUS_VOLTAGE;
    res = I2C_READ(handle);
    *raw = handle->i2c_param.data;
    if (res != 0) {
        return 1;
    }
    if (((*raw) & (1 << 0)) != 0) {
        return 4;
    }
    if (((*raw) & (1 << 1)) == 0) {
        return 5;
    }
    *raw = (*raw) >> 3;         /* right shift 3 */
    *mV = (float)(*raw) * 4.0f; /* set the converted data */

    return 0;
}

/**
 * @brief      read the current
 * @param      handle pointer to an ina219 handle structure
 * @param[out] *raw pointer to raw data buffer
 * @param[out] *mA pointer to converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read current failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ina219_read_current(ina219_handle_t *handle, int16_t *raw, float *mA)
{
    uint8_t res;
    union {
        uint16_t u;
        int16_t s;
    } u;

    if (handle == NULL) {
        return 2;
    }
    if (handle->inited != 1) {
        return 3;
    }

    handle->i2c_param.reg = INA219_REG_CURRENT;
    res = I2C_READ(handle);
    u.u = handle->i2c_param.data;
    if (res != 0) {
        return 1;
    }
    *raw = u.s;                                                 /* set the raw */
    *mA = (float)((double)(*raw) * handle->current_lsb * 1000); /* set the converted data */

    return 0;
}

/**
 * @brief      read the power
 * @param      handle pointer to an ina219 handle structure
 * @param[out] *raw pointer to raw data buffer
 * @param[out] *mW pointer to converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read power failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ina219_read_power(ina219_handle_t *handle, uint16_t *raw, float *mW)
{
    uint8_t res;

    if (handle == NULL) {
        return 2;
    }
    if (handle->inited != 1) {
        return 3;
    }

    handle->i2c_param.reg = INA219_REG_POWER;
    res = I2C_READ(handle);
    *raw = handle->i2c_param.data;
    if (res != 0) {
        return 1;
    }
    *mW = (float)((double)(*raw) * handle->current_lsb * 20.0 * 1000.0); /* set the converted data */

    return 0;
}

/**
 * @brief      get the calibration
 * @param      handle pointer to an ina219 handle structure
 * @param[out] *data pointer to a calibration data buffer
 * @return     status code
 *             - 0 success
 *             - 1 get calibration failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ina219_get_calibration(ina219_handle_t *handle, uint16_t *data)
{
    uint8_t res;

    if (handle == NULL) {
        return 2;
    }
    if (handle->inited != 1) {
        return 3;
    }

    handle->i2c_param.reg = INA219_REG_CALIBRATION;
    res = I2C_READ(handle);
    *data = handle->i2c_param.data;
    if (res != 0) {
        return 1;
    }

    return 0;
}

/**
 * @brief      calculate the calibration
 * @param      handle pointer to an ina219 handle structure
 * @param[out] calibration pointer to a calibration data buffer
 * @return     status code
 *             - 0 success
 *             - 1 calibration failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 r can't be zero
 *             - 5 pga is invalid
 * @note       none
 */
uint8_t ina219_calculate_calibration(ina219_handle_t *handle, uint16_t *calibration)
{
    uint8_t res;
    uint16_t prev;
    uint8_t pga;
    double v;

    if (handle == NULL) {
        return 2;
    }
    if (handle->inited != 1) {
        return 3;
    }
    if ((handle->r >= -0.000001f) && (handle->r <= 0.000001f)) /* check the r */
    {
        return 4;
    }

    handle->i2c_param.reg = INA219_REG_CONF;
    res = I2C_READ(handle);
    prev = handle->i2c_param.data;

    if (res != 0) {
        return 1;
    }
    pga = (prev >> 11) & 0x3; /* get pga */
    switch (pga)              /* select the pga */
    {
        case 0: {
            v = 0.04; /* 0.04 V */
            res = 0;  /* set ok */

            break;
        }
        case 1: {
            v = 0.08; /* 0.08 V */
            res = 0;  /* set ok */

            break;
        }
        case 2: {
            v = 0.16; /* 0.16 V */
            res = 0;  /* set ok */

            break;
        }
        case 3: {
            v = 0.32; /* 0.32 V */
            res = 0;  /* set ok */

            break;
        }
        default: {
            v = 0.0; /* 0.0 V */
            res = 1; /* set failed */

            break;
        }
    }
    if (res == 1) {
        return 5;
    }
    handle->current_lsb = v / handle->r / pow(2.0, 15.0);      /* current lsb */
    *calibration = (uint16_t)(0.04096 / (v / pow(2.0, 15.0))); /* set calibration */

    return 0;
}

/**
 * @brief     set the calibration
 * @param     handle pointer to an ina219 handle structure
 * @param     data calibration data
 * @return    status code
 *            - 0 success
 *            - 1 set calibration failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ina219_set_calibration(ina219_handle_t *handle, uint16_t data)
{
    uint8_t res;

    if (handle == NULL) {
        return 2;
    }
    if (handle->inited != 1) {
        return 3;
    }
    handle->i2c_param.reg = INA219_REG_CALIBRATION;
    handle->i2c_param.data = data;
    res = I2C_WRITE(handle);
    if (res != 0) {
        return 1;
    }

    return 0;
}

/**
 * @brief     initialize the chip
 * @param     ina219_handle pointer of pointer to an ina219 handle structure
 * @param     read_func I2C read interface
 * @param     write_func I2C write interface
 * @param     addr_pin address pin
 * @param     resistance current sampling resistance value
 * @return    status code
 *            - 0 success
 *            - 1 malloc failed
 *            - 2 i2c interface is NULL
 *            - 3 soft reset failed
 *            - 4 i2c read/write error \
 * @note      none
 */
uint8_t ina219_init(ina219_handle_t **ina219_handle,
                    ina219_i2c_read_func_t read_func,
                    ina219_i2c_write_func_t write_func,
                    ina219_address_t addr_pin,
                    double resistance)
{
    uint8_t res;
    uint16_t prev = 0;
    ina219_handle_t *handle = (ina219_handle_t *)malloc(sizeof(ina219_handle_t));

    if (handle == NULL) {
        return 1;
    }
    if (read_func == NULL) {
        return 2;
    }
    if (write_func == NULL) {
        return 2;
    }

    memset(handle, 0, sizeof(ina219_handle_t));
    handle->i2c_addr = addr_pin;
    handle->r = resistance;
    handle->current_lsb = 0;
    handle->i2c_read_func = read_func;
    handle->i2c_write_func = write_func;

    handle->i2c_param.address = addr_pin;

    handle->i2c_param.reg = INA219_REG_CONF;
    res = I2C_READ(handle);
    prev = handle->i2c_param.data;
    if (res != 0) {
        return 4;
    }

    /* set RST to 1 */
    prev |= 1 << 15;
    /* write into register */
    handle->i2c_param.data = prev;
    res = I2C_WRITE(handle);
    if (res != 0) {
        return 4;
    }
    ina219_delay_ms(10);
    /* read config again */
    res = I2C_READ(handle);
    prev = handle->i2c_param.data;
    if (res != 0) {
        return 4;
    }
    /* check the result */
    if ((prev & (1 << 15)) != 0) {
        return 4;
    }

    handle->inited = 1;
    *ina219_handle = handle;
    return 0;
}

/**
 * @brief     close the chip
 * @param     handle pointer to an ina219 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 handle is NULL
 *            - 2 handle is not initialized
 *            - 3 power down failed
 * @note      none
 */
uint8_t ina219_deinit(ina219_handle_t *handle)
{
    uint8_t res;
    uint16_t prev;

    if (handle == NULL) {
        return 1;
    }
    if (handle->inited != 1) {
        return 2;
    }

    handle->i2c_param.reg = INA219_REG_CONF;
    res = I2C_READ(handle);
    prev = handle->i2c_param.data;
    if (res != 0) {
        return 3;
    }

    /* set to power down */
    prev &= ~0x07;
    handle->i2c_param.data = prev;
    res = I2C_WRITE(handle);
    if (res != 0) {
        return 3;
    }
    handle->inited = 0;
    free(handle);

    return 0;
}

/**
 * @brief     set the chip register
 * @param     handle pointer to an ina219 handle structure
 * @param     reg register address
 * @param     data written data
 * @return    status code
 *            - 0 success
 *            - 1 handle is NULL
 *            - 2 handle is not initialized
 * @note      none
 */
uint8_t ina219_set_reg(ina219_handle_t *handle, uint8_t reg, uint16_t data)
{
    if (handle == NULL) {
        return 1;
    }
    if (handle->inited != 1) {
        return 2;
    }

    handle->i2c_param.reg = reg;
    handle->i2c_param.data = data;
    return I2C_WRITE(handle);
}

/**
 * @brief      get the chip register
 * @param      handle pointer to an ina219 handle structure
 * @param      reg register address
 * @param[out] *data pointer to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 handle is NULL
 *             - 2 handle is not initialized
 * @note       none
 */
uint8_t ina219_get_reg(ina219_handle_t *handle, uint8_t reg, uint16_t *data)
{
    if (handle == NULL) {
        return 1;
    }
    if (handle->inited != 1) {
        return 2;
    }

    uint8_t res;
    handle->i2c_param.reg = reg;
    res = I2C_READ(handle);
    *data = handle->i2c_param.data;
    return res;
}