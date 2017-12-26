/***************************************************************************************
 * ringbuffer.cpp
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
#include "ringbuffer.h"

RingBuffer::RingBuffer() {
  _size = _head = _tail = 0;
}

void RingBuffer::push(uint8_t data) {
	buffer_ix_t next = _head + 1;

	if(next >= RING_BUFFER_SIZE)
    next = 0;
    
  if(next == _tail)
    return;
  
  _data[_head]=data;
  _head = next;
  _size++;
}

int RingBuffer::pop() {
	buffer_ix_t next = _tail + 1;
	int data;
  if(_head == _tail)
    return -1;

  if(next >= RING_BUFFER_SIZE)
    next = 0;

  data = _data[_tail];
  _tail = next;
  _size--;
  return data;
}

int RingBuffer::peek() {
  if(_head == _tail)
    return -1;

  return _data[_tail];
}

void RingBuffer::reset() {
  _tail = _head = 0;
  _size = 0;
}

bool RingBuffer::isEmpty() {
  return _size == 0 ? true : false;
}

bool RingBuffer::isFull() {
  return _size == RING_BUFFER_SIZE-1;
}

buffer_ix_t RingBuffer::size()
{
	return this->_size;
}
