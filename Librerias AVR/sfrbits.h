/**************************************************************************************
 *  sfrbits.h
 *
 *
 *           Autor:  Alfredo Orozco de la Paz
 *         Archivo:  sfrbits.h
 *           Fecha:  25/12/2013
 *          e-mail:  alfredoopa@gmail.com
 *
 *         Familia:  AVRmega, AVRtiny
 *      Compilador:  GNU avr-gcc
 *
 *  Descripción:
 *  
 *      Libreria  para  crear  campos  de bits (bitfields) de registros y        
 *      variables mapeados en la memoria de datos para microcontroladores 
 *      AVR utilizando avr-libc.
 *
 *      La  libreria  declara 3 uniones para manipular registros de 8, 16
 *      y  32  bits, que  son SFRbits8, SFRbits16 y SFRbits32 que acceden
 *      a cada bit  individualmente o a  un  grupo  de bits definidios en
 *      cada una de  ellas.  Tambien  define  una  macro  que facilita el 
 *      mapeo de  un  registro en una estructura bitfield. Con esta macro
 *      se definen  aqui mismo otras macros que  mapean  registros en las
 *      estructuras aqui declaradas.
 *      
 *      Los registros mapeados en esta libreria son  los  registros PORTx,
 *      DDRx y PINx asociados a los puertos A, B, C y D.
 *
 *    --------------------------------------------------------------------------------- 
 *    | SFRbits8:
 *    |     Estructura para manipular registros de 8 bits, se puede 
 *    |     acceder a cada bit del registro mediante "B0"-"B7", 
 *    |     o al nibble alto y bajo con "NLOW" y "NHIGH".
 *    ---------------------------------------------------------------------------------
 *    | SFRbits16:
 *    |     Estructura para manipular registros de 16 bits, se puede
 *    |     acceder a cada bit del registro mediante "B0"-"B15",
 *    |     o al byte alto y bajo con "BLOW" y "BHIGH".
 *    ---------------------------------------------------------------------------------
 *    | SFRbits32:
 *    |     Estructura para manipular registros de 32 bits, se puede
 *    |     acceder a cada bit del registro mediante "B0"-"B31", a
 *    |     la palabra alta y baja mediante "WLOW" y "WHIGH" o a cada
 *    |     byte con "BYTE1", "BYTE2", "BYTE3" y "BYTE4".
 *    ---------------------------------------------------------------------------------
 *    | SFR_STRUCT_BITS(STRUCT,SFR) ( *( volatile STRUCT * ) _SFR_MEM_ADDR(SFR))
 *    |     Macro para mapear el registro SFR en la estructura STRUCT.
 *    |     STRUCT se castea a un apuntador de una estructura bitfiel y se
 *    |     dereferencia.
 *    ---------------------------------------------------------------------------------
 *    | SFR_BITS8(SFR) SFR_STRUCT_BITS(SFRbits8,(SFR))
 *    |     Macro para mapear el registro SFR en la estructura SFRbits8.
 *    |     Para registros de 8 bits.
 *    ---------------------------------------------------------------------------------
 *    | #define SFR_BITS16(SFR) SFR_STRUCT_BITS(SFRbits16,(SFR))
 *    |     Macro para mapear el registro SFR en la estructura SFRbits16.
 *    | Para registros de 16 bits.
 *    ---------------------------------------------------------------------------------
 *    | #define SFR_BITS32(SFR) SFR_STRUCT_BITS(SFRbits32,(SFR))
 *    |     Macro para mapear el registro SFR en la estructura SFRbits32.
 *    |     Para registros de 32 bits.
 *    ---------------------------------------------------------------------------------
 *          
 *  Modos de uso:
 *  
 *  Mapear un registro en una estructura:
 *      
 *      #define UCSRA0bits SFR_BITS8(UCSRA0)
 *      
 *      
 *  Modificar los bits de una variable mapeandola en una estructura:
 *  
 *      byte myByte = 0xFF;
 *      word myWord = 0xFFFF;
 *      dword myDword = 0xFFFFFFFF 
 *      
 *      SFR_BITS8(myByte).NLOW=0x2;
 *      SFR_BITS8(myByte).B7=0;
 *      
 *      SFR_BITS16(myWord).BLOW=0x55;
 *      SFR_BITS16(myWord).B15=0;
 *       
 *      SFR_BITS32(myDword).BYTE1=0xAA;
 *      SFR_BITS32(myDword).WHIGH=0x8822;
 *      SFR_BITS32(myDword).B7=0;
 *      
 *          ##resultado:  
 *                      myByte  = 0x72
 *                      myWord  = 0x7F55
 *                      myDword = 0x882200AA
 *      
 *  
 *  Mapear un registro en una estructura custom:
 *  
 *      typedef union TCCR0bits_t{
 *      
 *          byte value;
 *          struct{
 *              byte CS0    : 3;        
 *              byte WGM01  : 1; 
 *              byte COM0   : 2;
 *              byte WGM00  : 1;
 *              byte FOC0   : 1;
 *          };  
 *          
 *      }TCCR0b;    
 *  
 *  
 *      #define TCCR0bits SFR_STRUCT_BITS(TCCR0b,TCCR0)
 *  
 *      TCCR0bits.CS0=5;
 *      TCCR0bits.WGM01=0;
 *      TCCR0bits.CM0=3;
 *      TCCR0bits.WGM00=1;
 *  
 *      TCCR0bits.value=0x35;
 *  
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

#ifndef _SFRBITS_H_
#define _SFRBITS_H_

#define HIGH 1
#define LOW  0

#define INPUT  0
#define OUTPUT 1

/************************************************************************/
/* Tipos de datos basicos                                               */
/************************************************************************/
typedef uint8_t byte;
typedef uint16_t word;
typedef uint32_t dword;

