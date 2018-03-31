/******************************************************
 * main.c
 *
 * Program Name:  spi_hardware_interrupciones
 *         Date:  2018-03-30
 *       Author:  Alfredo Orozco
 *      License:  MIT
 *
 * Description:
 * 
 * Programa ejemplo de programación del módulo SPI en el microcontrolador AVR ATmega32.
 * El programa controla un cincuito integrado 74HC595, un registro de desplazamiento de 8 bits.
 * 
 * 	www.vidaembebida.wordpres.com
 * 
 *****************************************************/

#include <avr/io.h> 
#include <util/delay.h> 
#include <avr/interrupt.h>

void SPI_MasterInit();
void SPI_MasterTransmit(char data);
void AVRInit();

volatile char i = 0;

/* Rutina de interrupción que se ejecuta con cada tansmisión terminada */
ISR(SPI_STC_vect)
{
    /* Deshabilita el chip esclavo: SS en alto */
	PORTB |= (1<<PB4);
	/* Espera 100ms */
	_delay_ms(100);
	/* Envía el siguiente dato */
	PORTB &= ~(1<<PB4);
	SPDR = i++;
}

int main()
{
	// Initialize the AVR modules
	AVRInit();

	/* Habilita el chip esclavo: SS en bajo */
	PORTB &= ~(1<<PB4);
	/* Inicia la primera transmisión SPI */
	SPDR = i++;

	// Infinite loop
	while(1)
	{
	}

	return 0;
}

void AVRInit()
{
	SPI_MasterInit();
	sei();
}

void SPI_MasterInit()
{
	/* Configura MOSI, SCK y SS como salidas, las demas como entradas */
	DDRB = (1<<PB5)|(1<<PB7) | (1 << PB4);

	/* Habilita SPI, Modo Master, establece el reloj a una frecuenca de  fck/16 = 16000000/16 = 1Mhz */
	SPCR = (1 << SPE) | (1 << MSTR) | ( 1<< SPR0);

	/* Habilita interrupciones por transmision terminada */
	SPCR |= (1 << SPIE);
}
