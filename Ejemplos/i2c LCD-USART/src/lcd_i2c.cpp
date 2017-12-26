#include <lcd_i2c.h>
#include <util/delay.h>


LCD_I2C::LCD_I2C(uint8_t address){
	this->pcf_driver.init(address);
	this->backlight_state = 1;
}

void LCD_I2C::init() {
	// Dirección 0 del chip pcf8574: A2 = 1, A1 = 1, A0 = 1
	_delay_ms(20);
	this->pcf_driver.setOutputs(0xFF);
	this->pcf_driver.write(0xFF);
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
	this->mask = 0;
	if(display_on)
		this->mask |= 0x04;
	if(show_cursor)
		this->mask |= 0x02;
	if(blink)
		this->mask |= 0x01;

	this->sendCmd(0x08 | this->mask);
}
void LCD_I2C::gotoxy(uint8_t x, uint8_t y)
{
	if (y != 1)
		this->mask = 0x40;
	else
		this->mask = 0;
	this->mask += x - 1;

	this->sendCmd(0x80 | this->mask);
}

void LCD_I2C::shiftDisplay(uint8_t display_shift, uint8_t direction) {
	this->mask = 0;
	if(display_shift)
		this->mask |= 0x08;
	if(direction)
		this->mask |= 0x40;

	this->sendCmd(0x10 | this->mask);
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
	this->pcf_driver.write(((cmd & 0xF0)) | (1 << EN) | (this->backlight_state << BL));
	_delay_us(40);
	this->pcf_driver.write(this->backlight_state << BL);
	_delay_us(40);
	this->pcf_driver.write((cmd << 4) | (1 << EN) | (this->backlight_state << BL));
	_delay_us(40);
	this->pcf_driver.write(this->backlight_state << BL);
	_delay_ms(2);
}
void LCD_I2C::sendData(uint8_t data)
{
	this->pcf_driver.write(((data & 0xF0)) | (1 << EN) | (this->backlight_state << BL) | (1 << RS));
	_delay_us(40);
	this->pcf_driver.write(this->backlight_state << BL);
	_delay_us(40);
	this->pcf_driver.write((data << 4) | (1 << EN) | (this->backlight_state << BL) | (1 << RS));
	_delay_us(40);
	this->pcf_driver.write(this->backlight_state << BL);
	_delay_ms(2);
}