/******************************************************
 * main.c
 *
 * Program Name:  ds1307
 *         Date:  2017-12-28
 *       Author:  Alfredo Orozco
 *      License:  MIT
 *
 * Description:
 *  RTC ds1307 sample.
 * 
 *****************************************************/
#include <avr/io.h> 
#include <util/delay.h> 
#include "ds1307.h"

RTC rtc;

void AVRInit()
{
	DDRB = 0x01;
	rtc.init();
}

int main()
{
	RTC::time_t time;
	int seconds;
	// Initialize the AVR modules
	AVRInit();

	// Infinite loop
	while(1)
	{
		rtc.getTime(&time);
		if(seconds != time.seconds){
			PORTB^=0x01;
			seconds=time.seconds;
		}
		// YOUR CODE HERE
	}

	return 0;
}
