/******************************************************
 * main.c
 *
 * Program Name:  software-spi-master
 *         Date:  2017-12-29
 *       Author:  Alfredo Orozco
 *
 * Description:
 *  Ejemplo de uso de SPI modo maestro por software
 * 
 *  www.vidaembebida.wordpress.com
 * 
 *****************************************************/
#include <avr/io.h>
#include <util/delay.h>

// Define los puertos y los pines del micro para SPI
#define SPI_DDR		DDRB
#define SPI_PORT	PORTB
#define SPI_PIN		PINB
#define SPI_MOSI	0
#define SPI_MISO	1
#define SPI_SCK		2
#define SPI_CS		3
#define SPI_FREQ	8000 // 8 KHz

// Macros para escribir en pines de salida (1 y 0)
#define SPI_MOSI_HIGH (SPI_PORT |= (1<<SPI_MOSI))
#define SPI_MOSI_LOW (SPI_PORT &= ~(1<<SPI_MOSI))

#define SPI_SCK_HIGH (SPI_PORT |= (1<<SPI_SCK))
#define SPI_SCK_LOW (SPI_PORT &= ~(1<<SPI_SCK))

#define SPI_CS_HIGH (SPI_PORT |= (1<<SPI_CS))
#define SPI_CS_LOW (SPI_PORT &= ~(1<<SPI_CS))

// Macro para leer pin de entrada MISO
#define SPI_MISO_STATE (SPI_PIN & (1<<SPI_MISO))

// Macros para retardos.
#define delay_ms(MS) for( unsigned long i = 0; i< MS; i++) _delay_ms(1)
#define delay_us(US) for( unsigned long i = 0; i< US; i++) _delay_us(1)

// Guarda el tiempo de retardo para el periodo de SCK
unsigned long spi_delay;

void spi_init();
void spi_write(uint8_t data);
uint8_t spi_readwrite(uint8_t data);

void AVRInit()
{
	spi_init();
	spi_write(0);
}

int main()
{
	uint8_t i = 0;
	AVRInit();
	
	while (1)
	{
		i=0;
		while(i<8)
		{
			spi_write(1<<i++);	
			delay_ms(60);
		}

		i=0;
		while(i<8)
		{
			spi_write(0x80>>i++);	
			delay_ms(60);
		}
	}

	return 0;
}

void spi_init()
{
	// Pines MOSI, SCK y CS como salida, pin MISO como entrada
	DDRB |= (1 << SPI_MOSI) | (1 << SPI_SCK) | (1 << SPI_CS) | (0 << SPI_MISO);
	spi_delay = ((1.0 / SPI_FREQ) * 1000000UL) / 2;
}

void spi_write(uint8_t data) {
	// Selecciona el dispositivo SPI con CS=0
	SPI_CS_LOW;

	for (int i = 0; i < 8; i++)
	{
		// Checa el bit mas significativo y lo pone en
		// el bus (PIN MOSI)
		if ((data << i) & 0x80)
			SPI_MOSI_HIGH;
		else
			SPI_MOSI_LOW;

		// Envía pulso de reloj (CHPOL = )
		SPI_SCK_LOW;
		delay_us(spi_delay);
		SPI_SCK_HIGH;
		delay_us(spi_delay);
	}

	// Libera el dispositivo SPI con CS=1
	SPI_CS_HIGH;
}


uint8_t spi_readwrite(uint8_t data)
{
	uint8_t rd = 0;

	// Selecciona el dispositivo SPI con CS=0
	SPI_CS_LOW;

	for (int i = 0; i < 8; i++)
	{
		rd =  rd <<1;
		// Checa el bit mas significativo y lo pone en
		// el bus (PIN MOSI)
		if ((data << i) & 0x80)
			SPI_MOSI_HIGH;
		else
			SPI_MOSI_LOW;

		// Envía pulso de reloj (CHPOL = )
		SPI_SCK_LOW;
		delay_us(spi_delay);

		// Lee el bit recibido en MISO
		if (SPI_MISO_STATE)
			rd |= 1;

		SPI_SCK_HIGH;
		delay_us(spi_delay);

	}

	// Libera el dispositivo SPI con CS=1
	SPI_CS_HIGH;

	return rd;
}
