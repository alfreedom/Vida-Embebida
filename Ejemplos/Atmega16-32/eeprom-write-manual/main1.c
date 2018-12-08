#include <avr/io.h>
#include <util/delay.h>

void EEPROM_write(uint16_t direccion, uint8_t dato);
uint8_t EEPROM_read(uint16_t direccion);

void AVRInit()
{
	DDRB = 0x01; // PB0 como salida
	PORTB = 0;
}

int main()
{
	AVRInit();

	// Escribe A en la dirección 0x051 de la eeprom.
	EEPROM_write(0x051, 'A');
	// Lee la dirección 0x051 y si es A enciende el led.
	if(EEPROM_read(0x051) == 'A')
	PORTB |= 0x01;

	while(1)
	{}

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

uint8_t EEPROM_read(uint16_t direccion)
{
	// Espera a que el bit EEWE en EECR sea 0.
	while(EECR & (1 << EEWE));
	// Espera a que el bit SPMEN en SPMCR sea 0.
	while( SPMCR & (1 << SPMEN));
	// Escribe la dirección de la memoria en EEADR.
	EEAR = direccion;
	// Inicia la operación de escritura.
	EECR |= (1 << EERE);
	// Devuelve el dato leido de la memoria.
	return EEDR;
}
