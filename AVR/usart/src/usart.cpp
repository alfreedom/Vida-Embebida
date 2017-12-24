
#include "usart.h"
#include <avr/interrupt.h>

#if defined(UBRRH) 
  Usart Serial(&UBRRH, &UBRRL, &UCSRA, &UCSRB, &UCSRC, &UDR);
#endif 
#if defined(UBRR0H) 
  Usart Serial(&UBRR0H, &UBRR0L, &UCSR0A, &UCSR0B, &UCSR0C, &UDR0);
#endif
#if defined(UBRR1H)
	Usart Serial1(&UBRR1H, &UBRR1L, &UCSR1A, &UCSR1B, &UCSR1C, &UDR1);
#endif
#if defined(UBRR2H)
	Usart Serial2(&UBRR2H, &UBRR2L, &UCSR2A, &UCSR2B, &UCSR2C, &UDR2);
#endif
#if defined(UBRR3H)
	Usart Serial3(&UBRR3H, &UBRR3L, &UCSR3A, &UCSR3B, &UCSR3C, &UDR3);
#endif

#if defined(USART_RX_vect)
	void USART_RX_vect(void){
		Serial.__rx_irq();
	}
	void USART_UDRE_vect(void){
		Serial.__udre_irq();
	}
#endif

#if defined(USART0_RX_vect)
	void USART0_RX_vect(void){
		Serial.__rx_irq();
	}
	void USART0_UDRE_vect(void){
		Serial.__udre_irq();
	}
#endif

#if defined(USART1_RX_vect)
	void USART1_RX_vect(void){
		Serial1.__rx_irq();
	}
	void USART1_UDRE_vect(void){
		Serial1.__udre_irq();
	}
#endif

#if defined(USART2_RX_vect)
	void USART2_RX_vect(void){
		Serial2.__rx_irq();
	}
	void USART2_UDRE_vect(void){
		Serial2.__udre_irq();
	}
#endif

#if defined(USART3_RX_vect)
	void USART3_RX_vect(void){
		Serial3.__rx_irq();
	}
	void USART3_UDRE_vect(void){
		Serial3.__udre_irq();
	}
#endif

 /* START of Usart Class Methodes Implementation*/

Usart::Usart(volatile uint8_t * ubrrh, volatile uint8_t * ubrrl,
volatile uint8_t * ucsra, volatile uint8_t * ucsrb,
volatile uint8_t * ucsrc,volatile uint8_t * udr): _UBRRH(ubrrh),_UBRRL(ubrrl), _UCSRA(ucsra),
_UCSRB(ucsrb),_UCSRC(ucsrc),_UDR(udr)
{
	_is_write = 0;
}

void Usart::init(uint32_t baud) {

  #if defined ( U2X0 )
  baud = UBRR_VALUE2X(baud);
  *_UCSRA |= (1 << U2X0);
  #else
  baud = UBRR_VALUE(baud);
  #endif

  /* Set baud rate */
	*_UBRRH = (unsigned char)(baud>>8);
	*_UBRRL = (unsigned char)baud;

	cli();

  #if defined(UBRRH) 
  /* Enable receiver and transmitter whit RX interrupt */
  *_UCSRB = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);
  /* Set frame format: 8data, 1stop bit , parity none*/
  *_UCSRC = (1<<UCSZ0)|(1<<UCSZ1);
  #else
	/* Enable receiver and transmitter whit RX interrupt */
	*_UCSRB = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
	/* Set frame format: 8data, 1stop bit , parity none*/
	*_UCSRC = (1<<UCSZ00)|(1<<UCSZ01);
  #endif
	
	sei();
}

