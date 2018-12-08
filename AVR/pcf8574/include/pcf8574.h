/***************************************************************************************
 * pcf8574.h
 * 
 *        Autor:  Alfredo Orozco de la Paz      
 *        Fecha:  Septiembre 2017
 *   Procesador:  ATmega32
 *   Frecuencia:  16 MHz
 *      Familia:  AVR-mega
 *   Compilador:  GNU avr-gcc
 *
 *
 *        Copyrigth© 2017 Alfredo Orozco
 * 
 ***************************************************************************************/

#ifndef PCH8574_H_
#define PCH8574_H_

#include <stdint.h>
#include "i2c_master.h"

class PCF8574 : public I2CMaster
{

	private:
		uint8_t io_setup;
	public:

		PCF8574();
		void setInputs(uint8_t pin_mask);
		void setOutputs(uint8_t pin_mask);
		uint8_t readInputs();
		uint8_t read();
		void write(uint8_t data);
		
};

#endif //PCH8574_H_
