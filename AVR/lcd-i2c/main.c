/******************************************************
 * main.c
 *
 * Program Name:  lcd-i2c
 *         Date:  2017-12-28
 *       Author:  Alfredo Orozco de la Paz
 *      License:  MIT
 *
 *  Copyright© 2017 Alfredo Orozco
 * 
 * Description:
 * 	Ejemplo de control de un Display 16x2 con el
 *  chip pc8574 usando protocolo i2c.
 * 
 * 	www.vidaembebida.wordpress.com
 * 
 *****************************************************/
#include <avr/io.h> 
#include <util/delay.h>
#include "lcd16x2_i2c.h"

LCD_I2C lcd;

void AVRInit()
{
	DDRB = 0xFF;
	lcd.init(0x7E);
}

int main()
{
	// Initialize the AVR modules
	AVRInit();

	lcd.gotoxy(4,1);
	lcd.print("LCD i2c AVR");
	lcd.gotoxy(2,2);
	lcd.print("VIDA  EMBEBIDA");
	// Infinite loop
	while(1)
	{
	}

	return 0;
}
