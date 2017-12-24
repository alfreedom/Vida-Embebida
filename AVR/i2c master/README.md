
# I2C master library
#### C++ Library for control the I2C module of the AVR microcontroller

---
#### Notes: you need compile with the command avr-g++ instead of avr-gcc.

This library lets you control the i2c comunnication in master mode on the AVR microcontrollers. Provides methods for send start and stop i2c conditions, write data and read data.

The use of the library is very easy, only you need to copy the i2c_master.h and i2c_master.cpp files in your project folder, do the inclusion in your source file code that needs to use i2c protocol and add the i2c_master.cpp file to the compile files.

---
### Included methods
 
 ###
#### void I2CMaster::init ( uint8_t address, long scl_clock )

Initialize the i2c hardware in master mode whit the specific address and the SCL frequency (in Hz).
The address must contains the RD/WR bit (bit 0), for example if the address register of a device is 01011100, the addres passed to the function will be 0x5C (92 decimal)

	  7   6   5   4   3   2   1     0
	┌───┬───┬───┬───┬───┬───┬───┬───────┐
	│ 0 │ 1 │ 0 │ 1 │ 1 │ 1 │ 0 │ RW(0) │ = 0x5C
	└───┴───┴───┴───┴───┴───┴───┴───────┘
---
#### uint8_t I2CMaster::start()
Send start condition. return 1 if the start condition sent, otherwise return 0;

-----
#### void I2CMaster::stop ()
Send the stop condition.

---
#### uint8_t I2CMaster::write ( uint8_t data )
Write a single byte to the I2C bus.

---
#### uint8_t I2CMaster::read ();
Read a single byte from the I2C bus. Return the data readed.

---
#### uint8_t I2CMaster::write ( uint8_t* data, uint16_t count )
Write multiple bytes to the I2C bus. "data" is the array buffer and "count" the number of bytes to send.

---
#### uint8_t I2CMaster::read ( uint8_t* data, uint16_t count = 1)
 Read multiple bytes from the I2C bus. "data" is the array buffer where the data will be stored and "count" the number of bytes to read.
 
 ---
