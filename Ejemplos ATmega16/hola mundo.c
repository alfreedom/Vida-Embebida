 /**************************************************************************************
 *  Hola Mundo!
 *  
 *       Archivo:  hola mundo.c
 *         Autor:  Alfredo Orozco de la Paz
 *         Fecha:  8/12/2013
 *        e-mail:  alfredoopa@gmail.com
 *
 *    Procesador:  ATmega16
 *    Frecuencia:  8 MHz
 *    Compilador:  GNU avr-gcc
 *
 *   
 *   Descripción:
 * 
 *     Enciende y apaga leds en el puerto B con retarods de 1 segundo.
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
#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRB = 0xFF;
    PORTB = 0;

    while(1)
    {
        PORTB = 0xFF;
        _delay_ms(1000);
        PORTB = 0;
        _delay_ms(1000);
    }

    return 0;
}
