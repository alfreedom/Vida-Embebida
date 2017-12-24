/******************************************************
 * main.c
 *
 * Program Name:  usart-lib-example
 *       Author:  Alfredo Orozco
 *         Date:  DATE
 *      License:  MTI
 *
 * Description:
 * 	Use the usart-lib library to send and receive data
 * 	from serial port.
 * 
 *****************************************************/
#include <avr/io.h> 
#include <util/delay.h> 
#include "usart.h"

void AVRInit()
{
	 DDRB = 0xFF;			// PORTB as Output
	 Serial.begin(115200);	// Initialize serial to 115200 baud
}	

int main()
{
	char cad[100];
	char s[10];

 	// Initialize the AVR modules
	AVRInit();
	// Print a new line
	Serial.println();

	// Print ascii values and codes
	for (size_t i = 0; i <= 255; i++)
	{
		for (size_t j = 0; j < 8; j++)
			s[j] = (i<<j) & 0x80 ? '1' : '0';

		// Format the string whit the nomber
		sprintf(cad, "CHAR: %c   BIN: %s  DEC: %d  HEX: 0x%.2X", i, s, i, i);
		// Send formated string to serial port
		Serial.println(cad);
		
	}
	Serial.print(100);		// Prints a int number
	Serial.print(-34500);	// Prints a int number
	Serial.print(3.1416);	// Prints a decimal number
	Serial.print(16000000);	// Prints a big number

	// Turn ON PORTB leds
	PORTB = 0xFF;

	// Infinite loop
 	while(1)
 	{}

 	return 0;
}
