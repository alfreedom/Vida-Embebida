
#ifndef _AT24C_H_
#define _AT24C_H_

#include <stdint.h>
#include <i2c_master.h>

class AT24C : public I2CMaster 
{
public:
	AT24C();
	void write(uint16_t address, uint8_t data);
	void write(uint16_t address, uint8_t* data, uint16_t count);
	void read(uint16_t address, uint8_t* data, uint16_t count);
	uint8_t read(uint16_t address);
};

#endif // _AT24C_H_
