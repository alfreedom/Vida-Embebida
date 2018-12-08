/***************************************************************************************
 * lcd16x2_i2c.cpp
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

#include <lcd16x2_i2c.h>
#include <util/delay.h>


LCD_I2C::LCD_I2C(){
	this->backlight_state = 1;
}

void LCD_I2C::init(uint8_t address)
{
	PCF8574::init(address);
	_delay_ms(20);
	PCF8574::setOutputs(0xFF);
	PCF8574::write(0xFF);
	this->reset();
}

void LCD_I2C::reset() {
	this->sendCmd(0x33);
	this->sendCmd(0x32); /* Send for 4 bit initialization of LCD  */
	this->sendCmd(0x28); /* 2 line, 5*7 matrix in 4-bit mode */
	this->sendCmd(0x0C); /* Display on cursor off */
	this->sendCmd(0x06); /* Increment cursor (shift cursor to right) */
	this->clear();

}

void LCD_I2C::clear() {
	/* Clear display screen */
	sendCmd(0x01); 
}

void LCD_I2C::returnHome() {
	sendCmd(0x02); /* Clear display screen */
}

void LCD_I2C::setCursor(uint8_t display_on, uint8_t show_cursor, uint8_t blink) {
	this->sendCmd(0x08 | (display_on ? 0x04 : 0) | (show_cursor ? 0x02 : 0) | (blink ? 0x01 : 0));
}
void LCD_I2C::gotoxy(uint8_t x, uint8_t y)
{
	this->sendCmd(0x80 | ((y != 1 ? 0x40 : 0) + x - 1));
}

void LCD_I2C::shiftDisplay(uint8_t display_shift, uint8_t direction) {
	this->sendCmd(0x10 | (display_shift ? 0x08 : 0) | (direction ? 0x40 : 0));
}

void LCD_I2C::setCGRamAddress(uint8_t address) {
	this->sendCmd(0x40 | (address & 0x3F));
}
void LCD_I2C::print(char* str) {
	while(*str)
		sendData(*str++);
}

void LCD_I2C::print(char c) {
	sendData(c);
}

void LCD_I2C::backlight(uint8_t state) {
	this->backlight_state = state ? 1 : 0;
	sendCmd(0);
}

void LCD_I2C::sendCmd(uint8_t cmd)
{
	PCF8574::write(((cmd & 0xF0)) | (1 << LCD_EN) | (this->backlight_state << LCD_BL));
	_delay_us(40);
	PCF8574::write(this->backlight_state << LCD_BL);
	_delay_us(40);
	PCF8574::write((cmd << 4) | (1 << LCD_EN) | (this->backlight_state << LCD_BL));
	_delay_us(40);
	PCF8574::write(this->backlight_state << LCD_BL);
	_delay_ms(2);
}
void LCD_I2C::sendData(uint8_t data)
{
	PCF8574::write(((data & 0xF0)) | (1 << LCD_EN) | (this->backlight_state << LCD_BL) | (1 << LCD_RS));
	_delay_us(40);
	PCF8574::write(this->backlight_state << LCD_BL);
	_delay_us(40);
	PCF8574::write((data << 4) | (1 << LCD_EN) | (this->backlight_state << LCD_BL) | (1 << LCD_RS));
	_delay_us(40);
	PCF8574::write(this->backlight_state << LCD_BL);
	_delay_ms(2);
}