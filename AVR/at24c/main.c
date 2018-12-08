/******************************************************
 * main.c
 *
 * Program Name:  at24c
 *         Date:  2017-12-28
 *       Author:  YOUR_NAME
 *      License:  YOUR_LICENSE
 *
 * Description:
 *  YOUR PROGRAM DESCRIPTION HERE.
 * 
 *****************************************************/
#include <avr/io.h> 
#include <util/delay.h> 
#include "at24c.h"

#define EEMPROM_ADDRESS 0xA0

AT24C eeprom;

void AVRInit()
{
	char save = 'k';
	char read = 'l';

	DDRB = 0x01;
	eeprom.init(EEMPROM_ADDRESS);

	//eeprom.write(0x40, save);
	read = eeprom.read(0x40);

	if(read == save)
		PORTB = 0x01;
}

int main()
{
	// Initialize the AVR modules
	AVRInit();

	// Infinite loop
	while(1)
	{
	}

	return 0;
}
