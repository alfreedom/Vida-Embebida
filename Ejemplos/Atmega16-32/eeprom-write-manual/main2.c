/******************************************************
 * main.c
 *
 * Program Name:  eeprom-write-manual
 *         Date:  2018-04-15
 *       Author:  Alfredo Orozco
 *      License:  GPL
 *
 * Description:
 * 
 *  Ejemplo de programación de la memoria EEPROM del
 *  microcontrolador ATmega32 utilizando los registros.
 * 
 *****************************************************/

#include <avr/io.h> 
#include <util/delay.h> 
#include <avr/interrupt.h>
#include <string.h>

void EEPROM_write(uint16_t direccion, uint8_t dato);

char text[] = "Vida Embebida";
volatile int count = 13;
volatile int address = 0;
volatile uint8_t finish = 0;;
volatile uint8_t i = 0;

ISR(EE_RDY_vect)
{
    /* Verifica el fin de cadena y que la dirección no sobrepase el
    limite de la memoria EEPROM */
	if ( i < count && (address <= E2END) )
	{
		EEPROM_write(address++, text[i++]);
	}
	else
	{
		// Deshabilita la interrupción de la memoria EEPROM
		EECR &= ~(1<<EERIE);
		finish = 1;
	}
}

void AVRInit()
{
	DDRB = 0x01;	// PB0 como salida
	PORTB = 0;
	sei();			// Habilita interrupciones globales
}

int main()
{
	AVRInit();

    EECR |= (1<<EERIE);
	while(!finish);

	PORTB = 1;

	while(1){}

	return 0;
}

void EEPROM_write(uint16_t direccion, uint8_t dato)
{
	// Espera a que el bit EEWE en EECR sea 0.
	while(EECR & (1 << EEWE));
	// Espera a que el bit SPMEN en SPMCR sea 0.
	while( SPMCR & (1 << SPMEN));
	// Escribe la dirección de la memoria en EEADR.
	EEAR = direccion;
	// Escribe el dato a guardar en EEDR.
	EEDR = dato;
	// Establece operación de escritura.
	EECR |= (1 << EEMWE);
	// Inicia la operación de escritura.
	EECR |= (1 << EEWE);
}
