/**
 * Manejo del bus i2c de los AVR en modo maestro
 * 
*/
#ifndef _I2C_C_H_
#define _I2C_C_H_

#include <stdint.h>
#include <util/twi.h>

#define SCL_CLOCK 100000L

void i2c_init(uint8_t address);
uint8_t i2c_start();
void i2c_stop();
uint8_t i2c_write(uint8_t *data, uint8_t count = 1);
uint8_t i2c_read(uint8_t *data, uint8_t count = 1);

#endif