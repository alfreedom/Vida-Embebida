 /**************************************************************************************
 *  Ejemplo de la usart0 con la librería usart0.h
 *  
 *       Archivo:  usarttest2.c
 *         Autor:  Alfredo Orozco de la Paz
 *         Fecha:  8/12/2013
 *        e-mail:  alfredoopa@gmail.com
 *
 *    Procesador:  ATmega48,ATmega88, ATmega168, ATmega328
 *    Frecuencia:  8 MHz
 *    Compilador:  GNU avr-gcc
 *
 *   
 *   Descripción:
 * 
 *     Hace un eco del dato recibido por el puerto serie usando las funciones 
 *     de  la  librería  usart0.h  habilitando  interrupciones  y  usando   la 
 *     entrada/salida estandar.
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
/* Frecuencia de trabajo 16 MHz */
#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>

/* Libreria de la USART */
#include "usart.h"

int main()
{
    /* Se inicializa la USART */
    Serial.init(9600);

    /* Funcion de la libreria para*/
    Serial.print("*** EJEMPLO DE ECO CON LA USART ***\n");

    while(1){

        /* Si se ha recibido algún daro... */
        if(Serial.available()){
            /* Imprimimos el dato por el puerto serie. */
            Serial.print( "Tecla: ");
            Serial.print(Serial.read());
            /* Espera para que no se sature el buffer */
            _delay_ms(10);
        }
    }
 
    return 0;

}
