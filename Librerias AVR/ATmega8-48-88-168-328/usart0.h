/***************************************************************************************
 * usart0.h
 *
 *           Autor:  Alfredo Orozco de la Paz
 *         Archivo:  usart0.h
 *           Fecha:  10/07/2014
 *          e-mail:  alfredoopa@gmail.com
 *
 *      Procesador:  ATmega48, ATmega88, ATmega168, ATmega328
 *         Familia:  AVRmega
 *      Compilador:  GNU avr-gcc
 *
 *  Descripción:
 *
 *      Libreria  para  el  manejo  de la  USART0 de los    microcontroladores
 *      AVR ATmega48, ATmega88, ATmega168 y ATmega328 escrita en el compilador  
 *      GNU avr-gcc.
 *
 *      La libreria implementa  funcoines para  inicializar la  USART0, enviar
 *      y recibir datos por el puerto serie,verificar si hay dato  disponible
 *      y enviar cadenas de texto.
 *
 *      Cuenta con  la  posibilidad  hacer  uso de las interrupciones para el 
 *      envío y recepcion de datos, con lo que los datos recibidos y enviados 
 *      se almacenan  en  un  buffer  temporarl  (FIFO)  que serán llenados o 
 *      vaciados por las funciones de las interruciones  por  dato recibido o 
 *      por transmisor vacío.  Para hacer uso  de  las interrupciones se usan 
 *      las definiciones:
 *
 *          #define USE_USART0_RX_INTETTUPT  // Usa la interrupción de dato disponible en RX
 *          #define USE_USART0_TX_INTERRUPT  // Usa la interrupcion de transmisor vacío
 *          #define USE_USART0_INTERRUPTS    // Usa las 2 interrupciónes
 *
 *      Uso:
 *          #define USE_USART0_RX_INTERRUPT
 *          #include "usart0.h"
 *
 *      El programador puede activar y atender las interrupcions por su cuenta
 *      omitiendo las definiciones anteriormente mencionadas.
 *
 *      Para el caso de que se usen interrupciones, se debe tomar en cuenta el
 *      tamaño de los buffer de entrada y salida (FIFO), ya que es  espacio en 
 *      memoria RAM y hay que  considerar  ese  espacio en el desarrollo de la 
 *      aplicacion.  Por  default  se  define un buffer de 128 bytes, que bien 
 *      puede ser ampliado  por  el  programador  (a un maximo de 255 para los 
 *      indices de tipo char)  y  que es util en microcontroladores de mayores 
 *      capacidades.
 *
 *      Se puede hacer uso  de  la  entrada  y salida estandar para el envio y
 *      recepcion de datos con la libreria  "stdio.h",  usando  las  funciones
 *      printf, scanf, putc, etc. Para el uso de esta propiedad hay  que hacer
 *      la definicion "#define USE_USART0_STDIO".
 *
 *      Uso:
 *          #define USE_USART0_STDIO
 *          #include "usart0.h"
 *
 *
 *      Las funciones de la libreria son:
 *
 *      ---------------------------------------------------------------------------------
 *      |   void USART0_Init(int baudrate) *
 *      |       Inicializa la comunicación estandar (8N1) con el baudaje especificado.
 *      ---------------------------------------------------------------------------------
 *      |   void USART0_Init2(int baudrate,
 *      |                   unsigned char stop_bits,
 *      |                   unsigned char parity,
 *      |                   unsigned char data_size)
 *      |
 *      |       Inicializa la comunicacion configurando todos los parametros.
 *      ---------------------------------------------------------------------------------
 *      |   void USART0_PutChar(char c)
 *      |       Envía un dato por la USART0 o lo inserta en el buffer de salida si se 
        |       usa interrupción.
 *      ---------------------------------------------------------------------------------
 *      |   int USART0_GetChar()
 *      |       Lee un dato recibido en la USART0.
 *      ---------------------------------------------------------------------------------
 *      |   void USART0_PutString(char *str)
 *      |       Envia una cadena de caracteres por la USART0.
 *      ---------------------------------------------------------------------------------
 *      |   int USART0_Kbhit()
 *      |       Determina si hay un dato para ser leido de la USAR, o el numero
 *      |       de datos en el buffer de entrada si se usa interrupcion.
 *      ---------------------------------------------------------------------------------
 *
 *      Ejemplo de uso:
 *
 * 
 *      #define F_CPU 8000000L 
 *      #define USE_USART0_RX_INTERRUPT
 *      #define USE_USART0_TX_INTERRUPT
 *      #define USE_USART0_STDIO
 *
 *      #include <avr/io.h>
 *      #include <util/delay.h>
 *      #include "usart0.h"
 *
 *      int main(void) 
 *      {
 *          USART0_Init(9600);
 *          sei();
 *
 *          USART0_PutString("Ejemplo ECO con la USART0.\n");
 *      
 *          while(1){
 *      
 *              if(USART0_Kbhit()){
 *          
 *                  printf( "Tecla: %c" , USART0_GetChar() );
 *                  _delay_ms(10);
 *              
 *              }
 *          }
 *      }
 *
 ***************************************************************************************
 *
 *    Copyright:
 *
 *        Copyrigth© 2013
 *        Alfredo Orozco
 *
 *     Licencia:
 *
 *        Este programa es software libre; usted lo puede distribuir y/o modificar
 *        bajo los terminos   de la General Public License GNU, según es publicada
 *        en la  Free  Software  Foundation;  ya se la versión 2 de la Licencia, o
 *        (a su elección) una versión posterior.
 *
 *        Este  programa se  distribuye  con la  esperanza  de que sea  útil, pero
 *        SIN   NINGUNA   GARANTÍA,  incluso   sin   la   garantía   implícita  de
 *        COMERCIALIZACIÓN  o  IDONEIDAD PARA UN PROPÓSITO PARTICULAR. consulte la
 *        Licencia Pública General de GNU para más detalles.
 *
 *        Debería haber recibido una copia de  la  Licencia Pública General de GNU
 *        junto con este programa; si no, visite http://www.gnu.org/licenses.
 *
 *
 ***************************************************************************************/

