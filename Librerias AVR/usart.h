/***************************************************************************************
 * usart.h
 *
 *           Autor:  Alfredo Orozco de la Paz
 *         Archivo:  usart.h
 *           Fecha:  10/07/2014
 *          e-mail:  alfredoopa@gmail.com
 *
 *      Procesador:  ATmega16, ATmega32
 *         Familia:  AVRmega
 *      Compilador:  GNU avr-gcc
 *
 *  Descripción:
 *
 *      Libreria  para  el  manejo  de la  USART de los    microcontroladores
 *      AVR  ATmega16  y  ATmega32  escrita  en  el  compilador  GNU avr-gcc.
 *
 *      La libreria implementa  funcoines para  inicializar la  USART, enviar
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
 *          #define USE_USART_RX_INTETTUPT  // Usa la interrupción de dato disponible en RX
 *          #define USE_USART_TX_INTERRUPT  // Usa la interrupcion de transmisor vacío
 *          #define USE_USART_INTERRUPTS    // Usa las 2 interrupciónes
 *
 *      Uso:
 *          #define USE_USART_RX_INTERRUPT
 *          #include "usart.h"
 *
 *      El programador puede activar y atender las interrupcions por su cuenta
 *      omitiendo las definiciones anteriormente mencionadas.
 *
 *      Para el caso de que se usen interrupciones, se debe tomar en cuenta el
 *      tamaño de los buffer de entrada y salida (FIFO), ya que es  espacio en 
 *      memoria RAM y hay que  considerar  ese  espacio en el desarrollo de la 
 *      aplicacion.  Por  default  se  define  un buffer de 64 bytes, que bien 
 *      puede ser ampliado  por  el  programador  (a un maximo de 255 para los 
 *      indices de tipo char)  y  que es util en microcontroladores de mayores 
 *      capacidades.
 *
 *      Se puede hacer uso  de  la  entrada  y salida estandar para el envio y
 *      recepcion de datos con la libreria  "stdio.h",  usando  las  funciones
 *      printf, scanf, putc, etc. Para el uso de esta propiedad hay  que hacer
 *      la definicion "#define USE_USART_STDIO".
 *
 *      Uso:
 *          #define USE_USART_STDIO
 *          #include "usart.h"
 *
 *
 *      Las funciones de la libreria son:
 *
 *      ---------------------------------------------------------------------------------
 *      |   void USART_Init(int baudrate) *
 *      |       Inicializa la comunicación estandar (8N1) con el baudaje especificado.
 *      ---------------------------------------------------------------------------------
 *      |   void USART_Init2(int baudrate,
 *      |                   unsigned char stop_bits,
 *      |                   unsigned char parity,
 *      |                   unsigned char data_size)
 *      |
 *      |       Inicializa la comunicacion configurando todos los parametros.
 *      ---------------------------------------------------------------------------------
 *      |   void USART_PutChar(char c)
 *      |       Envía un dato por la USART o lo inserta en el buffer de salida si se 
        |       usa interrupción.
 *      ---------------------------------------------------------------------------------
 *      |   int USART_GetChar()
 *      |       Lee un dato recibido en la USART.
 *      ---------------------------------------------------------------------------------
 *      |   void USART_PutString(char *str)
 *      |       Envia una cadena de caracteres por la USART.
 *      ---------------------------------------------------------------------------------
 *      |   int USART_Kbhit()
 *      |       Determina si hay un dato para ser leido de la USAR, o el numero
 *      |       de datos en el buffer de entrada si se usa interrupcion.
 *      ---------------------------------------------------------------------------------
 *
 *      Ejemplo de uso:
 *
 * 
 *      #define F_CPU 8000000L 
 *      #define USE_USART_RX_INTERRUPT
 *      #define USE_USART_TX_INTERRUPT
 *      #define USE_USART_STDIO
 *
 *      #include <avr/io.h>
 *      #include <util/delay.h>
 *      #include "usart.h"
 *
 *      int main(void) 
 *      {
 *          USART_Init(9600);
 *          sei();
 *
 *          USART_PutString("Ejemplo ECO con la USART.\n");
 *      
 *          while(1){
 *      
 *              if(USART_Kbhit()){
 *          
 *                  printf( "Tecla: %c" , USART_GetChar() );
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

#ifndef USART_H_
#define USART_H_

#include <avr/io.h>


#define USART_DATA_SIZE_5   0x00                /*Tamaño de palabra de 5 bits*/
#define USART_DATA_SIZE_6   _BV(UCSZ0)          /*Tamaño de palabra de 6 bits*/
#define USART_DATA_SIZE_7   _BV(UCSZ1)          /*Tamaño de palabra de 7 bits*/
#define USART_DATA_SIZE_8   _BV(UCSZ0) | _BV(UCSZ1)     /*tamaño de palabra de 8 bits*/