/************************************************************************/
/* Estructura para maniupular variables y registros de 8 bits          */
/************************************************************************/
typedef union SFRbits8_t{
    
    byte value;
    struct{
        byte NLOW  :4;
        byte NHIGH  :4;
    };
    struct{
        byte B0 :1;
        byte B1 :1;
        byte B2 :1;
        byte B3 :1;
        byte B4 :1;
        byte B5 :1;
        byte B6 :1;
        byte B7 :1;     
    };
    
}SFRbits8;


/************************************************************************/
/*      Estructura para maniupular variables y registros de 16 bits     */
/************************************************************************/
typedef union SFRbits16_t{
    
    word value;
    
    struct{
        word BLOW  :8;
        word BHIGH :8;
    };
    struct{
        word B0 :1;
        word B1 :1;
        word B2 :1;
        word B3 :1;
        word B4 :1;
        word B5 :1;
        word B6 :1;
        word B7 :1;
        word B8 :1;
        word B9 :1;
        word B10 :1;
        word B11 :1;
        word B12 :1;
        word B13 :1;
        word B14 :1;
        word B15 :1;
    };
    
}SFRbits16;

/************************************************************************/
/*      Estructura para maniupular variables y registros de 32 bits     */
/************************************************************************/
typedef union SFRbits32_t{
    
    dword value;
    struct{
        dword WLOW  :16;
        dword WHIGH :16;
    };
    struct{
        dword BYTE1 :8;
        dword BYTE2 :8;
        dword BYTE3 :8;
        dword BYTE4 :8;
    };
    struct{
        dword B0 :1;
        dword B1 :1;
        dword B2 :1;
        dword B3 :1;
        dword B4 :1;
        dword B5 :1;
        dword B6 :1;
        dword B7 :1;
        dword B8 :1;
        dword B9 :1;
        dword B10 :1;
        dword B11 :1;
        dword B12 :1;
        dword B13 :1;
        dword B14 :1;
        dword B15 :1;
        dword B16 :1;
        dword B17 :1;
        dword B18 :1;
        dword B19 :1;
        dword B20 :1;
        dword B21 :1;
        dword B22 :1;
        dword B23 :1;
        dword B24 :1;
        dword B25 :1;
        dword B26 :1;
        dword B27 :1;
        dword B28 :1;
        dword B29 :1;
        dword B30 :1;
        dword B31 :1;       
    };
    
}SFRbits32;

#define SFR_STRUCT_BITS(STRUCT,SFR) ( *( volatile STRUCT * ) _SFR_MEM_ADDR(SFR))

#define SFR_BITS8(SFR) SFR_STRUCT_BITS(SFRbits8,(SFR))
#define SFR_BITS16(SFR) SFR_STRUCT_BITS(SFRbits16,(SFR))
#define SFR_BITS32(SFR) SFR_STRUCT_BITS(SFRbits32,(SFR))



/*##### DEFINICIONES PARA PORTA #####*/
/*#####  DEFINITIONS FOR PORTA  #####*/
#if defined(PORTA) 

#define DDRAbits SFR_BITS8(DDRA)
#define PORTAbits SFR_BITS8(PORTA)
#define PINAbits SFR_BITS8(PINA)

#endif

/*##### DEFINICIONES PARA PORTB #####*/
/*#####  DEFINITIONS FOR PORTB  #####*/
#if defined(PORTB) 

#define DDRBbits SFR_BITS8(DDRB)
#define PORTBbits SFR_BITS8(PORTB)
#define PINBbits SFR_BITS8(PINB)

#endif

/*##### DEFINICIONES PARA PORTC #####*/
/*#####  DEFINITIONS FOR PORTC  #####*/
#if defined(PORTC)

#define DDRCbits SFR_BITS8(DDRC)
#define PORTCbits SFR_BITS8(PORTC)
#define PINCbits SFR_BITS8(PINC)

#endif

/*##### DEFINICIONES PARA PORTD #####*/
/*#####  DEFINITIONS FOR PORTD  #####*/
#if defined(PORTD)

#define DDRDbits SFR_BITS8(DDRD)
#define PORTDbits SFR_BITS8(PORTD)
#define PINDbits SFR_BITS8(PIND)

#endif

#endif
/*fin de archivo*/
