/** 
 *  @file    usart.cpp
 *  @author  Alfredo Orozco ©2017 Alfredo Orozco <alfredoopa@gmail.com>
 *  @date    24/06/2017  
 *  @version 1.0 
 *  
 *  @brief Uart class for Atmega16/32/48/88/168/328 USART programming.
 *
 *  @section DESCRIPTION
 *
 */

#ifndef USART_H_
#define USART_H_

#include <stdio.h>
#include <stdint.h> 
#include <avr/io.h>


#define UBRR_VALUE(BAUD)   (( F_CPU / (16UL * (BAUD)) ) - 1)
#define UBRR_VALUE2X(BAUD)   (( F_CPU / (8UL * (BAUD)) ) - 1)

#define MAX_RING_BUFFER_SIZE 128

#if MAX_RING_BUFFER_SIZE > 255
	typedef uint16_t buffer_ix_t;
#else
	typedef uint8_t buffer_ix_t;
#endif

#if defined(USART_RX_vect)
	extern "C" void USART_RX_vect(void) __attribute__ ((signal));
	extern "C" void USART_UDRE_vect(void) __attribute__ ((signal));
#endif
#if defined(USART0_RX_vect)
	extern "C" void USART0_RX_vect(void) __attribute__ ((signal));
	extern "C" void USART0_UDRE_vect(void) __attribute__ ((signal));
#endif
#if defined(USART1_RX_vect)
	extern "C" void USART1_RX_vect(void) __attribute__ ((signal));
	extern "C" void USART1_UDRE_vect(void) __attribute__ ((signal));
#endif
#if defined(USART2_RX_vect)
	extern "C" void USART2_RX_vect(void) __attribute__ ((signal));
	extern "C" void USART2_UDRE_vect(void) __attribute__ ((signal));
#endif
#if defined(USART3_RX_vect)
	extern "C" void USART3_RX_vect(void) __attribute__ ((signal));
	extern "C" void USART3_UDRE_vect(void) __attribute__ ((signal));
#endif

/* START OF RingBuffer Class*/
class RingBuffer{

  public:
    RingBuffer();
    void push(uint8_t data);
    int pop();
    int peek();
    bool isEmpty();
    bool isFull();
    int size();
    void reset();

  private:

    uint8_t _buffer[MAX_RING_BUFFER_SIZE];
    buffer_ix_t _head;
    buffer_ix_t _tail;
    buffer_ix_t _size;
};
/* END OF RingBuffer Class*/

/* START of Usart Class*/
class Usart{

  protected:
	volatile uint8_t * const _UBRRH;
	volatile uint8_t * const _UBRRL;
	volatile uint8_t * const _UCSRA;
	volatile uint8_t * const _UCSRB;
	volatile uint8_t * const _UCSRC;
	volatile uint8_t * const _UDR;
	RingBuffer buffer_in;
	RingBuffer buffer_out;
	bool _is_write;

	public:
	typedef enum {
		BIN,
		HEX,
		OCT,
		DEC,
    }Format;

    Usart(volatile uint8_t * ubrrh,
		  volatile uint8_t * ubrrl,
          volatile uint8_t * ucsra,
          volatile uint8_t * ucsrb,
		  volatile uint8_t * ucsrc,
		  volatile uint8_t * udr
		  );

    void init(uint32_t baudrate);

    void print(char c);
    void print(int num);
    void print(long int num);
    void print(unsigned int num);
    void print(unsigned long int num);
    void print(float num);
    void print(double num);
    void print(char* str);
    void print(const char* str);

    void println();
    void println(char c);
    void println(int num);
    void println(unsigned int num);
    void println(unsigned long int num);
    void println(long int num);
    void println(float num);
    void println(double num);
    void println(char* str);
    void println(const char* str);

    int peek();
    void write(uint8_t data);
    void write(uint8_t *data, buffer_ix_t len);
    int read();
    buffer_ix_t read(uint8_t *data, buffer_ix_t len);
    buffer_ix_t available();
    void flush();

	void __rx_irq();
	void __udre_irq();
};
/* END of Usart Class*/

/* Object definitions for the Usarts HW modules */
#if defined(UBRRH) || defined(UBRR0H)
  extern Usart Serial;
#endif
#if defined(UBRR1H)
  extern Usart Serial1;
#endif
#if defined(UBRR2H)
  extern Usart Serial2;
#endif
#if defined(UBRR3H)
  extern Usart Serial3;
#endif

#endif // USART_H_