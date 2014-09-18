/***************************************************************************************
 *
 *      Archivo:  ejemplo1.c
 *        Autor:  Alfredo Orozco de la Paz
 *        Fecha:  16 Sep, 2014
 *   Procesador:  ATmega16 ATmega32
 *   Frecuencia:  8 MHz
 *   Compilador:  GNU avr-gcc 
 *
 *  Descripción:
 *  
 *      Uso del Timer/Counter0 en modo CTC para generar una onda cuadrada  por el
 *      pin OC0 de una frecuencia de 38kHz para controlar un led infrarrojo cone-
 *      ctado a este pin, con el fin de simular un control remoto infrarrojo.
 *
 ***************************************************************************************
 *
 *    Copyright:
 *
 *        Copyrigth© 2014
 *        Alfredo Orozco
 *        e-mail:  alfredoopa@gmail.com
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
 ***************************************************************************************/
 
/************************************************************************ 
*                       DEFINICION DE CONSTANTES   
************************************************************************/
#define F_CPU 8000000
#define BUTTON PORTD2 // Push Button conectado a PD2
/************************************************************************ 
*                       INCLUSION DE LIBRERIAS  
************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
 
/************************************************************************ 
*                         FUNCIONES PROTOTIPO   
************************************************************************/
void InitiSystem(){
 
    DDRD &= ~_BV(BUTTON); //Puerto PD2 como entrada.
    PORTD |= _BV(BUTTON); // Activa Pull-Up de PD2
 
    // Timer0 en modo CTC, prescaler de 8 y cambio de estado de pin OC0
    // cada coincidencia del registro OCR0 y TCNT0
    TCCR0 = _BV(WGM01) | _BV(COM00) | _BV(CS01);
 
    // Registro OCR0 con 12 para generar una señal de 38khz
    OCR0 = 12;
 
    // Habilita interrupcion en INT0
    GICR = _BV(INT0);
    // Configura interrupcion por flanco de bajada en pin INT0
    MCUCR = _BV(ISC01);
    // Habilita interrupciones globales.
    sei();
 
}
 
/******************
 *      MAIN      *
 ******************/
int main(void) {
 
    InitiSystem();
 
    while(1) {  
    }
 
    return 0;
}
 
ISR(INT0_vect){
 
    // Cambia la dirección del puerto OC0, si es de entrada
    // lo pone como salida (enciende led) si es de salida
    // lo pone como entrada (apaga el led)
 
    DDRB ^= _BV(PB3);
 
    // pausa para eliminar rebotes.
    _delay_ms(30);
}
