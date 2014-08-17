/***************************************************************************************
 * 
 *      Archivo:  ejemplo2.c
 *        Autor:  Alfredo Orozco de la Paz
 *        Fecha:  3/08/2014
 *   Procesador:  ATmega16 ATmega32
 *   Frecuencia:  8 MHz
 *   Compilador:  GNU avr-gcc 
 *
 *  Descripción:
 *
 *      Ejemplo 2 que muestra el uso del timer0 de 8 bits en modo normal.
 *      Se parpadea un led en el puerto PB0 cada que se desborda el timer0
 *      usando la interrupción por desbordamiento.
 *
 *      La frecuencia del reloj es de 8 MHz, el prescaler del timer0 es
 *      1024, con lo que la frecuencia del timer quedaría:
 *
 *      	            8000000
 *         F Timer =  ---------  =  7812.5 Hz
 *                        1024
 *
 *      el periodo de trabajo del timer es:
 *
 *                       1
 *        T timer =  ----------  =  128us por cada incremento del contador
 *                     7812.5
 *
 *     si nuestro contador alcanza una cuenta máxima de 255 a un periodo de
 *     128us, el tiempo que toma el timer en desbordarse será:
 *
 *        128us * 255 = 32.64ms
 *
 *
 ***************************************************************************************
 *
 *    Copyright:
 *
 *        Copyrigth© 2013
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
*                       INCLUSION DE LIBRERIAS  
************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>

/******************
 *      MAIN      *
 ******************/
int main(void) {

	// Timer0 modo normal, sin usar el pin OC0, prescaler de 1024
	TCCR0 = _BV(CS00) | _BV(CS02);

	// habilta interrupción por desbordamiento de timer0
	TIMSK = _BV(TOIE0);

	// habilita interrupciones globales
	sei();

	// Puerto PB0 como salida.
	DDRB = _BV(PB0);
	PORTB = 0;

    while(1) {} // CPU libre

    return 0;
}

// función para atender la interrupción
ISR(TIMER0_OVF_vect){
	// se conmuta el estado del led
	PORTB ^= _BV(PB0);
}


