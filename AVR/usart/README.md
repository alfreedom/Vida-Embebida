
# USART/UART library
####  C++ Library for control the USART module of the AVR microcontroller

---
#### Note 1: you need compile with the command "avr-g++" instead of "avr-gcc". 

#### Note 2 (Optional): If you need to use the printf and derivated functions with float numbers, add the LDFLAGS "-Wl,-u,vfprintf -lprintf_flt -lm" to the compiler options,

This library lets you control the serial comunnication with the USART/UART module on the AVR microcontrollers. Provides methods for initialization, write and read data in many formats.


---
### Included methods
 
 ###

#### void Usart::init ( uint32_t baudrate ) 
Initialize the Usart module at specific baudrate.

---
#### void Usart::print ( char c )
Send a single character to the Usart.

---
#### void Usart::print ( int num )
Send a string format with a int number to the Usart.

---
#### void Usart::print ( long int num )
Send a string format with a long int number to the Usart.

---
#### void Usart::print ( unsigned int num )
Send a string format with a unsigned int number to the Usart.

---
#### void Usart::print ( unsigned long int num )
Send a string format with a unsigned long int number to the Usart.

---
#### void Usart::print ( float num )
Send a string format with a float number to the Usart.

---
#### void Usart::print ( double num )
Send a string format with a double number to the Usart.

---
#### void Usart::print ( char* str )
Send a NULL terminated string to the Usart.

---
#### void Usart::print ( const char* str )
Send a NULL terminated constant string to the Usart.

---

#### void Usart::println ( )
Send the characters '\r' (carriage return) and '\n' (line feed or new line) to the Usart.

---
#### void Usart::println ( char c )
Send a single character to the Usart with the characters '\r' (carriage return) and '\n' (line feed or new line) at end of the character.

---
#### void Usart::println ( int num )
Send a string format with a int number to the Usart with the characters '\r' (carriage return) and '\n' (line feed or new line) at end of the character.

---
#### void Usart::println ( unsigned int num )
Send a string format with a unsigned int number to the Usart with the characters '\r' (carriage return) and '\n' (line feed or new line) at end of the character.

---
#### void Usart::println ( unsigned long int num )
Send a string format with a unsigned long int number to the Usart with the characters '\r' (carriage return) and '\n' (line feed or new line) at end of the character.

---
#### void Usart::println ( long int num )
Send a string format with a long int number to the Usart with the characters '\r' (carriage return) and '\n' (line feed or new line) at end of the character.

---
#### void Usart::println ( float num )
Send a string format with a float number to the Usart with the characters '\r' (carriage return) and '\n' (line feed or new line) at end of the character.

---
#### void Usart::println ( double num )
Send a string format with a double number to the Usart with the characters '\r' (carriage return) and '\n' (line feed or new line) at end of the character.

---
#### void Usart::println ( char* str )
Send a NULL terminated string to the Usart with the characters '\r' (carriage return) and '\n' (line feed or new line) at end of the character.

---
#### void Usart::println ( const char* str )
Send a NULL terminated constant string to the Usart with the characters '\r' (carriage return) and '\n' (line feed or new line) at end of the character.

---

#### int Usart::peek ()
Get the next received data from the Usart without eliminate it from the input ring buffer.

---
#### void Usart::write ( uint8_t data )
Send single byte to the Usart. The "data" to send is stored in the output ring buffer.

---
#### void Usart::write ( uint8_t *data, buffer_ix_t len )
Send multiple bytes to the Usart. "data" specifies the array buffer to send and "len" the data count to send. The "data" to send are stored in the output ring buffer.

---
#### int Usart::read ()
Read single byte received from the Usart. The data returned is the next byte available in the input ring buffer.

---
#### buffer_ix_t Usart::read ( uint8_t *data, buffer_ix_t len )
Read multiple bytes received from the Usart. The data returned are the next bytes available in the input ring buffer.

---
#### buffer_ix_t Usart::available ()
Return the number of bytes available to read in the input ring buffer.

---
#### void Usart::flush ()
Wait until all data in the output ring buffer are sent.

---

Alfredo Orozco de la Paz

<alfredo.orozco@develcrew.com.mx>

www.vidaembebida.wordpres.com
