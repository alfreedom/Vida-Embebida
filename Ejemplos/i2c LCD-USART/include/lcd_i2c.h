#ifndef LCD_I2C_H_
#define LCD_I2C_H_
#include "pcf8574.h"

#define RS  0
#define WR  1
#define EN  2
#define BL	3


class LCD_I2C : public PCF8574
{
	public:
		LCD_I2C();
		void backlight(uint8_t state);
		void init(uint8_t address = 0);
		void reset();
		void clear();
		void returnHome();
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
		uint8_t mask;
		
};
#endif //LCD_I2C_H_
