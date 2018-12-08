/***************************************************************************************
 * i2c_master.cpp
 * 
 *        Autor:  Alfredo Orozco de la Paz      
 *        Fecha:  Marzo 2018
 *   Procesador:  ATmega32
 *   Frecuencia:  16 MHz
 *      Familia:  AVR-mega
 *   Compilador:  GNU avr-gcc
 *
 *
 *        Copyrigth© 2018 Alfredo Orozco
 * 
 ***************************************************************************************/
#include <util/twi.h>
#include <util/delay.h>
#include "i2c_master.h"

#define I2CMASTER_TIMEOUT 100
static int timeout;

I2CMaster::I2CMaster() {}

// Initialize the I2C Module in Master mode
void I2CMaster::init(uint8_t address, long scl_clock) {
    this->address = address;
    TWSR = 0;
    TWBR = ((F_CPU/scl_clock)-16)/2;
}

uint8_t I2CMaster::start(Start_t rw)
{
	timeout = 0;
	// Send start condition
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    // wait for start condition ends
    while(!(TWCR & (1<<TWINT)) && (timeout++ < I2CMASTER_TIMEOUT));

    // If error sending start, return 0
    if (((TW_STATUS & 0xF8) != TW_START) && ((TW_STATUS & 0xF8) != TW_REP_START)) 
        return 0;

    // Send device address to device
		if(rw)
    	TWDR = address | 1;
		else
    	TWDR = address;
			
    TWCR = (1<<TWINT) | (1<<TWEN);

	timeout = 0;
    // wait for transmission
    while(!(TWCR & (1<<TWINT)) && (timeout++ < I2CMASTER_TIMEOUT));
    // if not ACK received, error, return 0
    if (((TW_STATUS & 0xF8) != TW_MT_SLA_ACK) && ((TW_STATUS & 0xF8) != TW_MR_SLA_ACK)) 
        return 0;

    return 1;
}

void I2CMaster::stop(void) {
	timeout=0;
	// Send stop condition
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
    // whait for stop condition ends
    while(TWCR & (1<<TWSTO) && (timeout++ < I2CMASTER_TIMEOUT));
}

uint8_t I2CMaster::write(uint8_t data) {
	
    TWDR = data;
    TWCR = (1<<TWINT) | (1<<TWEN);

	timeout=0;
    while(!(TWCR & (1<<TWINT)) && (timeout++ < I2CMASTER_TIMEOUT));

    if ((TW_STATUS & 0xF8) != TW_MT_DATA_ACK) 
        return 0;

    return 1;
}

uint8_t I2CMaster::write(uint8_t* data, uint16_t count) {
	
	for (uint16_t i = 0; i < count; ++i)
	{
	    TWDR = *data++;
	    TWCR = (1<<TWINT) | (1<<TWEN);

		timeout=0;
	    while(!(TWCR & (1<<TWINT)) && (timeout++ < I2CMASTER_TIMEOUT));

	    if ((TW_STATUS & 0xF8) != TW_MT_DATA_ACK) 
	        return 0;
	    _delay_ms(2);
	}

    return 1;
}

uint8_t I2CMaster::read(uint8_t* data, uint16_t count){
	uint8_t i = 0;

	while(count)
	{
		if(count-- > 1)
			TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
		else 
			TWCR = (1<<TWINT) | (1<<TWEN);
	
		timeout=0;
		while( !(TWCR & (1<<TWINT)) && (timeout++ < I2CMASTER_TIMEOUT));
		data[i++] = TWDR;
	}

	return i;

}

uint8_t I2CMaster::read(){

	TWCR = (1<<TWINT) | (1<<TWEN);
	
	timeout=0;
	while( !(TWCR & (1<<TWINT)) && (timeout++ < I2CMASTER_TIMEOUT));
	return TWDR;

}


