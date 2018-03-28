/***************************************************************************************
 * i2c_master.h
 * 
 *        Autor:  Alfredo Orozco de la Paz      
 *        Fecha:  Marzo 2018
 *   Procesador:  ATmega32
 *   Frecuencia:  16 MHz
 *      Familia:  AVR-mega
 *   Compilador:  GNU avr-gcc
 *
 *
 *        Copyrigth© 2017 Alfredo Orozco
 * 
 ***************************************************************************************/

#ifndef _I2C_MASTER_H_
#define _I2C_MASTER_H_

#include <stdint.h>

#define SCL_CLOCK  10000L

class I2CMaster {

	public:

		typedef enum{ 
			WRITE = 0,
			READ = 1
		}Start_t;

		I2CMaster();
		void init(uint8_t address = 0, long scl_clock = SCL_CLOCK);
		uint8_t start(Start_t rw = I2CMaster::WRITE);
		void stop(void);
		uint8_t write(uint8_t data);
		uint8_t write(uint8_t* data, uint16_t count);
		uint8_t read(uint8_t* data, uint16_t count);
		uint8_t read();
	protected:
		uint8_t address;
};

#endif // _I2C_MASTER_H_