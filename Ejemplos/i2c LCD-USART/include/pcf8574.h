#ifndef PCH8574_H_
#define PCH8574_H_

#include <stdint.h>
#include "i2c.h"

#define PCF_BASE_ADDRESS 0x70

class PCF8574 {

	private:
		uint8_t io_setup;
		I2C i2c;
	public:

		PCF8574();
		void init(uint8_t address);
		void setInputs(uint8_t pin_mask);
		void setOutputs(uint8_t pin_mask);
		uint8_t readInputs();
		uint8_t read();
		void write(uint8_t data);
};

#endif //PCH8574_H_
