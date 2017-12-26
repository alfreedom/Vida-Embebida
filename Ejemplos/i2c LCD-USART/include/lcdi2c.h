#ifndef LCDI2C_C_H_
#define LCDI2C_C_H_

#define PCF_BASE_ADDRESS 0x70

#define RS 0
#define WR 1
#define EN 2
#define BL 3

void lcd_backlight(uint8_t state);
void lcd_init(uint8_t address);
void lcd_reset();
void lcd_clear();
void lcd_returnHome();
void lcd_setCursor(uint8_t display_on, uint8_t show_cursor, uint8_t blink);
void lcd_gotoxy(uint8_t x, uint8_t y);
void lcd_displayShift(uint8_t display_shift, uint8_t direction);
void lcd_setCGRamAddress(uint8_t address);
void lcd_print(char *str);
void lcd_putchar(char c);

#endif //LCDI2C_H_
