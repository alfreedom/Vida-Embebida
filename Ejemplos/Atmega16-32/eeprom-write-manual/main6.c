/******************************************************
 * main.c
 *
 * Program Name:  eeprom-write-manual
 *         Date:  2018-04-15
 *       Author:  Alfredo Orozco
 *      License:  GPL
 *
 * Description:
 * 
 *  Ejemplo de programación de la memoria EEPROM del
 *  microcontrolador ATmega32 utilizando los registros.
 * 
 *****************************************************/
#include <avr/io.h>
#include <avr/eeprom.h>

#define BLOCK_SIZE 13
uint8_t text[] ="Vida Embebida";

int main(void)
{
	int i;
	uint16_t address = 0x060;
	uint8_t readed[BLOCK_SIZE];
	// Escribe en texto en la EEPROM
	eeprom_write_block((const void *)text, address, BLOCK_SIZE);

	// Lee el texto de la EEPROM
	eeprom_read_block ((void *)readed, address, BLOCK_SIZE);

	for(i = 0; i< BLOCK_SIZE; i++)
	{
		if(text[i] != readed[i])
			while(1);
	}
	PORTB = 1;

	while(1)
	{
		//do nothing
	}
}