void Usart::flush(){
	// Si no está escribiendo regresa
	if (!_is_write)
        return;
 	
  #if defined(UBRRH) 
      // Si está escribiendo...
  // Espera a que todos los datos se hayan enviado
  // Mientras la interrupción esté habilitada ó la transmisión de datos
  // no se haya completado....
  while ((*_UCSRB & (1<<UDRIE)) || !(*_UCSRA & (1<<TXC)))
    {
    // Si las interrupciones globales NO están habilitadas y la interrupción por
    // transmisor vacío esté habilitada envía el siguiente dato del buffer.
        if (!(SREG & (1<<SREG_I)) && (*_UCSRB & (1<<UDRIE)))
        {
            // si el registro de datos está vacío envía el siguiente dato.
                if (*_UCSRA & (1<<UDRE))
                    __udre_irq();
        }
  }
  #else
	// Si está escribiendo...
	// Espera a que todos los datos se hayan enviado
	// Mientras la interrupción esté habilitada ó la transmisión de datos
	// no se haya completado....
	while ((*_UCSRB & (1<<UDRIE0)) || !(*_UCSRA & (1<<TXC0)))
    {
		// Si las interrupciones globales NO están habilitadas y la interrupción por
		// transmisor vacío esté habilitada envía el siguiente dato del buffer.
        if (!(SREG & (1<<SREG_I)) && (*_UCSRB & (1<<UDRIE0)))
        {
            // si el registro de datos está vacío envía el siguiente dato.
                if (*_UCSRA & (1<<UDRE0))
                    __udre_irq();
        }
  }
  #endif

  
}

void Usart::write(uint8_t data) {
   _is_write = true;
  #if defined(UBRRH) 
	// Si el buffer está vacío y el registro de datos está vació
	// Envía el dato inmediatamente y limpia la bandera de transmisor vacío
	if (buffer_out.isEmpty() && (*_UCSRA & (1<<UDRE   ))) {
        *_UDR = data;
            *_UCSRA |= (1<<TXC   );
        return;
    }

	// Si el buffer de datos no está vació
	// Mientras el buffer de datos esté lleno...
	while(buffer_out.isFull())
    {
		// Checa si las interrupciones globales NO están habilitadas, para manejar
		// el envío de datos manualmente....
		if(!(SREG & (1<<SREG_I)))
		{
			// Si el registro de datos está vacio, envía un dato del buffer de salida para liberar
			// el espacio en la UART..
			if((*_UCSRA & (1<<UDRE  )))
				__udre_irq();
		}
	}

	// Agrega el dato a envíoar al bufer de salida.
	buffer_out.push(data);
	// Habilita la interrupción por registro de datos vacío.
	*_UCSRB |= (1<<UDRIE  );
  
  #else
  // Si el buffer está vacío y el registro de datos está vació
  // Envía el dato inmediatamente y limpia la bandera de transmisor vacío
  if (buffer_out.isEmpty() && (*_UCSRA & (1<<UDRE0))) {
        *_UDR = data;
            *_UCSRA |= (1<<TXC0);
        return;
    }

  // Si el buffer de datos no está vació
  // Mientras el buffer de datos esté lleno...
  while(buffer_out.isFull())
    {
    // Checa si las interrupciones globales NO están habilitadas, para manejar
    // el envío de datos manualmente....
    if(!(SREG & (1<<SREG_I)))
    {
      // Si el registro de datos está vacio, envía un dato del buffer de salida para liberar
      // el espacio en la UART..
      if((*_UCSRA & (1<<UDRE0)))
        __udre_irq();
    }
  }

  // Agrega el dato a envíoar al bufer de salida.
  buffer_out.push(data);
  // Habilita la interrupción por registro de datos vacío.
  *_UCSRB |= (1<<UDRIE0);
  #endif
}

int Usart::read() {
	// devuelve un dato recibido almacenado en el buffer de entrada.
  return buffer_in.pop();
}

int Usart::peek() {
  return buffer_in.peek();
}

void Usart::print(char* str) {
  while(*str)
    write(*str++);
}

void Usart::print(char c) {
  if(c=='\r')
    c='\n';
    
  if(c=='\n')
    write('\r');
  write(c);
}

