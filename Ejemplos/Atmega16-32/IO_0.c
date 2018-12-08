/**************************************************************************************
 *  Ejemplo Puertos 1
 *   
 *       Archivo:  usartmega16.c
 *         Autor:  Alfredo Orozco de la Paz
 *         Fecha:  8/07/2014
 *        e-mail:  alfredoopa@gmail.com
 *
 *    Procesador:  ATmega16
 *    Frecuencia:  8 MHz
 *    Compilador:  GNU avr-gcc
 *
 * 
 *   Descripción:
 * 
 *      Se lee un numero de 4 bits por los 4 bits menos significativos del
 *      PUERTO A y se refleja el numero por los 4 bits mas significativos
 *      del mismo PUERTO A
 *   
 ***************************************************************************************
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
 *        SIN   NINGUNA   GARANTÍA,  incluso   sin   la   garantía   implícita  de
 *        COMERCIALIZACIÓN  o  IDONEIDAD PARA UN PROPÓSITO PARTICULAR. consulte la
 *        Licencia Pública General de GNU para más detalles.
 *
 *        Debería haber recibido una copia de  la  Licencia Pública General de GNU
 *        junto con este programa; si no, visite http://www.gnu.org/licenses.
 *
 *
 ***************************************************************************************/


#define F_CPU 8000000L  //definimos la frecuencia del reloj para la librería delay y otras librerias.

#include <avr/io.h>     //incluimos la libreria para los registros de uc.
#include <util/delay.h> //libreria de retardos.


int main(void)
{
    unsigned char entrada=0;
    DDRA = 0xF0;        //Puerto A bajo como entrada y alto como salida.
    PORTA = 0x0F;       //Apagamos los leds y habilitamos resistencias PULL-UP en entradas.

    while(1)            //ciclo infinito.
    {
        entrada = PINA;         //leemos el estado de las entradas.
        PORTA = entrada << 4;   //mandamos el estado de la entrada a los leds.
    }

    return 0;
}
