/**************************************************************************************
 *  Ejempo de uso de la librería sfrbits.h
 * 
 *       Archivo: sfrbitstest1.c
 *         Autor:  Alfredo Orozco de la Paz
 *         Fecha:  06/01/2014
 *        e-mail:  alfredoopa@gmail.com
 *
 *    Procesador:  ATmega16
 *    Frecuencia:  8 MHz
 *    Compilador:  GNU avr-gcc
 *
 *    Descripción:
 * 
 *      En este ejemplo conectaremos 4 leds  a los 4 bits más significativos 
 *      del B (PB0-PB3) y 2 push buttons  conectados la PB4  y PB5 del mismo 
 *      puerto B, al presionar un push button se desplazara el led encendido 
 *      de  derecha  a  izquierda,  y  al presionar el otro se desplazará en 
 *      sentido contrario.
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

#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>
#include "sfrbits.h"

//estructura definida para manipuilar los Leds
typedef union Leds_t{
    byte value : 4;
    
    struct{
        byte led1       : 1;   //para el led 1. PB0
        byte led2       : 1;   //para el led 2. PB1
        byte led3       : 1;   //para el led 3. PB2
        byte led4       : 1;   //para el led 4. PB3
        byte btn1pull   : 1;   //para activar pull-up en el boton 1.
        byte btn2pull   : 1;   //para activar pull-up en el boton 12
        byte            : 1;   //sin uso.
        byte            : 1;   //sin uso.
    };
}Leds;
//estructura definida para manipuilar los botones
typedef struct Btns_t{
    byte       : 1;   //sin uso.
    byte       : 1;   //sin uso.
    byte       : 1;   //sin uso.
    byte       : 1;   //sin uso.
    byte left  : 1;   //Para el boton a la izquierda.
    byte right : 1;   //para el boton a la derecha.
    byte       : 1;   //sin uso.
    byte       : 1;   //sin uso.
}Btns;  

#define LEDS SFR_STRUCT_BITS(Leds,PORTB)   //Mapeamos el PORTB a la estructura Leds
#define BTNS SFR_STRUCT_BITS(Btns,PINB)   //Mapeamos el PORTB a la estructura Btns

int main(void)
{
    byte valant;
    //establecemos la direccion de los pines como salida para los leds
    //es equivalente a DDRBbits.NLOW=0xF
    DDRBbits.B0=OUTPUT;
    DDRBbits.B1=OUTPUT;
    DDRBbits.B2=OUTPUT;
    DDRBbits.B3=OUTPUT;
    
    //establecemos la direccion de los pines como entradas para los botones
    //es equivalente a DDRBbits.NHIGH=0x3
    DDRBbits.B4=INPUT;
    DDRBbits.B5=INPUT;
    
    //Activamos pull-ups en los botones
    LEDS.btn1pull=HIGH;
    LEDS.btn2pull=HIGH;
    LEDS.value=0;       //apagamos todos los leds.
    LEDS.led1=HIGH;     //encendemos el primer led
    
    while(1)        //cilco infinito
    {
            
            valant=LEDS.value;                        //guardamos el valor de los leds          
            while(BTNS.left==LOW && BTNS.right==LOW)  //mientras se presionan los dos botones
                LEDS.value=0xF;                       //encendemos todos los leds
            LEDS.value=valant;          
            
            //desplazamos a la izquieda  
            if(BTNS.left==LOW && LEDS.led4==LOW)
            {
                LEDS.led4=LEDS.led3;
                LEDS.led3=LEDS.led2;
                LEDS.led2=LEDS.led1;
                LEDS.led1=0;
            }
            //desplazamos a la derecha
            if(BTNS.right==LOW && LEDS.led1==LOW)
            {
                LEDS.led1=LEDS.led2;
                LEDS.led2=LEDS.led3;
                LEDS.led3=LEDS.led4;
                LEDS.led4=0;
            }
            
            _delay_ms(50);  //retardo anti-rebotes
    }
    
    return 0;
}
