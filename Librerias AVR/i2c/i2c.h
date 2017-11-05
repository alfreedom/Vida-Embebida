/***************************************************************************************
 * i2c.h
 * 
 *        Autor:  Alfredo Orozco de la Paz      
 *        Fecha:  Septiembre 2017
 *   Procesador:  ATmega328p
 *   Frecuencia:  16 MHz
 *      Familia:  AVR-mega
 *   Compilador:  GNU avr-gcc
 *
 *
 *        Copyrigth© 2017 Alfredo Orozco
 * 
 ***************************************************************************************/

#ifndef _I2C_H_
#define _I2C_H_

#include <stdint.h>
#include <util/twi.h>

#define SCL_CLOCK  100000L

class I2C {
public:
    I2C();
    void begin(uint8_t address);
    uint8_t start();
    void stop(void);
    uint8_t write(uint8_t data);
	uint8_t read(uint8_t* data, uint8_t count = 1);
private:
    uint8_t address;
};

#endif