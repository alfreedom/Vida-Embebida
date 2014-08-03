 /**************************************************************************************
 *  Ejemplo de como usar Bit Fields
 *  
 *       Archivo:  bitfields1-avr.c
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
 *      Muesta el uso de como implementar campos de bits con registros SFR.
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
#define F_CPU   8000000L
#include <avr/io.h>
#include <util/delay.h>

typedef struct DDBbits_t{

    unsigned char DD0  :1;
    unsigned char DD1  :1;
    unsigned char DD2  :1;
    unsigned char DD3  :1;
    unsigned char DD4  :1;
    unsigned char DD5  :1;
    unsigned char DD6  :1;
    unsigned char DD7  :1;
    
}volatile *DDBbits;

typedef struct PBbits_t{

    unsigned char PO0  :1;
    unsigned char PO1  :1;
    unsigned char PO2  :1;
    unsigned char PO3  :1;
    unsigned char PO4  :1;
    unsigned char PO5  :1;
    unsigned char PO6  :1;
    unsigned char PO7  :1;
    
}volatile *PBbits;

typedef struct PINBbits_t{

    unsigned char PI0  :1;
    unsigned char PI1  :1;
    unsigned char PI2  :1;
    unsigned char PI3  :1;
    unsigned char PI4  :1;
    unsigned char PI5  :1;
    unsigned char PI6  :1;
    unsigned char PI7  :1;
    
}volatile *PIBbits;

#define PORTBbits (*(PBbits)_SFR_MEM_ADDR(PORTB))
#define DDRBbits (*(DDBbits)_SFR_MEM_ADDR(DDRB))
#define PINBbits (*(PIBbits)_SFR_MEM_ADDR(PINB))

#define INPUT   0
#define OUTPUT  1

#define ON  1
#define OFF 0

#define LED PORTBbits.PO0
#define BUTTON PINBbits.PI1

int main(void)
{
    DDRBbits.DD0=OUTPUT;//Puerto P0 como salida.
    DDRBbits.DD1=INPUT; //Puerto P1 como entrada.
    PORTBbits.PO1=ON;   //Activamovs PULL-UP en el puerto P1.
    
    while(1)
    {
        while(BUTTON!=ON)   //mientras se presione el boton.
        {
            LED=ON;
            _delay_ms(300);
            LED=OFF;
            _delay_ms(300); 
        }
    }
    return 0;
}