#define USART_PARITY_OFF        0x00                    /*Sin paridad*/
#define USART_PARITY_EVEN_ON    _BV(UPM1)               /*Paridad Par*/
#define USART_PARITY_ODD_ON     _BV(UPM1) | _BV(UPM0)   /*Paridad Impar*/

#define USART_STOP_BITS_1   0x00        /*1 bit de parada*/
#define USART_STOP_BITS_2   _BV(USBS)   /*2 bit de parada*/

/************************************************************************ 
 * Macro calcular el valor de los registros generadores del
 * baudrate segun la formula del datasheet.
 ************************************************************************/
#define MYUBRR(BAUD) (F_CPU/16/(BAUD)-1)


/************************************************************************
 *                      Declaración de Funciones
 ************************************************************************/

void USART_Init(int baudrate);
void USART_Init2(int baudrate,unsigned char stop_bits, unsigned char parity,unsigned char data_size);
void USART_PutChar(char c);
int USART_GetChar();
void USART_PutString(char *str);
int USART_Kbhit();


/************************************************************************
 * Si se define que se usen interrupciones, se crea un buffer para
 * almacenar los datos recibidos, por default es de 64, para no ocupar
 * mucho espacio en memoria RAM. *
 ************************************************************************/
#if defined(USE_USART_INTERRUPTS)
#define USE_USART_RX_INTERRUPT
#define USE_USART_TX_INTERRUPT
#endif

#if defined(USE_USART_RX_INTERRUPT)
    #include <avr/interrupt.h>
    #define MAX_IN_BUFFER 64
    volatile char _rx_buffer[MAX_IN_BUFFER];
    volatile unsigned int _headrx;
    volatile unsigned int _tailrx;
#endif

#if defined(USE_USART_TX_INTERRUPT)
    #include <avr/interrupt.h>
    #define MAX_OUT_BUFFER 64
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
#if defined(USE_USART_STDIO)
    #include <stdio.h>
    static int _usart_putchar(char c, FILE *stream);
    static int _usart_getchar(FILE *stream);
    static FILE _myiostream = FDEV_SETUP_STREAM(_usart_putchar, _usart_getchar, _FDEV_SETUP_RW);
#endif


/************************************************************************
 *          Implementacion de las funciones de la librería
 ************************************************************************/

/************************************************************************
 * USART_Init
 *
 * Programa la USART del AVR con una configuración de 8 bits de palabra,
 * sin paridad y un bit de stop a una velocidad "baudrate".
 * Tambien habilita las interrupciones de recepcion de dato si se defie
 * USE_USART_INTERRUPT y el uso de entrada y salida estandar si se define
 * USE_USART_STDIO.
 *
 * Recibe:
 *      -baudrate: Velocidad en baudios a la que trabajará la USART.
 * 
 *
 ************************************************************************/
void USART_Init(int baudrate) {

    USART_Init2(baudrate, USART_STOP_BITS_1,
                USART_PARITY_OFF,
                USART_DATA_SIZE_8);

}

/************************************************************************
 * USART_Init2
 *
 * Programa la USART del AVR con la confguracion especificada por el
 * programador. A diferencia de USART_Init, se debe especificar el
 * tamaño de palabra, la paridad, los bits de stop y el baudaje.
 * Tambien habilita las interrupciones de recepcion de dato si se hace
 * alguna definición de ellas y el uso de entrada y salida estandar si se define
 * USE_USART_STDIO.
 *
 * Recibe:
 *
 *       baudrate:  Velocidad en baudios a la que trabajará la USART.
 *       strop_bits:    Numero de bits de parada
 *                          USART_STOP_BITS_1       -   1 Bit de parada.
 *                          USART_STOP_BITS_2       -   2 Bits de parada.
 *       parity:        Paridad.
 *                          USART_PARITY_OFF        -   Sin paridad
 *                          USART_PARITY_EVEN_ON    -   Paridad Par
 *                          USART_PARITY_ODD_ON     -   Paridad Impar
 *       data_size: Tamaño de palabra
 *                          USART_DATA_SIZE_5       -   Tamaño de palabra de 5 bits
 *                          USART_DATA_SIZE_6       -   Tamaño de palabra de 6 bits
 *                          USART_DATA_SIZE_7       -   Tamaño de palabra de 7 bits
 *                          USART_DATA_SIZE_8       -   Tamaño de palabra de 8 bits
 *
 ************************************************************************/
void USART_Init2(int baudrate,
            unsigned char stop_bits,
            unsigned char parity,
            unsigned char data_size){

    /*Se programa el valor del baudrate segun la formula del datasheet*/
    UBRRL = MYUBRR(baudrate);
    UBRRH = MYUBRR(baudrate) >> 8;

    UCSRC = _BV(URSEL) | stop_bits | parity | data_size;

    /*Habilitamos el transmisor y el receptor*/
    UCSRB = _BV(RXEN) | _BV(TXEN);

#if defined(USE_USART_RX_INTERRUPT)
    UCSRB |= _BV(RXCIE);
    _headrx=0;
    _tailrx=0;
#endif

#if defined(USE_USART_TX_INTERRUPT)
    UCSRB |= _BV(TXCIE);
    _headtx=0;
    _tailtx=0;
    _txbusy=0;
#endif

#ifdef USE_USART_STDIO
    stdout = stdin = & _myiostream;
#endif

}

