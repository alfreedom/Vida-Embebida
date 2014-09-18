 /**************************************************************************************
 *  Ejemplo de Puertos 2
 *  
 *       Archivo:  IO_1.c
 *         Autor:  Alfredo Orozco de la Paz
 *         Fecha:  10/12/2013
 *        e-mail:  alfredoopa@gmail.com
 *
 *    Procesador:  ATmega16
 *    Frecuencia:  8 MHz
 *    Compilador:  GNU avr-gcc
 *
 *   
 *   Descripción:
 * 
 *      Enciende y apaga leds en los puertos A,B y C con diferentes 
 *      patrones.
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


#define F_CPU 8000000L  //definimos la frecuencia del reloj para la librería delay y otras librerias.

#include <avr/io.h>     //incluimos la libreria para los registros de uc.
#include <util/delay.h> //libreria de retardos.

/* Inicializa los puertos*/
void Init_System() {

    DDRA = 0xFF;
    DDRB = 0b11111111;
    DDRC = _BV(PD0) | _BV(PD1) | _BV(PD2) | _BV(PD3) | _BV(PD4) | _BV(PD5) | _BV(PD6) | _BV(PD7);

    PORTA = PORTB = PORTC = 0x00;
}

int main(void)
{
   
    Init_System();

    PORTA = 0b10101010;
    PORTB = _BV(PD0) | _BV(PD1) | _BV(PD2) | _BV(PD3);
    PORTC = 1;

    while(1)            //ciclo infinito.
    {
        PORTA = ~PORTA;
        PORTB ^= PORTB;
        PORTC = PORTC ? PORTC << 1 : 1;
        _delay_ms(1000);
    }

    return 0;
}