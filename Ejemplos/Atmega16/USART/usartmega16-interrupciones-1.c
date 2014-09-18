/***************************************************************************************
*   Manejo de la USART con interrupciones.
* 
*       Archivo:  usartmega16.c
*         Autor:  Alfredo Orozco de la Paz
*         Fecha:  27/07/2014
*        e-mail:  alfredoopa@gmail.com
*
*    Procesador:  ATmega16
*    Frecuencia:  8 MHz
*    Compilador:  GNU avr-gcc
*
*    Descripción:
*        Programa  para  el  manuejo  de la USART del ATmega16.
*        El programa maneja la interrupción por dato recibido en
*        la USART, que lee el dato recibido y lo envía nuevamente.
*        (ECO).
*
***************************************************************************************
*
*    Copyright:
*
<<<<<<< HEAD
*        Copyrigth© 2014
=======
*        Copyrigth© 2013
>>>>>>> f0ee67e0f18cf41141dbeb81be02813fd1fe6fb6
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
*	  SIN   NINGUNA   GARANTÍA,  incluso   sin   la   garantía   implícita  de
*        COMERCIALIZACIÓN  o  IDONEIDAD PARA UN PROPÓSITO PARTICULAR. consulte la
*        Licencia Pública General de GNU para más detalles.
*
*        Debería haber recibido una copia de  la  Licencia Pública General de GNU
*        junto con este programa; si no, visite http://www.gnu.org/licenses.
*
*
***************************************************************************************/

#define BAUD	9600
#define F_CPU	8000000L

#include <avr/io.h>
/* Macros para el calculo del Registro UBRR */
#include <util/setbaud.h>
#include <avr/interrupt.h>

void UsartInit();
void UsartPutChar(char c);
void UsartPutString(char* s);
char UsartGetChar();
char UsartKbhit();

/* Manejador de la interrupción por dato recibido en l USART */
ISR(USART_RXC_vect) {

	/* Se envía el dato recibido */
	UsartPutChar(UDR);

}

int main() {

    
    UsartInit();

    /* Se habilitan las interrupciones globales */
    sei();

    UsartPutString("Ejemplo simple de ECO con interrupciones en el ATmega16.\n");
    UsartPutString("Presione cualquier tecla:\n");
    
    while(1) {}

    return 0;
}

void UsartInit() {

	UBRRL = UBRRL_VALUE;
	UBRRH = UBRRH_VALUE;

	UCSRC = _BV(URSEL) | _BV(UCSZ0) | _BV(UCSZ1);
	
	/* Se habilita la interrupción por dato recibido. */
	UCSRB = _BV(RXEN) | _BV(TXEN)| _BV(RXCIE);
}

void UsartPutChar(char c) {
	while (!(UCSRA & _BV(UDRE)));
	UDR = c;
}

void UsartPutString(char* s) {
	while (*s)
	    UsartPutChar(*s++);
}

char UsartGetChar() {
	while (!(UCSRA & _BV(RXC)));
	return UDR;
}

char UsartKbhit() {
	return (UCSRA & _BV(RXC));
}