#ifndef USART0_H_
#define USART0_H_

#include <avr/io.h>


#define USART0_DATA_SIZE_5  0x00                    /*Tamaño de palabra de 5 bits*/
#define USART0_DATA_SIZE_6  _BV(UCSZ00)             /*Tamaño de palabra de 6 bits*/
#define USART0_DATA_SIZE_7  _BV(UCSZ01)             /*Tamaño de palabra de 7 bits*/
#define USART0_DATA_SIZE_8  _BV(UCSZ00) | _BV(UCSZ01)   /*tamaño de palabra de 8 bits*/

#define USART0_PARITY_OFF       0x00                    /*Sin paridad*/
#define USART0_PARITY_EVEN_ON   _BV(UPM01)              /*Paridad Par*/
#define USART0_PARITY_ODD_ON    _BV(UPM01) | _BV(UPM00) /*Paridad Impar*/

#define USART0_STOP_BITS_1  0x00        /*1 bit de parada*/
#define USART0_STOP_BITS_2  _BV(USBS)   /*2 bit de parada*/

/************************************************************************ 
 * Macro calcular el valor de los registros generadores del
 * baudrate segun la formula del datasheet.
 ************************************************************************/
#define MYUBRR(BAUD) (F_CPU/(BAUD*8L)-1)/2 //Mejor formula que (F_CPU/16/(BAUD)-1)



/************************************************************************ 
 *                      Declaración de Funciones    
 ************************************************************************/

void USART0_Init(long baudrate);
void USART0_Init2(long baudrate,unsigned char stop_bits, unsigned char parity,unsigned char data_size);
void USART0_PutChar(char byte);
int USART0_GetChar();
void USART0_PutString(char *str);
int USART0_Kbhit();


/************************************************************************
 * Si se define que se usen interrupciones, se crea un buffer para
 * almacenar los datos recibidos, por default es de 64, para no ocupar
 * mucho espacio en memoria RAM. * 
 ************************************************************************/
#if defined(USE_USART0_INTERRUPTS)
#define USE_USART0_RX_INTERRUPT
#define USE_USART0_TX_INTERRUPT
#endif

#if defined(USE_USART0_RX_INTERRUPT)
    #include <avr/interrupt.h>
    #define MAX_IN_BUFFER 128
    volatile char _rx_buffer[MAX_IN_BUFFER];
    volatile int _headrx;
    volatile int _tailrx;
#endif

