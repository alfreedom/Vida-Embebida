/**************************************************************************************
 *  Ejemplo del ADC del ATmega16 con conversión manual
 *  
 *       Archivo:  adcmega16-1.c
 *         Autor:  Alfredo Orozco de la Paz
 *         Fecha:  2/08/2014
 *    Procesador:  ATmega16 ATmega32
 *    Frecuencia:  8 MHz
 *    Compilador:  GNU avr-gcc
 *
 *   
 *   Descripción:
 * 
 *      Ejemplo  de  uso  del ADC en conversión modo Free  Running. Usa 
 *      la librería usart.h para el envío de datos por el puerto serie.
 *   
 ***************************************************************************************
 *
 *        Copyrigth© 2014
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
* DEFINICION DE CONSTANTES
************************************************************************/
#define F_CPU 16000000L
#define USE_USART_STDIO

#define POT_PIN 0
#define delay(ms) _delay_ms((ms))

/************************************************************************
* INCLUSION DE LIBRERIAS
************************************************************************/
#include <avr/io.h>
#include <util/delay.h>
#include "usart.h"

/************************************************************************
* FUNCIONES PROTOTIPO
************************************************************************/
void ADCInit();
int ADCRead(unsigned char canal);

/************************************************************************/

void InitSystem() {

    ADCInit();
    Serial.init(9600);

}

/******************
*      MAIN       *
******************/
int main(void) {

    unsigned int valorAdc;
    InitSystem();

    while(1) {

        valorAdc = ADCRead(POT_PIN);
        Serial.print("Valor leido en el pin ");
        Serial.print(POT_PIN);
        Serial.print(": ");
        Serial.print(valorAdc);
        delay(500);
    }

    return 0;
}
void ADCInit() {

    // Referencia AVCC
    ADMUX = (1 << REFS0);

    // ADC habilitado con preescaler de 128
    // F_ADC = 8000000/128 = 62.5 KHz
    // F_MUESTREO = 62500/13 = 4.8Khz
    // T_MUESTREO = 1/4800 = 208us
    // La conversión tarda 208us.
    ADCSRA = (1 << ADEN) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
}
int ADCRead(unsigned char canal) {

    // seleccionamos el nuevo canal a leer solo modificando solo
    // los bits MUX0 MUX1 y MUX2.
    ADMUX =(ADMUX & 0xF8) | (canal & 0x07);

    // se inicia la conversión.
    ADCSRA |= (1 << ADSC);

    // espera a que termina la conversión.
    while(ADCSRA & (11 << ADSC));

    // regresamos el valor de la conversión.
    return ADC;
}




