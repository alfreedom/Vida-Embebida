//#include "i2c_c.h"
#define SCL_CLOCK 100000L

#include <stdint.h>
#include <util/twi.h>
uint8_t _address;

void i2c_init(uint8_t address)
{
	_address = address;
	TWSR = 0;
	TWBR = ((F_CPU / SCL_CLOCK) - 16) / 2;
}

uint8_t i2c_start()
{
	uint8_t status;

	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)))
		;

	status = TW_STATUS & 0xF8;
	if ((status != TW_START) && (status != TW_REP_START))
		return 0;

	TWDR = _address;
	TWCR = (1 << TWINT) | (1 << TWEN);

	while (!(TWCR & (1 << TWINT)))
		;

	status = TW_STATUS & 0xF8;
	if ((status != TW_MT_SLA_ACK) && (status != TW_MR_SLA_ACK))
		return 0;

	return 1;
}
void i2c_stop(void)
{
	// Send the stop condition
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
	//wait for the stop condition ends.
	while (TWCR & (1 << TWSTO))
		;
}

uint8_t i2c_write(uint8_t *data, uint8_t count)
{

	for(int i = 0; i < count; i++)
	{
		TWDR = data[i];
		TWCR = (1 << TWINT) | (1 << TWEN);

		while (!(TWCR & (1 << TWINT)))
			;

		if ((TW_STATUS & 0xF8) != TW_MT_DATA_ACK)
			return 0;
	}

	return 1;
}

uint8_t i2c_read(uint8_t *data, uint8_t count)
{
	uint8_t i = 0;

	while (count)
	{
		// If receive more that 1 data, send ACK to the end of the transmission
		// Else, it it's only one data or the las data to receive, don't send
		// the ACK to the slave.
		if (count-- > 1)
			TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
		else
			TWCR = (1 << TWINT) | (1 << TWEN);

		// wait for end of transmission
		while (!(TWCR & (1 << TWINT)))
			;
		// Store received data from TWDR
		data[i++] = TWDR;
	}

	return i;
}