/************************************************************************
 * USART_PutChar
 *
 * Envia un byte por el puerto serie.
 *
 * Recibe:
 *
 *      - byte: Dato a enviar por el puerto serie.
 ************************************************************************/
void USART_PutChar(char c) {

#if defined(USE_USART_TX_INTERRUPT)

    if(!_txbusy) {

        _txbusy=1;
        UDR = c;

    }
    else {

        UCSRB &= ~_BV(TXCIE);

        _tx_buffer[_tailtx++] = c;

        if(_tailtx>MAX_OUT_BUFFER)
            _tailtx=0;

        UCSRB |= _BV(TXCIE);

    }

#else
    while (!(UCSRA & _BV(UDRE)));
    UDR = c;
#endif


}

/************************************************************************
 * USART_GetChar
 *
 * Lee el dato recibido por el puerto serie.
 * Si se define USE_USART_INTERRUP el dato se leera
 * del buffer de entrada, de lo contrario esperara a
 * que un dato este disponible en el registro de entrada.
 *
 *  Devuelve:
 *      El dato leido del puerto serie o del buffer de entrada.
 *
 ************************************************************************/
int USART_GetChar() {

#if defined(USE_USART_RX_INTERRUPT)
    char ret=-1;

    if(_headrx != _tailrx) {
        ret=_rx_buffer[_headrx++];
        if(_headrx>MAX_IN_BUFFER)
        _headrx=0;

    }

    return ret;
#else
    while (!(UCSRA & _BV(RXC)));
    return UDR;
#endif
}
/************************************************************************
 * USART_PutString_rx_bu
 *
 * Envia una cadena de caracteres por el puerto serie.
 *
 * Recibe:
 *      - str:      Apuntador a la cadena de caracteres.
 ************************************************************************/
void USART_PutString(char *str) {

    while (*str)
        USART_PutChar(*str++);
}

/************************************************************************
 * USART_Kbhit
 *
 * Indica si hay algun dato disponible para leer del registro de
 * recepcion. Si se define USE_USART_RX_INTERRUP, la funcion devolvera
 * el numero de datos disponibles en el buffer de entrada, de lo
 * contrario devolvera 1 si hay un dato listo en el registro de
 * recepcion o 0 si aun no hay dato listo.
 *
 ************************************************************************/
int USART_Kbhit() {

#if defined(USE_USART_RX_INTERRUPT)
    return _tailrx - _headrx;
#else
    return (UCSRA & _BV(RXC));
#endif

}

/************************************************************************
 * ISR(USART_RCX_vect)
 *
 * Funcion que atiende la interrupcion de dato recibido por el
 * puerto serie. Almacena el dato recibido en el buffer de entrada
 * e incrementa el contador de datos recibidos.
 *
 * Solo se usa si se define USE_USART_RX_INTERRUPT ó USE_USART_INTERRUPTS
 ************************************************************************/
#if defined(USE_USART_RX_INTERRUPT)

ISR(USART_RXC_vect) {

    _rx_buffer[_tailrx++]=UDR;

    if(_tailrx>MAX_IN_BUFFER)
        _tailrx=0;
}
#endif

/************************************************************************
 * ISR(USART_TCX_vect)
 *
 * Funcion que atiende la interrupcion transmisor vacío.
 * Envia por el puerto serie el siguiente dato del buffer de salida.
 *
 * Solo se usa si se define USE_USART_TX_INTERRUPT ó USE_USART_INTERRUPTS
 ************************************************************************/
#if defined(USE_USART_TX_INTERRUPT)

ISR(USART_TXC_vect) {

    _txbusy=0;
    if(_headtx != _tailtx) {

        _txbusy=1;
        UDR = _tx_buffer[_headtx++];
        if(_headtx>MAX_OUT_BUFFER)
        _headtx=0;

    }

}
#endif


/************************************************************************
 * Funciones para el uso de la entrada y la salida estandar con la
 * USART.
 ************************************************************************/


#ifdef USE_USART_STDIO

/************************************************************************
 * Funcion para el envio de un caracter mediante la salida estandar.
 ************************************************************************/
static int _usart_putchar(char c, FILE *stream) {
    if(c=='\n')
        _usart_putchar('\r',stream);
    USART_PutChar(c);
    return 0;
}

/************************************************************************
 * Funcion para la recepcion de un caracter mediante la entrada estandar.
 ************************************************************************/
static int _usart_getchar(FILE *stream) {
    char incomming;
    while(!USART_Kbhit());


    if((incomming=USART_GetChar())==13)
            incomming='\n';
    _usart_putchar(incomming,stream);

    return incomming;
}

#endif

#endif /* USART_H_ */
