/***************************************************************************************
 * ds1307.cpp
 * 
 *        Autor:  Alfredo Orozco de la Paz      
 *        Fecha:  Marzo 2018
 *   Procesador:  ATmega32
 *   Frecuencia:  16 MHz
 *      Familia:  AVR-mega
 *   Compilador:  GNU avr-gcc
 *
 *
 *        Copyrigth© 2017 Alfredo Orozco
 * 
 ***************************************************************************************/

#include <stdint.h>
#include "ds1307.h"

RTC::RTC() {
}

void RTC::init()
{
	RTC::time_t time;

	I2CMaster::init(DS1307_ADDRESS);

	getTime(&time);
	if (time.seconds & 0x80)
	{
		this->start();
		this->write(0x00);
		this->write((time.seconds & 0x7F)+1);
		this->stop();
	}
	this->start();
	this->write(0x07);
	this->write(0x10);
	this->stop();
}

void RTC::getTime(RTC::time_t* time)
{
	this->start();
	this->write(0x00);
	this->stop();
	this->start(I2CMaster::READ);
	this->read((uint8_t *)time, sizeof(RTC::time_t));
	this->stop();
}

void RTC::setTime(RTC::time_t* time)
{
	this->start();
	this->write(0x00);
	this->write((uint8_t*)time, sizeof(RTC::time_t));
	this->write(0x10);
	this->stop();
}

