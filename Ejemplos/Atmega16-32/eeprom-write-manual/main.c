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
#include <string.h>

uint8_t EEMEM text[] ="Texto";
float EEMEM flotante = 5.55;
int EEMEM entero = 35;
uint16_t EEMEM word = 0xDEAD;

int main(void)
{
	DDRB = 0x00;
	char eeprom_text[6];
	
	eeprom_read_block(eeprom_text, &text, 6);

	if(eeprom_read_word(&word) == 0xDEAD && 
	   eeprom_read_float(&flotante) == 5.55 && 
	   strcmp(eeprom_text, "Texto") == 0)
		PORTB = 1;

	
	while(1)
	{}
}