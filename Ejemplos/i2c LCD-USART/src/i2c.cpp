/***************************************************************************************
 * i2c.cpp
 * 
 *        Autor:  Alfredo Orozco de la Paz      
 *        Fecha:  Septiembre 2017
 *   Procesador:  ATmega16/32/24/88/168/328 etc...
 *   Frecuencia:  16 MHz
 *      Familia:  AVR-mega
 *   Compilador:  GNU avr-gcc
 *
 *
 *        Copyrigth© 2017 Alfredo Orozco
 * 
 ***************************************************************************************/

#include "i2c.h"
#include <util/delay.h>
I2C::I2C() {}

// Initialize the I2C Module
void I2C::init(uint8_t address, long scl_clock) {
    this->address = address;
    TWSR = 0;
    TWBR = ((F_CPU/scl_clock)-16)/2;
    PORTC |= (1<<PC4) | (1<<PC5);
}

uint8_t I2C::start() {
	
	// Send start condition
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    // wait for start condition ends
    while(!(TWCR & (1<<TWINT)));

    // If error sending start, return 0
    if (((TW_STATUS & 0xF8) != TW_START) && ((TW_STATUS & 0xF8) != TW_REP_START)) 
        return 0;

    // Send device address to device
    TWDR = address;
    TWCR = (1<<TWINT) | (1<<TWEN);

    // wait for transmission
    while(!(TWCR & (1<<TWINT)));
    // if not ACK received, error, return 0
    if (((TW_STATUS & 0xF8) != TW_MT_SLA_ACK) && ((TW_STATUS & 0xF8) != TW_MR_SLA_ACK)) 
        return 0;

    return 1;
}

void I2C::stop(void) {
	// Send stop condition
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
    // whait for stop condition ends
    while(TWCR & (1<<TWSTO));
}

uint8_t I2C::write(uint8_t data) {
	
    TWDR = data;
    TWCR = (1<<TWINT) | (1<<TWEN);

    while(!(TWCR & (1<<TWINT)));

    if ((TW_STATUS & 0xF8) != TW_MT_DATA_ACK) 
        return 0;

    return 1;
}

uint8_t I2C::write(uint8_t* data, uint16_t count) {
	
	for (uint16_t i = 0; i < count; ++i)
	{
	    TWDR = *data++;
	    TWCR = (1<<TWINT) | (1<<TWEN);

	    while(!(TWCR & (1<<TWINT)));

	    if ((TW_STATUS & 0xF8) != TW_MT_DATA_ACK) 
	        return 0;
	    _delay_ms(2);
	}

    return 1;
}

uint8_t I2C::read(uint8_t* data, uint16_t count){
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

uint8_t I2C::read(){

	TWCR = (1<<TWINT) | (1<<TWEN);

	while( !(TWCR & (1<<TWINT)) );
	return TWDR;

}


