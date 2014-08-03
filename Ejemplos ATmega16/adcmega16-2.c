 /**************************************************************************************
 *  Ejemplo del ADC del ATmega16 con interrupciones
 *  
 *       Archivo:  adcmega16-2.c
 *         Autor:  Alfredo Orozco de la Paz
 *         Fecha:  2/08/2014
 *    Procesador:  ATmega16 ATmega32
 *    Frecuencia:  8 MHz
 *    Compilador:  GNU avr-gcc
 *
 *   
 *   Descripción:
 * 
 *      Ejemplo de uso del ADC en conversión modo Free Running con uso
 *      de interrupcion por conversión terminada. Usa la librería usart.h
 *      para el envío de datos por el puerto serie.
 *   
 ***************************************************************************************
 *
 *    Copyright:
 *
 *        Copyrigth© 2013
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
 *
 ***************************************************************************************/
/************************************************************************
*                       DEFINICION DE CONSTANTES
************************************************************************/
#define F_CPU   8000000L
#define USE_USART_STDIO

#define POT_PIN 0
#define delay(ms) _delay_ms((ms))
/************************************************************************
*                       INCLUSION DE LIBRERIAS
************************************************************************/
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "usart.h"
/************************************************************************
*                         FUNCIONES PROTOTIPO
************************************************************************/
void ADCInit();
void InitSystem();

/************************************************************************
*                           VARIABLES GLOBALES
************************************************************************/

/************************************************************************/


// Función que atiende la interrupción de conversión completa
ISR(ADC_vect) {

    int valorAdc=ADC;

    float voltaje = (valorAdc*5.0)/1023.0;
    int partedecimal = (voltaje - (int)voltaje) * 1000.0;

    // envia el valor del ADC por el puerto serie.
    printf("Valor ADC: %d   \tVoltaje: %d.%d v \n",valorAdc,(int)voltaje,partedecimal);
    delay(500);

    // inicia de nuevo la conversión.
    ADCSRA |= _BV(ADSC);
}

/******************
 *      MAIN      *
 ******************/
int main(void) {

    InitSystem();

    // habilta nterrupciones globales
    sei();

    // inicia primera conversión
    ADCSRA |= _BV(ADSC);

    // deja libre al micro.
    while(1){
    }

    return 0;
}

void InitSystem() {

    ADCInit();
    USART_Init(9600);

}

void ADCInit() {

    // Referencia AVCC y lectura del canal 0 para el potecionmetro
    ADMUX = _BV(REFS0) | (POT_PIN & 0x07);

    // ADC habilitado con preescaler de 128
    // Interrupcion del ADC habilitada
    // F_ADC = 8000000/128 = 62.5 KHz
    // F_MUESTREO = 62500/13 = 4.8Khz
    // T_MUESTREO = 1/4800 = 208us
    // La conversión tarda 208us.
    ADCSRA = _BV(ADEN) | _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2) | _BV(ADIE);
}
