/******************************************************
 * main.c
 *
 * Program Name:  ../AVR/pcf8574
 *         Date:  2017-12-25
 *       Author:  YOUR_NAME
 *      License:  YOUR_LICENSE
 *
 * Description:
 *  YOUR PROGRAM DESCRIPTION HERE.
 * 
 *****************************************************/
#include <avr/io.h> 
#include <util/delay.h> 
#include <pcf8574.h>

// Dirección base del chip PCF (0x70 para modelos Ax y 0x80 para otros modelos)
#define PCF_BASE_ADDRESS 0x70
// Dirección del chip PCF 111 (A2=1, A1=1, A0=1) = 0x07
#define PCF_ADDRESS 0x07

// Crea el objeto pcf
PCF8574 pcf;

void AVRInit()
{
	// Inicializa el driver PCF con la dirección del dispositivo
	pcf.init(PCF_BASE_ADDRESS | (PCF_ADDRESS << 1));
	// Todos los pines del PCF como salida
	pcf.setOutputs(0xFF);
	// escribe 1's en las salidas
	pcf.write(0x00);
}

int main()
{
	AVRInit();

	while(1)
	{
		pcf.write(0x01);
		_delay_ms(100);
		pcf.write(0x02);
		_delay_ms(100);
		pcf.write(0x04);
		_delay_ms(100);
		pcf.write(0x08);
		_delay_ms(100);
		pcf.write(0x10);
		_delay_ms(100);
		pcf.write(0x20);
		_delay_ms(100);
		pcf.write(0x40);
		_delay_ms(100);
		pcf.write(0x80);
		_delay_ms(100);
		pcf.write(0x40);
		_delay_ms(100);
		pcf.write(0x20);
		_delay_ms(100);
		pcf.write(0x10);
		_delay_ms(100);
		pcf.write(0x08);
		_delay_ms(100);
		pcf.write(0x04);
		_delay_ms(100);
		pcf.write(0x02);
		_delay_ms(100);
	}

	return 0;
}
