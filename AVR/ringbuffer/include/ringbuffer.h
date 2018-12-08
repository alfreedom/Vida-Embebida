/***************************************************************************************
 * ringbuffer.h
 * 
 *        Autor:  Alfredo Orozco de la Paz      
 *        Fecha:  Septiembre 2017
 *   Procesador:  ATmega328p
 *   Frecuencia:  16 MHz
 *      Familia:  AVR-mega
 *   Compilador:  GNU avr-gcc
 *
 *
 *        Copyrigth© 2017 Alfredo Orozco
 * 
 ***************************************************************************************/

#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_

#include <stdint.h>

#define RING_BUFFER_SIZE 64

typedef uint16_t buffer_ix_t;

class RingBuffer{

  public:
    RingBuffer();
    void push(uint8_t data);
    int pop();
    int peek();
    bool isEmpty();
    bool isFull();
		buffer_ix_t size();
		void reset();

	private:

    uint8_t _data[RING_BUFFER_SIZE];
		buffer_ix_t _head;
		buffer_ix_t _tail;
		buffer_ix_t _size;
};

#endif // RING_BUFFER_H_
