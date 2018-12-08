

#ifndef _DS1307_H_
#define _DS1307_H_

#include <stdint.h>
#include <i2c_master.h>

#define DS_FORMAT_12 0
#define DS_FORMAT_24 1
#define DS1307_ADDRESS 0xD0

class RTC : public I2CMaster
{
public:
	typedef struct
	{
		uint8_t seconds;
		uint8_t minutes;
		uint8_t hours;
		uint8_t day;
		uint8_t date;
		uint8_t month;
		uint8_t year;
	} time_t;

	RTC();
	void init();
	void getTime(RTC::time_t *time);
	void setTime(RTC::time_t *time);
};

#endif // _DS1307_H_