#if defined(USE_USART0_TX_INTERRUPT) 
    #include <avr/interrupt.h>
    #define MAX_OUT_BUFFER 128
    volatile char _tx_buffer[MAX_OUT_BUFFER];
    volatile unsigned int _headtx;
    volatile unsigned int _tailtx;
    volatile unsigned char _txbusy;
#endif

/************************************************************************
 * Si se define el uso de la entrada salida estandar se declaran las 
 * funciones base y el stream que necesita la librería stdio.h para 
 * enviar y leer un dato mediante las funciones de la USART.
 ************************************************************************/
#if defined(USE_USART0_STDIO)
    #include <stdio.h>
    static int _usart0_putchar(char c, FILE *stream);
    static int _usart0_getchar(FILE *stream);
    static FILE _myiostream = FDEV_SETUP_STREAM(_usart0_putchar, _usart0_getchar, _FDEV_SETUP_RW);
#endif


/************************************************************************
 *          Implementacion de las funciones de la librería
 ************************************************************************/

/************************************************************************
 * USART0_Init
 *
 * Programa la USART0 del AVR con una configuración de 8 bits de palabra,
 * sin paridad y un bit de stop a una velocidad "baudrate".
 * Tambien habilita las interrupciones de recepcion de dato si se defie
 * USE_USART0_INTERRUPT y el uso de entrada y salida estandar si se define
 * USE_USART0_STDIO.
 *
 * Recibe:
 *      -baudrate: Velocidad en baudios a la que trabajará la USART0.
 *
 ************************************************************************/
void USART0_Init(long baudrate) {

    USART0_Init2(baudrate, USART0_STOP_BITS_1,
                USART0_PARITY_OFF,
                USART0_DATA_SIZE_8);

}

/************************************************************************
 * USART0_Init2
 *
 * Programa la USART0 del AVR con la confguracion especificada por el
 * programador. A diferencia de USART0_Init, se debe especificar el
 * tamaño de palabra, la paridad, los bits de stop y el baudaje.
 * Tambien habilita las interrupciones de recepcion de dato si se defie
 * USE_USART0_INTERRUPT y el uso de entrada y salida estandar si se define
 * USE_USART0_STDIO.
 *
 * Recibe:
 *
 *       baudrate:  Velocidad en baudios a la que trabajará la USART0.
 *       strop_bits:    Numero de bits de parada
 *                          USART0_STOP_BITS_1      -   1 Bit de parada.
 *                          USART0_STOP_BITS_2      -   2 Bits de parada.
 *       parity:        Paridad.
 *                          USART0_PARITY_OFF       -   Sin paridad
 *                          USART0_PARITY_EVEN_ON   -   Paridad Par
 *                          USART0_PARITY_ODD_ON    -   Paridad Impar
 *       data_size: Tamaño de palabra
 *                          USART0_DATA_SIZE_5      -   Tamaño de palabra de 5 bits
 *                          USART0_DATA_SIZE_6      -   Tamaño de palabra de 6 bits
 *                          USART0_DATA_SIZE_7      -   Tamaño de palabra de 7 bits
 *                          USART0_DATA_SIZE_8      -   Tamaño de palabra de 8 bits
 *
 ************************************************************************/
void USART0_Init2(long baudrate,
                 unsigned char stop_bits,
                 unsigned char parity,
                 unsigned char data_size) {

    /*Se programa el valor del baudrate segun la formula del datasheet*/
    UBRR0L = MYUBRR(baudrate);
    UBRR0H = MYUBRR(baudrate) >> 8;

    UCSR0C =  stop_bits | parity | data_size;

    /*Habilitamos el transmisor y el receptor*/
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);

#if defined(USE_USART0_RX_INTERRUPT)
    UCSR0B |= _BV(RXCIE0);
    _headrx=0;
    _tailrx=0;
#endif

#if defined(USE_USART0_TX_INTERRUPT)
    UCSR0B |= _BV(TXCIE0);
    _headtx=0;
    _tailtx=0;
    _txbusy=0;
#endif

#ifdef USE_USART0_STDIO
    stdout = stdin = & _myiostream;
#endif

}

/************************************************************************
 * USART0_PutChar
 *
 * Envia un byte por el puerto serie.
 *
 * Recibe:
 *
 *      - byte: Dato a enviar por el puerto serie.
 ************************************************************************/
