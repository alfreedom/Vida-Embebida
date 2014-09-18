 /**************************************************************************************
 *  Ejemplo de la usart con la librería usart.h
 *  
 *       Archivo:  usarttest1.c
 *         Autor:  Alfredo Orozco de la Paz
 *         Fecha:  8/12/2013
 *        e-mail:  alfredoopa@gmail.com
 *
 *    Procesador:  ATmega16,ATmega32
 *    Frecuencia:  8 MHz
 *    Compilador:  GNU avr-gcc
 *
 *   
 *   Descripción:
 * 
 *     Hace un eco del dato recibido por el puerto serie usando las funciones 
 *     de  la  librería  usart.h  habilitando  interrupciones  y  usando   la 
 *     entrada/salida estandar.
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
 *        SIN   NINGUNA   GARANTÍA,  incluso   sin   la   garantía   implícita  de
 *        COMERCIALIZACIÓN  o  IDONEIDAD PARA UN PROPÓSITO PARTICULAR. consulte la
 *        Licencia Pública General de GNU para más detalles.
 *
 *        Debería haber recibido una copia de  la  Licencia Pública General de GNU
 *        junto con este programa; si no, visite http://www.gnu.org/licenses.
 *
 *
 ***************************************************************************************/
/* Frecuencia de trabajo 8 MHz */
#define F_CPU 8000000L

/* Definiciones para usar interrupciones RX, TX y el uso
 * de la salida estandar para printf().*/
#define USE_USART_INTERRUPTS
#define USE_USART_STDIO

#include <avr/io.h>
#include <util/delay.h>

/* Libreria de la USART */
#include "usart.h"

int main(void)
{
    /* Se inicializa la USART */
    USART_Init(9600);
    /* Se habilitan interrupciones globales */
    sei();

    /* Funcion de la libreria para*/
    USART_PutString("*** EJEMPLO DE ECO CON LA USART ***\n");

    while(1){

        /* Si se ha recibido algún daro... */
        if(USART_Kbhit()){
            /* Imprimimos el dato por el puerto serie. */
            printf( "Tecla: %c\n" , USART_GetChar() );
            /* Espera para que no se sature el buffer */
            _delay_ms(10);

        }

    }

}