void Usart::print(int num) {
  print((long int)num);
}

void Usart::print(unsigned int num) {
  print((unsigned long int)num);
}

void Usart::print(unsigned long int num) {
  char str[10];
  sprintf(str, "%lu", num);
  print(str);
}

void Usart::print(long int num) {
  char str[10];
  sprintf(str, "%ld", num);
  print(str);
}

void Usart::print(double num) {
  int u,d;
  char str[10];
  u=(int)num;
  d = ((num - (double)u) * 100.0);
  sprintf(str, "%d.%d", u,d);
  print(str);
}

void Usart::print(float num) {
  print((double) num);
}

void Usart::print(const char* str) {
  print((char*) str);
}
void Usart::println() {
  print("\r\n");
}
void Usart::println(char* str) {
  print(str);
  println();
}
void Usart::println(char c) {
  write(c);
  println();
}
void Usart::println(int num) {
  print(num);
  println();
}
void Usart::println(unsigned int num) {
  print(num);
  println();
}
void Usart::println(long int num) {
  print(num);
  println();
}

void Usart::println(unsigned long int num) {
  print(num);
  println();
}

void Usart::println(float num) {
  print(num);
  println();
}

void Usart::println(double num) {
  print(num);
  println();
}

void Usart::println(const char* str) {
  print((char*) str);
  println();
}

void Usart::write(uint8_t *data, buffer_ix_t len) {
  for (buffer_ix_t i = 0; i < len; i++)
    write(data[i]);
}

buffer_ix_t Usart::read(uint8_t *data, buffer_ix_t len) {
  buffer_ix_t n_reads;

  for( n_reads = 0; n_reads < len && available(); n_reads++)
    data[n_reads] = read();
  
  return n_reads;
}

buffer_ix_t Usart::available() {
  return buffer_in.size();
}

void Usart::__udre_irq() {
	// Envía el siguiente dato del buffer
	*_UDR = buffer_out.pop();
  #if defined(UBRRH) 
    // Limpia la bandera de transmisión completa
  *_UCSRA |= (1<<TXC); 
  // SI el buffer está vacío deshabilita las interrupción
  // por registro de datos vacío
  if(buffer_out.isEmpty()) 
    *_UCSRB &= ~(1 << UDRIE);
  #else
	// Limpia la bandera de transmisión completa
	*_UCSRA |= (1<<TXC0);	
	// SI el buffer está vacío deshabilita las interrupción
	// por registro de datos vacío
	if(buffer_out.isEmpty()) 
		*_UCSRB &= ~(1 << UDRIE0);
  #endif
}

void Usart::__rx_irq() {
  buffer_in.push(*_UDR);	
}
 /* END of Usart Class Methodes Implementation*/

 /************************************************/


 /************************************************/

 /* START of RingBuffer Class Methodes Implementation*/
RingBuffer::RingBuffer() {
  _size = _head = _tail = 0;
}

void RingBuffer::push(uint8_t data) {
  buffer_ix_t next = (buffer_ix_t)(_head + 1) % MAX_RING_BUFFER_SIZE;
    
  if(next == _tail)
    return;
  
  _buffer[_head]=data;
  _head = next;
  _size++;
}

int RingBuffer::pop() {
  int data;

  if(_head == _tail)
    return -1;

  data = _buffer[_tail];
  _tail = (buffer_ix_t)(_tail + 1) % MAX_RING_BUFFER_SIZE;;
  _size--;
  return data;
}

int RingBuffer::peek() {
  if(_head == _tail)
    return -1;

  return _buffer[_tail];
}

void RingBuffer::reset() {
  _tail = _head = 0;
  _size = 0;
}

bool RingBuffer::isEmpty() {
  return _size == 0;
}

bool RingBuffer::isFull() {
  return _size == MAX_RING_BUFFER_SIZE-1;
}

int RingBuffer::size() {
  return _size;
}

 /* END of RingBuffer Class Methodes Implementation*/