void USART0_PutChar(char c) {

#if defined(USE_USART0_TX_INTERRUPT)
    
    if(!_txbusy) {

        _txbusy=1;
        UDR0 = c;

    }
    else {

        UCSR0B &= ~_BV(TXCIE0);

        _tx_buffer[_tailtx++] = c;

        if(_tailtx>MAX_OUT_BUFFER)
            _tailtx=0;

        UCSR0B |= _BV(TXCIE0);

    }
    
#else
    while (!(UCSR0A & _BV(UDRE0)));
    UDR0 = c;
#endif

}

/************************************************************************
 * USART0_GetChar
 *
 * Lee el dato recibido por el puerto serie.
 * Si se define USE_USART0_INTERRUP el dato se leera
 * del buffer de entrada, de lo contrario esperara a
 * que un dato este disponible en el registro de entrada.
 *
 *  Devuelve:
 *      El dato leido del puerto serie o del buffer de entrada.
 *
 ************************************************************************/
int USART0_GetChar() {

#if defined(USE_USART0_RX_INTERRUPT)

    char ret=-1;
    if(_headrx != _tailrx) {
        ret=_rx_buffer[_headrx++];
        if(_headrx>MAX_IN_BUFFER)
        _headrx=0;      
    }

    return ret;

#else
    while (!(UCSR0A & _BV(RXC0)));
    return UDR0;
#endif




}
/************************************************************************
 * USART0_PutString
 *
 * Envia una cadena de caracteres por el puerto serie.
 *
 * Recibe:
 *      - str:      Apuntador a la cadena de caracteres.
 ************************************************************************/
void USART0_PutString(char *str) {

    while (*str)
        USART0_PutChar(*str++);
}

/************************************************************************
 * USART0_Kbhit
 *
 * Indica si hay algun dato disponible para leer del registro de
 * recepcion. Si se define USE_USART0_RX_INTERRUP, la funcion devolvera
 * el numero de datos disponibles en el buffer de entrada, de lo
 * contrario devolvera 1 si hay un dato listo en el registro de
 * recepcion o 0 si aun no hay dato listo.
 *
 ************************************************************************/
int USART0_Kbhit() {

#if defined(USE_USART0_RX_INTERRUPT)
    return _tailrx - _headrx;
#else
    return (UCSR0A & _BV(RXC0));
#endif

}

/************************************************************************
 * ISR(USART_RX_vect)
 *
 * Funcion que atiende la interrupcion de dato recibido por el
 * puerto serie. Almacena el dato recibido en el buffer de entrada
 * e incrementa el contador de datos recibidos.
 *
 * Solo se usa si se define USE_USART0_INTERRUPT
 ************************************************************************/
#if defined(USE_USART0_RX_INTERRUPT)

ISR(USART_RX_vect) {

    _rx_buffer[_tailrx++]=UDR0;
    if(_tailrx>MAX_IN_BUFFER)
        _tailrx=0;
}
#endif

/************************************************************************
 * ISR(USART0_TX_vect)
 *
 * Funcion que atiende la interrupcion transmisor vacío. 
 * Envia por el puerto serie el siguiente dato del buffer de salida.
 *
 * Solo se usa si se define USE_USART_TX_INTERRUPT ó USE_USART_INTERRUPTS
 ************************************************************************/
#if defined(USE_USART0_TX_INTERRUPT)

ISR(USART_TX_vect) {

    _txbusy=0;
    if(_headtx != _tailtx) {
        _txbusy=1;
        UDR0 = _tx_buffer[_headtx++];
        if(_headtx>MAX_OUT_BUFFER)
        _headtx=0;

    }
    
}
#endif

/************************************************************************
 * Funciones para el uso de la entrada y la salida estandar con la
 * USART0.
 ************************************************************************/

#ifdef USE_USART0_STDIO

/************************************************************************
 * Funcion para el envio de un caracter mediante la salida estandar.
 ************************************************************************/
static int _usart0_putchar(char c, FILE *stream) {
    if(c=='\n')
        _usart0_putchar('\r',stream);
    USART0_PutChar(c);
    return 0;
}
/************************************************************************
 * Funcion para la recepcion de un caracter mediante la entrada estandar.
 ************************************************************************/
static int _usart0_getchar(FILE *stream) {
    char incomming;
    while(!USART0_Kbhit());

    if((incomming = USART0_GetChar()) == 13)
        incomming='\n';
    _usart0_putchar(incomming,stream);

    return incomming;
}

#endif



#endif /* USART0_H_ */
