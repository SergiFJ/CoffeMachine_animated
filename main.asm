/* Main.c 
 * Processor: PIC18F45K22
 * Compiler:  MPLAB XC8
 */

#include <xc.h>
#include <string.h>
#include <stdio.h>
#include "config.h"
#include "GLCD.h"
#include "cafetera.h"
#define _XTAL_FREQ 8000000  

const char * s1 = "L5 Individual\n";
const char * s2 = "--------\n";
const char * s3 = "Sergi Font Jane\n";

extern int percentatgenum;
extern char posbarra;
extern int segons;
extern int decimes;
extern char fentcafe;
extern char actualitzar;
extern char final;



void tic(){
   if (decimes == 0 && segons != 0){
      decimes = 9;
      --segons;
      if (segons > 4){
	 ClearDot(59,posbarra);
	 ClearDot(60,posbarra);
	 --posbarra;
      }
   }
   else if (decimes == 1 && segons == 0){
      --decimes;
      fentcafe = 0;
      final = 1;
   }
   else
      --decimes;
      
   if (decimes < 0) decimes = 0;
   actualitzar = 1;
}


void configPIC(){
   ANSELA=0x00; 
   ANSELB=0x00;                  
   ANSELC=0x00;                  
   ANSELD=0x00;                  
   
   TRISD=0x00;
   TRISC=0xFF;
   TRISB=0x00;
    
   PORTD=0x00;
   PORTB=0x00;
}


void configTimer(){
   T08BIT = 0;
   T0CS = 0;
   PSA = 0;
   T0CONbits.T0PS = 0b001;
   TMR0 = 15536; //carrega del timer
   TMR0IF = 0;
   TMR0IE = 1;
   GIE = 1;
   IPEN = 1;
   TMR0H = 1;
   TMR0ON = 0;
}


void interrupt RSI(){
   if (TMR0IF && TMR0IE){
      TMR0 = 15536;
      tic();//REDUIR 0.1 SEGONS
      TMR0IF = 0;
   }
}

/////COM A MINIM HA D'HAVER UN 5% D'AIGUA PERQUE PER FER UN CAFE SEMPRE ES NECESSITA AIGUA//////
////LA BARRA INDICA LA QUANTITAT D'AIGUA A POSAR, NO EL TEMPS QUE TARDA///////

void main(void)
{
   configPIC(); 
   configTimer();
   
   GLCDinit();		   //Inicialitzem la pantalla
   clearGLCD(0,7,0,127);   //Esborrem pantalla
   setStartLine(0);        //Definim linia d'inici

   writeTxt(2, 8, s1);
   writeTxt(3,10,s2);
   writeTxt(4,6,s3);
   __delay_ms(1000);
   clearGLCD(2,4,0,127);
   
   estatinicial();
   
   char flancRC0 = 0;
   char flancRC1 = 0;
   
   
   while (1)
   {  
      if (fentcafe == 0){
	 if (PORTCbits.RC0 == 0) flancRC0 = 1;
	 if (PORTCbits.RC1 == 0) flancRC1 = 1;

	 if (PORTCbits.RC0 && flancRC0){	//augmentar
	    __delay_ms(100);
	    if (PORTCbits.RC1 == 0) flancRC1 = 1;
	    if (PORTCbits.RC1 && flancRC1){	//fer cafe
	       flancRC1 = 0;
	       cafe();
	    }
	    else {
	       if (percentatgenum != 100)
		  augmentar();      
	    }
	    flancRC0 = 0;
	 }
	 
	 if (PORTCbits.RC1 && flancRC1){	//disminuir
	    if (PORTCbits.RC0 == 0) flancRC0 = 1;
	    if (PORTCbits.RC0 && flancRC0){	//fer cafe
	       flancRC0 = 0;
	       cafe();
	    }
	    else {
	       if (percentatgenum != 5)
		  disminuir();
	    }
	    flancRC1 = 0;
	 }
      }
      
      if (final){
	 acaba();
	 
      }
   }
}
