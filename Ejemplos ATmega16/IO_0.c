/**********************************************************************
* Ejemplo Puertos 1
*
* Nombre del Archivo:	IO_0.c
* Microcontrolador:		Atmega16
* Compilador:			avr-gcc
* IDE:		            Atmel Studio® IDE v6 or later
*
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Autor: 	Alfredo Orozco de la Paz
* e-mail:	alfredoopa@gmail.com
* Fecha:	8/Julio/2014
*
* DESCRIPCIÓN:
*	Se lee un numero de 4 bits por los 4 bits menos significativos del
*	PUERTO A y se refleja el numero por los 4 bits mas significativos
*	del mismo PUERTO A
*	
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
* NOTAS ADICIONALES:
*
*	Copyrigth© 2013  
*	Alfredo Orozco
*	
*	Este programa es software libre; usted lo puede distribuir y/o modificar
*	bajo los terminos de la General Public License GNU, según es publicada
*	en la Free Software Foundation; ya se la versión 2 de la Licencia, o
*	(a su elección) una versión posterior.
*
*	Este programa se distribuye con la esperanza de que sea útil,
*	pero SIN NINGUNA GARANTÍA, incluso sin la garantía implícita de
*	COMERCIALIZACIÓN o IDONEIDAD PARA UN PROPÓSITO PARTICULAR. consulte la
*	Licencia Pública General de GNU para más detalles.
*
+	Debería haber recibido una copia de la Licencia Pública General de GNU
*	junto con este programa; si no, escriba a la Free Software
+	Fundación, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 EE.UU.
*
*
**********************************************************************/


#define F_CPU 8000000L	//definimos la frecuencia del reloj para la librería delay y otras librerias.

#include <avr/io.h>		//incluimos la libreria para los registros de uc.
#include <util/delay.h>	//libreria de retardos.


int main(void)
{
	unsigned char entrada=0;
	DDRA = 0xF0;		//Puerto A bajo como entrada y alto como salida.
	PORTA = 0x0F;		//Apagamos los leds y habilitamos resistencias PULL-UP en entradas.

	while(1)			//ciclo infinito.
	{
		entrada = PINA;			//leemos el estado de las entradas.
		PORTA = entrada << 4;	//mandamos el estado de la entrada a los leds.
	}

	return 0;
}