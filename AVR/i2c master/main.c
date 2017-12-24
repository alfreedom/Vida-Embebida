/******************************************************
 * main.c
 *
 * Program Name:  i2c
 *         Date:  2017-12-24
 *       Author:  YOUR_NAME
 *      License:  YOUR_LICENSE
 *
 * Description:
 *  YOUR PROGRAM DESCRIPTION HERE.
 * 
 *****************************************************/
#include <avr/io.h> 
#include <util/delay.h> 
#include "i2c_master.h"


I2CMaster i2c;

uint8_t receive;
uint8_t buff[20] = {0x3C, 0x38, 0x3C, 0x38,
					0x3C, 0x38, 0x2C, 0x28, 
					0x2C, 0x28, 0x8C, 0x88,
					0x0C, 0x08, 0xfC, 0xf8,
					0x0C, 0x08, 0x6C, 0x68};

void AVRInit()
{
	// Intilize device at address 0x07 (include RD/WR bit)
	i2c.init(0x07E);
	DDRB = 0xFF;
}

int main()
{
	// Initialize the AVR modules
	AVRInit();

	// send a single byte
	i2c.start();
	i2c.write(0xFF);
	i2c.stop();

	// read single byte
	i2c.start();
	receive = i2c.read();
	i2c.stop();

	// send multiple bytes
	i2c.start();
	i2c.write(buff, 20);
	i2c.stop();

	// read multiple bytes
	i2c.start();
	i2c.read(buff, 5);
	i2c.stop();

	// Infinite loop
	while(1)
	{
		i2c.start();
		i2c.write(0x6D);
		i2c.write(0x69);
		i2c.write(0x6D);
		i2c.write(0x69);
		i2c.stop();
		_delay_ms(1000);
	}

	return 0;
}
