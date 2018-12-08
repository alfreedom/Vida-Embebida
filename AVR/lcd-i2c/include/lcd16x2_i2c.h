/***************************************************************************************
 * lcd16x2_i2c.h
 * 
 *        Autor:  Alfredo Orozco de la Paz      
 *        Fecha:  Septiembre 2017
 *   Procesador:  ATmega32
 *   Frecuencia:  16 MHz
 *      Familia:  AVR-mega
 *   Compilador:  GNU avr-gcc
 *
 *
 *        Copyrigth© 2017 Alfredo Orozco
 * 
 ***************************************************************************************/

#ifndef LCD16X2_I2C_H_
#define LCD16X2_I2C_H_
#include "pcf8574.h"

#define LCD_RS  0
#define LCD_WR  1
#define LCD_EN  2
#define LCD_BL	3


class LCD_I2C : public PCF8574
{
	public:
		LCD_I2C();
		void init(uint8_t address);
		void reset();
		void clear();
		void returnHome();
		void backlight(uint8_t state);
		void setCursor(uint8_t display_on, uint8_t show_cursor, uint8_t blink);
		void gotoxy(uint8_t x, uint8_t y);
		void shiftDisplay(uint8_t display_shift, uint8_t direction);
		void setCGRamAddress(uint8_t address);
		void print(char* str);
		void print(char c);
	private: 
		void sendCmd(uint8_t cmd);
		void sendData(uint8_t data);
		uint8_t backlight_state;
		
};
#endif //LCD16X2_I2C_H_
