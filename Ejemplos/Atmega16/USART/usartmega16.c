/***************************************************************************************
*   Manejo de la USART
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
*        Espera a que reciba un dato por la USART y lo devuelve
*        por el mismo puerto serie (ECO).
*
*
***************************************************************************************
*
*    Copyright:
*
*        Copyrigth© 2014
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
// Macros para el calculo del Registro UBRR
#include <util/setbaud.h>

void UsartInit();
void UsartPutChar(char c);
void UsartPutString(char* s);
char UsartGetChar();
char UsartKbhit();

int main() {

    UsartInit();

    UsartPutString("Ejemplo simple de ECO con ATmega16.\n");
    UsartPutString("Presione cualquier tecla:\n");
    
    while(1) {

        if(UsartKbhit()) {

            UsartPutChar(UsartGetChar());

        }
    }

    return 0;
}

void UsartInit() {

	UBRRL = UBRRL_VALUE;
	UBRRH = UBRRH_VALUE;

	UCSRC = _BV(URSEL) | _BV(UCSZ0) | _BV(UCSZ1);

	UCSRB = _BV(RXEN) | _BV(TXEN);
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

