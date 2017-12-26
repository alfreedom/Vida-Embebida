#include <i2c_c.h>
#include <lcdi2c.h>
#include <util/delay.h>

static uint8_t _io_setup;
static uint8_t _backlight_state;

static void lcd_sendCmd(uint8_t cmd)
{
	uint8_t send = (cmd & 0xF0) | (1 << EN) | (_backlight_state << BL);
	i2c_start();
	i2c_write(&send);
	i2c_stop();
	_delay_us(40);
	send = _backlight_state << BL;
	i2c_start();
	i2c_write(&send);
	i2c_stop();
	_delay_us(40);
	send = ((cmd << 4) | (1 << EN) | _backlight_state << BL);
	i2c_start();
	i2c_write(&send);
	i2c_stop();
	_delay_us(40);
	send = _backlight_state << BL;
	i2c_start();
	i2c_write(&send);
	i2c_stop();
	_delay_ms(2);
}
static void lcd_sendData(uint8_t data)
{
	uint8_t send = (data & 0xF0) | (1 << EN) | (_backlight_state << BL) | (1 << RS);
	i2c_start();
	i2c_write(&send);
	i2c_stop();
	_delay_us(40);
	send = _backlight_state << BL;	
	i2c_start();
	i2c_write(&send);
	i2c_stop();
	_delay_us(40);
	send = (data << 4) | (1 << EN) | (_backlight_state << BL) | (1 << RS);
	i2c_start();
	i2c_write(&send);
	i2c_stop();
	_delay_us(40);
	send = _backlight_state << BL;
	i2c_start();
	i2c_write(&send);
	i2c_stop();
		_delay_ms(2);

}

static void lcd_configOutputs(uint8_t addr) {
	i2c_init(addr);
	_backlight_state = 1;
	_io_setup = 0xFF;
}

void lcd_init(uint8_t address) {
	lcd_configOutputs(PCF_BASE_ADDRESS | (address & 0x07) << 1);
	lcd_reset();
}

void lcd_reset() {
	_delay_ms(20);
	lcd_sendCmd(0x33); /* Send init sequence */
	lcd_sendCmd(0x32); /* Send for 4 bit initialization of LCD  */
	lcd_sendCmd(0x28); /* 2 line, 5*7 matrix in 4-bit mode */
	lcd_sendCmd(0x0f); /* Display on cursor off */
	lcd_sendCmd(0x06); /* Increment cursor (shift cursor to right) */
	lcd_clear();

}

void lcd_clear() {
	/* Clear display screen */
	lcd_sendCmd(0x01); 
}

void lcd_returnHome() {
	lcd_sendCmd(0x02); /* Clear display screen */
}

void lcd_setCursor(uint8_t display_on, uint8_t show_cursor, uint8_t blink) {
	uint8_t mask = 0;
	if(display_on)
		mask |= 0x04;
	if(show_cursor)
		mask |= 0x02;
	if(blink)
		mask |= 0x01;

	lcd_sendCmd(0x08 | mask);
}
void lcd_gotoxy(uint8_t x, uint8_t y)
{
	uint8_t mask;
	if (y != 1)
		mask = 0x40;
	else
		mask = 0;
	mask += x - 1;

	lcd_sendCmd(0x80 | mask);
}

void lcd_displayShift(uint8_t display_shift, uint8_t direction) {
	uint8_t mask = 0;
	if(display_shift)
		mask |= 0x08;
	if(direction)
		mask |= 0x04;

	lcd_sendCmd(0x10 | mask);
}

void lcd_setCGRamAddress(uint8_t address) {
	lcd_sendCmd(0x40 | (address & 0x3F));
}
void lcd_print(char* str) {
	while(*str)
		lcd_sendData(*str++);
}
void lcd_putchar(char c) {
	lcd_sendData(c);
}

void lcd_backlight(uint8_t state) {
	_backlight_state = state ? 1 : 0;
	lcd_sendCmd(0);
}

