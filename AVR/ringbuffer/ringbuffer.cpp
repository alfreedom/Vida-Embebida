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
  int next = _head+1;

  if(next >= MAX_RING_BUFFER_SIZE)
    next = 0;
    
  if(next == _tail)
    return;
  
  _data[_head]=data;
  _head = next;
  _size++;
}

int RingBuffer::pop() {
  int next =  _tail+1;
  int data;
  if(_head == _tail)
    return -1;

  if(next >= MAX_RING_BUFFER_SIZE)
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
  return _size == MAX_RING_BUFFER_SIZE-1;
}

int RingBuffer::size() {
	int ret = this->_size;
  return ret;
}
