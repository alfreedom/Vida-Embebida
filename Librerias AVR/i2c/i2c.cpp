/***************************************************************************************
 * i2c.cpp
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

#include "i2c.h"

I2C::I2C() {
  address=0; 
}

void I2C::begin(uint8_t address) {
    this->address = address;
    TWSR = 0;
    TWBR = ((F_CPU/SCL_CLOCK)-16)/2;
    PORTC |= (1<<PC4) | (1<<PC5);
}

uint8_t I2C::start() {
	uint8_t status;
	
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    while(!(TWCR & (1<<TWINT)));

    status = TW_STATUS & 0xF8;
    if ((status != TW_START) && (status != TW_REP_START)) 
        return 1;

    TWDR = address;
    TWCR = (1<<TWINT) | (1<<TWEN);

    while(!(TWCR & (1<<TWINT)));

    status = TW_STATUS & 0xF8;
    if ((status != TW_MT_SLA_ACK) && (status != TW_MR_SLA_ACK)) 
        return 1;


    return 0;
}
void I2C::stop(void) {
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
    while(TWCR & (1<<TWSTO));
}

uint8_t I2C::write(uint8_t data) {
	
    TWDR = data;
    TWCR = (1<<TWINT) | (1<<TWEN);

    while(!(TWCR & (1<<TWINT)));

    if ((TW_STATUS & 0xF8) != TW_MT_DATA_ACK) 
        return 1;

    return 0;
}

uint8_t I2C::read(uint8_t* data, uint8_t count){
	uint8_t i = 0;

	while(count)
	{
		if(count-- > 1)
			TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
		else 
			TWCR = (1<<TWINT) | (1<<TWEN);

		while( !(TWCR & (1<<TWINT)) );
		data[i++] = TWDR;
	}

	return i;
}


