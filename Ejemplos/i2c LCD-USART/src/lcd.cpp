#include "lcd.h"
#include <util/delay.h>

LCD_I2C::LCD_I2C(uint8_t address){
	pcf_driver.init(address);
}
void LCD_I2C::init() {
	// Dirección 0 del chip pcf8574: A2 = 1, A1 = 1, A0 = 1
	this->pcf_driver.setOutputs(0xFF);
	while(1){
		pcf_driver.write(8);
		_delay_ms(400);
		pcf_driver.write(0);
		_delay_ms(400);
	}
}
void LCD_I2C::clearDisplay() {
	this->pcf_driver.write(0x01);
}
void LCD_I2C::returnHome() {
	this->pcf_driver.write(0x02);
}
void LCD_I2C::entryModeSet() {

}
void LCD_I2C::displayControl() {

}
void LCD_I2C::cursorDisplayShift() {

}
void LCD_I2C::functionSet() {

}
void LCD_I2C::setDRamAddress() {

}
void LCD_I2C::setGRamAddress() {

}
void LCD_I2C::writeData() {

}
void LCD_I2C::readData() {

}