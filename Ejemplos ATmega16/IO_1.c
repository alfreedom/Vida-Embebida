/**********************************************************************
* Ejemplo Puertos 2
*
* Nombre del Archivo:   IO_1.c
* Microcontrolador:     Atmega16
* Compilador:           avr-gcc
* IDE:                  Atmel Studio® IDE v6 or later
*
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Autor:    Alfredo Orozco de la Paz
* e-mail:   alfredoopa@gmail.com
* Fecha:    9/Julio/2014
*
* DESCRIPCIÓN:
*   Enciende y apaga leds en los puertos A,B y C con diferentes 
*   patrones.
*   
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
* NOTAS ADICIONALES:
*
*   Copyrigth© 2013  
*   Alfredo Orozco
*   
*   Este programa es software libre; usted lo puede distribuir y/o modificar
*   bajo los terminos de la General Public License GNU, según es publicada
*   en la Free Software Foundation; ya se la versión 2 de la Licencia, o
*   (a su elección) una versión posterior.
*
*   Este programa se distribuye con la esperanza de que sea útil,
*   pero SIN NINGUNA GARANTÍA, incluso sin la garantía implícita de
*   COMERCIALIZACIÓN o IDONEIDAD PARA UN PROPÓSITO PARTICULAR. consulte la
*   Licencia Pública General de GNU para más detalles.
*
+   Debería haber recibido una copia de la Licencia Pública General de GNU
*   junto con este programa; si no, escriba a la Free Software
+   Fundación, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 EE.UU.
*
*
**********************************************************************/


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