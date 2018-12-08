/******************************************************
 * main.c
 *
 * Program Name:  usart-example
 *       Author:  Alfredo Orozco
 *         Date:  DATE
 *      License:  MIT
 *
 * Description:
 * 	Use the usart-lib library to send and receive data
 * 	from serial port.
 * 
 *****************************************************/
#include <avr/io.h> 
#include <util/delay.h> 
#include "usart.h"

void printData(uint8_t d);
void onReceive(uint8_t c);

void AVRInit()
{
	 DDRB = 0x01;			// PORTB as Output
	 Serial.init(9600, onReceive);	// Initialize serial to 9600 baud
}	

int main()
{
	
 	// Initialize the AVR modules
	AVRInit();
	// Print a new line
	Serial.println();

	// Infinite loop
 	while(1)
 	{
		 if(Serial.available())
		 {
			//Serial.print("From Polling:\t");
			//printData(Serial.read());
		 }
	}

 	return 0;
}

void onReceive(uint8_t c)
{
	Serial.print("From interrupt:\t");
	printData(c);
}

void printData(uint8_t d)
{
	char cad[100] = "";
	char s[9];
	char *_s = s;
	PORTB = 0x01;
	// Generate binary string
	for (size_t j = 0; j < 8; j++)
	{
		if (j == 4)
			*_s++ = ' ';
		*_s++ = (d << j) & 0x80 ? '1' : '0';
	}
	// Format the string whit the number
	sprintf(cad, "CHAR: %c\tBIN: %s\tDEC: %d HEX: 0x%.2X", d, s, d, d);
	// Send formated string to serial port
	Serial.println(cad);
	Serial.flush();
	PORTB = 0;
}
