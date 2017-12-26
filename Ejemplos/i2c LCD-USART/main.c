#define _DVK501_M16_EX_ 1
#include <avr/io.h>
#include <util/delay.h>
#include "lcd_i2c.h"
#include <usart.h>
#include <stdio.h>
//#include <pcf8574.h>
int cursorX=1;
int cursorY=1;

LCD_I2C lcd(7);
//PCF8564 pcf(7);
int main(void)
{
	uint8_t count = 1;
	char readed;
	lcd.init();
	Serial.init(9600);
	DDRB = 0;

	
		
	while (1)
	{
		if(Serial.available())
		{	
			if(count == 16){
				lcd.clear();
				count = 0;
			}
			PORTB = 0xFF;
			readed = Serial.read();
			Serial.print(readed);
			lcd.print(readed);
			count++;
		}
		PORTB = 0; 
		
	}
}