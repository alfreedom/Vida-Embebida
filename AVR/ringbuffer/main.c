/******************************************************
 * main.c
 *
 * Program Name:  ring_buffer
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

#include <ringbuffer.h>

RingBuffer buffer;

void AVRInit()
{
	buffer.reset();
	DDRB = 0xFF;
}

int main()
{
	// Initialize the AVR modules
	AVRInit();

	while(1)
	{
		buffer.push(0x01);
		buffer.push(0x04);
		buffer.push(0x08);
		buffer.push(0x10);
		buffer.push(0x20);
		buffer.push(0x40);
		buffer.push(0x80);
		buffer.push(0x40);
		buffer.push(0x20);
		buffer.push(0x10);
		buffer.push(0x08);
		buffer.push(0x04);
		buffer.push(0x02);

		// Infinite loop
		while(buffer.size())
		{
			PORTB = buffer.pop();
			_delay_ms(100);
		}

	}

	return 0;
}
