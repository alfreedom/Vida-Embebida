#ifndef LCD_I2C16X2_H_
#define LCD_I2C16X2_H_
#include "pcf8574.h"

class LCD_I2C {
	public:
		LCD_I2C(uint8_t address);
		void init();
		void clearDisplay();
		void returnHome();
		void entryModeSet();
		void displayControl();
		void cursorDisplayShift();
		void functionSet();
		void setDRamAddress();
		void setGRamAddress();
		void writeData();
		void readData();

	private: 
		PCF8574 pcf_driver;
};
#endif //LCD_I2C16X2_H_
