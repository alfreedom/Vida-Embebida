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

    static const int MAX_RING_BUFFER_SIZE = 64;
    uint8_t _data[MAX_RING_BUFFER_SIZE];
    int _head;
    int _tail;
    int _size;
};

#endif // RING_BUFFER_H_
