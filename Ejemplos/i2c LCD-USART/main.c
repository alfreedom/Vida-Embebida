#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "usart.h"
#include "lcd_i2c.h"

#define LCD_ADDRESS 0x7E // A2=1, A1=1 y A0=1 del módulo PC8574AT

LCD_I2C lcd;
//PCF8564 pcf(7);
int main(void)
{
	uint8_t count = 1;
	char readed;
	DDRB = 0;
	lcd.init(LCD_ADDRESS);
	Serial.init(9600);

	
		
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
			_delay_ms(40);
		}
		PORTB = 0; 
		
	}
}