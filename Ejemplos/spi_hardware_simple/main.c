/******************************************************
 * main.c
 *
 * Program Name:  SPI hardware simple
 *         Date:  2018-03-30
 *       Author:  Alfredo Orozco
 *      License:  MIT
 *
 * Description:
 *  
 * Programa ejemplo de programación del módulo SPI en el microcontrolador AVR ATmega32.
 * El programa controla un cincuito integrado 74HC595, un registro de desplazamiento de 8 bits.
 * 
 * 	www.vidaembebida.wordpress.com
 * 
 *****************************************************/
#include <avr/io.h> 
#include <util/delay.h> 

void SPI_MasterInit();
void SPI_MasterTransmit(char data);
void AVRInit();

int main()
{
	char i = 0;
	// Initialize the AVR modules
	AVRInit();

	// Infinite loop
	while(1)
	{
		SPI_MasterTransmit(i++);
		_delay_ms(150);
	}

	return 0;
}

void AVRInit()
{
	/* Configura el módulo SPI en modo maestro */
	SPI_MasterInit();
}

void SPI_MasterInit()
{
	/* Configura MOSI, SCK y SS como salidas, las demas como entradas */
	DDRB = (1<<PB5)|(1<<PB7) | (1 << PB4);

	/* Habilita SPI, Modo Master, establece el reloj a una frecuenca de  fck/16 = 16000000/16 = 1Mhz */
	SPCR = (1 << SPE) | (1 << MSTR) | ( 1<< SPR0);
}

void SPI_MasterTransmit(char data)
{
	/* Habilita el chip esclavo: SS en bajo */
	PORTB &= ~(1<<PB4);

	/* Inicia la transmisión */
	SPDR = data;
	/* Espera a que se complete la transmisión checando el bit SPIF del registro SPSR*/
	while(!(SPSR & (1<<SPIF)));

	/* Deshabilita el chip esclavo: SS en alto */
	PORTB |= (1<<PB4);
}
