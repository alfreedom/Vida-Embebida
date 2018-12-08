#include <pcf8574.h>

PCF8574::PCF8574()
{
	this->io_setup = 0xFF;
}

void PCF8574::setInputs(uint8_t pin_mask) {
	this->io_setup |= pin_mask;
}
void PCF8574::setOutputs(uint8_t pin_mask) {
	this->io_setup &= ~pin_mask;
}
uint8_t PCF8574::readInputs() {
	uint8_t in;
	I2CMaster::start();
	in = I2CMaster::read();
	I2CMaster::stop();
	return in & io_setup;
}
uint8_t PCF8574::read() {
	uint8_t in;
	I2CMaster::start();
	in = I2CMaster::read();
	I2CMaster::stop();
	return in;
}
void PCF8574::write(uint8_t data) {
	uint8_t send = (~this->io_setup & data) | this->io_setup;
	I2CMaster::start();
	I2CMaster::write(send);
	I2CMaster::stop();
}