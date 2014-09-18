/***************************************************************************************
 *
 *      Archivo:  ejemplo3.c
 *        Autor:  Alfredo Orozco de la Paz
 *        Fecha:  4/08/2014
 *   Procesador:  ATmega16 ATmega32
 *   Frecuencia:  8 MHz
 *   Compilador:  GNU avr-gcc 
 *
 *  Descripción:
 *
 *      Ejemplo 3 que muestra el uso del timer0 de 8 bits en modo normal.
 *      Se parpadea un led en el puerto B cada 1000 milisegundos, el tiempo
 *      lo marca el Timer/Counter0 en pasos de 10 milisegundos.
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
 *     si nuestro contador alcanza una cuenta máxima de 256 a un periodo de
 *     128us, el tiempo que toma el timer en desbordarse será:
 *
 *        128us * 256 = 32768 us = 32.77 ms
 *
 *     Esto quiere decir que el timer se desborda cada 32.64 milisegundos.
 *     si queremos medir un tiempo de 10ms basta hacer una regla de 3
 *
 *     256  ->  32768
 *      ?   ->  10000  (valor deseado)
 *
 *        10000
 *       ------- * 256 +1 = 79.125 (79)
 *        32768
 *
 *     cuando el timer llegue a 79 habrán transcurrido 10 milisegundos.
 *
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

/************************************************************************ 
*                       INCLUSION DE LIBRERIAS  
************************************************************************/
#include <avr/io.h>
#define RETARDO 1000  // 1000 milisegundos - 1 segundo

/******************
 *      MAIN      *
 ******************/
int main(void) {

	int milis=0;

	// Timer en modo normal, sin salida por OC0 con preescaler de 1024
	TCCR0 = _BV(CS00) | _BV(CS02);

	// Puerto B como salida.
	DDRB = _BV(PB0);
	PORTB = 0;

    while(1) {  

    	if(TCNT0 == 79) // si ya pasaron 10 milisegundos
    	{
    		TCNT0=0;
    		if((milis+=10) == RETARDO) // si ya pasaron 1000 milisegundos
			{
    			// cambia el estado del led
				PORTB ^= _BV(PB0);
				// reinicia el contador de milisegundos
				milis=0;
			}
    	}


    }

    return 0;
}
