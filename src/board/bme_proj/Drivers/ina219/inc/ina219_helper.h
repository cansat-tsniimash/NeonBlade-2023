/*
 * pcu_inahelpers.h
 *
 *  Created on: Jun 10, 2019
 *      Author: kirs
 */

#ifndef INA219_HELPER_H_
#define INA219_HELPER_H_

#include "ina219.h"
#include <stdio.h>
#include "main.h"

#define INA_CURRENT_LSB         ((ina219_float_t)(3.f/0x8000))
#define INA_POWER_LSB           ((ina219_float_t)(20*INA_CURRENT_LSB))
#define INA_VOLTAGE_BUS_LSB     0.004
#define INA_SHUNT_RES			0.1
#define INA_VOLTAGE_SHUNT_LSB   0.00001

int ina219_init_default(ina219_t * self, I2C_HandleTypeDef *hi2c, ina219_i2c_addr_t addr, uint32_t timeout);

// Current is given in amperes, power is in watts
int ina219_read(ina219_t * self, float * current, float * power);

float ina219_power_convert(ina219_t * hina, uint16_t power);

float ina219_current_convert(ina219_t * hina, int16_t current);

float ina219_bus_voltage_convert(ina219_t * hina, uint16_t voltage);

float ina219_shunt_voltage_convert(ina219_t * hina, int16_t voltage);

#endif /* INA219_H_ */
