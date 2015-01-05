/***************************************************************************************
 *   Proyecto: timer0-fastpwm-m16
 * 
 *      Archivo:  ejemplo1.c
 *        Autor:  Alfredo Orozco de la Paz
 *        Fecha:  4 Enero del 2015
 *   Procesador:  ATmega16 ATmega32
 *   Frecuencia:  8 MHz
 *   Compilador:  GNU avr-gcc 
 *
 *  Descripción:
 *
 *      Este ejemplo usa el timer0 para generar una señal PWM por el pin OC0 ().
 *      En la salida del pin OC0 se conecta un led el cual variará la intensidad
 *      segun el periodo de trabajo de la señal PWM.
 *
 *      El LED incrementara su brillo de 0 a 255  y de 255 a 0 con incrementos de 
 *      5 unidades a un intervalo de 50 ms por incremento, lo que dara el efecto 
 *      de FADE-IN y FADE-OUT.
 *
 ***************************************************************************************
 *
 *    Copyright:
 *
 *        Copyrigth© 2015
 *        Alfredo Orozco
 *        e-mail:  alfredoopa@gmail.com
 *        www.vidaembebida.wordpress.com
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

/************************************************************************ 
*                       INCLUSION DE LIBRERIAS  
************************************************************************/
#include <avr/io.h>
#include <util/delay.h>
 
/************************************************************************ 
*                         FUNCIONES PROTOTIPO   
************************************************************************/
void InitSystem()
{
    // Pin OCR0 como salida.
    DDRB = _BV(PB3);

    // WGM00 y WGM01 = 1 : Modo FAST-PWM.
    // COM01 = 1 : Señal No invertida.
    // CS01 = 1 :  Preescaler de 8.
    TCCR0 = _BV(WGM00) | _BV(WGM01) | _BV(COM01) | _BV(CS01);

    
}
/******************
 *      MAIN      *
 ******************/
int main(void) {

    char brillo = 0;
    int  fadein = 1;

    InitSystem();

    while(1) {  

        // Escribe el brillo del LED.
        OCR0 = brillo;

        // Si es FADE-IN incrementa el brillo, si no, es FADE-OUT y decrementa el brillo,
        if(fadein)
            brillo += 5;
        else
            brillo -= 5;

        // Si el brillo es 0 (despues de un FADE-OUT)
        // o si el brillo es 255 (despues de un FADE IN)
        // inercambia el FADE.
        if(brillo == 0  || brillo ==  255)
            fadein = !fadein;

        // Espera 50 miliengundos.
        _delay_ms(50);
    }

}
