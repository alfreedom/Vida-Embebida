
#include <util/delay.h>
#include "at24c.h"

AT24C::AT24C() {
}

void AT24C::write(uint16_t address, uint8_t data) {
	I2CMaster::start();
	I2CMaster::write(address >> 8);
	I2CMaster::write(address);
	I2CMaster::write(data);
	I2CMaster::stop();
	_delay_ms(10);
}

void AT24C::write(uint16_t address, uint8_t *data, uint16_t count) {
	I2CMaster::start();
	I2CMaster::write(address >> 8);
	I2CMaster::write(address);
	I2CMaster::write(data, count);
	I2CMaster::stop();
	_delay_ms(10);
}

void AT24C::read(uint16_t address, uint8_t *data, uint16_t count) {
	I2CMaster::start();
	I2CMaster::write(address >> 8);
	I2CMaster::write(address);
	I2CMaster::start(I2CMaster::READ);
	I2CMaster::read(data, count);
	I2CMaster::stop();
}

uint8_t AT24C::read(uint16_t address) {
	uint8_t r;
	I2CMaster::start();
	I2CMaster::write(address >> 8);
	I2CMaster::write(address);
	I2CMaster::start(I2CMaster::READ);
	I2CMaster::read(&r, 1);
	I2CMaster::stop();
	return r;
}