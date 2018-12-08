/******************************************************
 * main.c
 *
 * Program Name:  reloj-i2c
 *         Date:  2017-12-26
 *       Author:  YOUR_NAME
 *      License:  YOUR_LICENSE
 *
 * Description:
 *  YOUR PROGRAM DESCRIPTION HERE.
 * 
 *****************************************************/
#include <avr/io.h>
#include <util/delay.h>
#include <ds1307.h>
#include <at24c.h>

#define EEPROM_ADDRESS 0xA0

RTC rtc;
AT24C eeprom;


void AVRInit()
{
	char r = 'F';
	DDRB = 0xFF;
	DDRC = 0;
	PORTC = 0x03;

	eeprom.init(EEPROM_ADDRESS);
	rtc.init();

	eeprom.write(0x0000, &r, 1);
	if(eeprom.read(0) == 'F')
		PORTB = 0x01;	
	
}

int main()
{
	RTC::time_t time;
	// Initialize the AVR modules
	AVRInit();
  
	/*
	// Formato 12 hrs (AM/PM), 9 PM
	time.hours = 0x60 | 0x11;	// Formato 12 hrs en PM, hora: 11 Horas
	time.minutes = 0x33;			// 33 minutps
	time.seconds = 0x15;			// 15 segundos
	time.day = 0x04;					// dia 4 (miércoles)
	time.date = 0x27;					// dia del mes 27
	time.month = 0x12;				// mes 12 (diciembre)
	time.year = 0x17;					// año 17 (2017)
	rtc.setTime(&time); 
	*/
	// Infinite loop
	uint8_t s = 0;
	while (1)
	{
		rtc.getTime(&time);
		if(s != time.minutes)
		{
			s=time.minutes;
			//printTime(&time);
		}
	}

	return 0;
}

/*
void printTime(RTC::time_t* time) {
	switch (time->day)
	{
	case 1:
		Serial.print("Domingo ");
		break;
	case 2:
		Serial.print("Lunes ");
		break;
	case 3:
		Serial.print("Martes ");
		break;
	case 4:
		Serial.print("Miercoles ");
		break;
	case 5:
		Serial.print("Jueves ");
		break;
	case 6:
		Serial.print("Viernes ");
		break;
	case 7:
		Serial.print("Sabado ");
		break;
	}

	Serial.print(time->date >> 4);
	Serial.print(time->date & 0x0F);
	Serial.print(" de ");

	switch ((time->month >> 4) * 10 + (time->month & 0x0F))
	{
		case 1: Serial.print("Enero"); break;
		case 2: Serial.print("Febrero"); break;
		case 3: Serial.print("Marzo"); break;
		case 4: Serial.print("Abril"); break;
		case 5: Serial.print("Mayo"); break;
		case 6: Serial.print("Junio"); break;
		case 7: Serial.print("Julio"); break;
		case 8: Serial.print("Agosto"); break;
		case 9: Serial.print("Septiembre"); break;
		case 10: Serial.print("Octubre"); break;
		case 11: Serial.print("Noviembre"); break;
		case 12: Serial.print("Diciembre"); break;
	}
	Serial.print(" del 20");

	Serial.print(time->year >> 4);
	Serial.print(time->year & 0x0F);
	Serial.print(", ");

	if(time->hours & 0x40)
		Serial.print((time->hours >> 4) & 0x01);
	else
		Serial.print((time->hours >> 4) & 0x03);
	Serial.print((time->hours & 0x0F));
	Serial.print(':');
	Serial.print(time->minutes >> 4);
	Serial.print(time->minutes & 0x0F);
	if(time->hours & 0x40)
		time->hours & 0x20 ? Serial.print(" PM ") : Serial.print(" AM ");

	Serial.print("\e[?25l\r ");
	Serial.flush();
}
*/