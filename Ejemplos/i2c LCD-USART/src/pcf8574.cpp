#define _DVK501_M128_EX_ 1
#include <pcf8574.h>

PCF8574::PCF8574()
{
	this->io_setup = 0xFF;
}
void PCF8574::init(uint8_t address) {
	i2c.init(PCF_BASE_ADDRESS | (address & 0x07) << 1);
}
void PCF8574::setInputs(uint8_t pin_mask) {
	this->io_setup |= pin_mask;
}
void PCF8574::setOutputs(uint8_t pin_mask) {
	this->io_setup &= ~pin_mask;
}
uint8_t PCF8574::readInputs() {
	uint8_t in;
	i2c.start();
	in = i2c.read();
	i2c.stop();
	return in & io_setup;
}
uint8_t PCF8574::read() {
	uint8_t in;
	i2c.start();
	in = i2c.read();
	i2c.stop();
	return in;
}
void PCF8574::write(uint8_t data) {
	uint8_t send = (~this->io_setup & data) | this->io_setup;
	i2c.start();
	i2c.write(send);
	i2c.stop();
}