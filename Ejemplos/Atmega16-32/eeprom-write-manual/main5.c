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


void AVRInit()
{
	DDRB = 0x01; // PB0 como salida
	PORTB = 0;
}

int main()
{
	AVRInit();

	// Escribe el caractér M en la dirección 0x50 de la eeprom.
    eeprom_write_byte((uint8_t*)0x050, 'M');
    // Lee la dirección 0x50 y si es igual a M enciende el led
    if(eeprom_read_byte((uint8_t*)0x050) == 'M')
        PORTB |= 0x01;  

	while(1)
	{}

	return 0;
}