/* 
 * cafetera
 */
 
#include <xc.h>
#include "GLCD.h"
#include "cafetera.h"
#include "ascii.h"
#include "stdio.h"
#define _XTAL_FREQ 8000000  

// D'us intern

int percentatgenum = 50;
char posbarra = 62;
int segons = 15;
int decimes = 0;
char fentcafe = 0;
char actualitzar = 0;
char final = 0;


char *stat[3]={"Choose\n","Serving\n","Done\n"};
char barra[36] = {0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0xBC,0xBC,0xBC,0xBC,0xBC,0xBC,0xBC,0xBC,0xBC,0xBC,0xBC,0xA4,0xA4,0xA4,0xA4,0xA4,0xA4,0xA4,0xA4,0xA4,0xA4,0xBC,0x80,0x80,0x80,0x80,0x80,0x80,0xFF};
char botodown1[11] = {0x7F,0x40,0x40,0x43,0x4F,0x5F,0x4F,0x43,0x40,0x40,0x7F};
char botodown2[11] = {0xE7,0x24,0xA4,0xA4,0xA4,0xA4,0xA4,0xA4,0xA4,0x24,0xE5};
char botoup1[11] = {0x7F,0x40,0x50,0x5C,0x5F,0x5F,0x5F,0x5C,0x50,0x40,0x7F};
char botoup2[11] = {0xE5,0x24,0x24,0x24,0x24,0xA4,0x24,0x24,0x24,0x24,0xE7};
char tassa[17] = {0x3E,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0x24,0x24,0x18};
char top[32] = {0x70,0x8C,0x82,0x81,0x81,0xB1,0xB1,0x81,0x81,0xB1,0xB1,0x81,0x81,0x81,0x99,0xA5,0xA5,0x99,0x81,0x81,0x81,0x91,0x81,0x81,0x91,0x81,0x81,0x81,0x81,0x82,0x8C,0x70};
char surtidor[26] = {0x03,0x07,0x07,0x07,0x07,0x03,0xFF,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x0E,0x12,0x22,0x22,0x22,0x22,0x12,0x0E,0x03};


void writeTxt(byte page, byte y, char * s) {
   int i=0;
   while (*s!='\n' && *s!='\0') 
   {
      putchGLCD(page, y+i, *(s++));
      i++;
   };
}

	

void updateGLCD(){
   char buff[256];
   sprintf(buff,"%02d.%ds\n", segons,decimes);
   writeTxt(6,10,buff);
   __delay_ms(50);
}


void creacio_botons(){
   for (int i = 0; i < 11; ++i){
      writeByte(5,48+i,botodown1[i]);
      writeByte(4,48+i,botodown2[i]);
      writeByte(5,67+i,botoup1[i]);
      writeByte(4,67+i,botoup2[i]);
   }
}


void escriure_percentatge(){
   char percentatge[256];
   sprintf(percentatge,"%03d\n",percentatgenum);
   writeTxt(6,11,percentatge);
   putchGLCD(6, 14, '%');
}


void creacio_barra(){
   for (int i = 0; i < 36; ++i)
      writeByte(7,45+i,barra[i]);
   
   escriure_percentatge();
}


void creacio_tassa(){
   for (int i = 0; i < 6; ++i)
      writeByte(4,60+i,0x07);
      
   for (int i = 0; i < 17; ++i)
      writeByte(3,56+i,tassa[i]);
}


void creacio_surtidor(){
   for (int i = 0; i < 32; ++i)
      writeByte(0,47+i,top[i]);
      
   for (int i = 0; i < 26; ++i)
      writeByte(1,42+i,surtidor[i]);
   
   for (int i = 0; i < 4; ++i)
      SetDot(7,43+i);
}


void contorn(){
   writeByte(6,45,0xFF);
   writeByte(5,45,0xFF);
   writeByte(4,45,0xC0);
   writeByte(6,80,0xFF);
   writeByte(5,80,0xFF);
   writeByte(4,80,0xC0);
   writeByte(4,79,0x30);
   writeByte(4,46,0x30);
   SetDot(35,47);
   SetDot(35,78);
   writeByte(3,48,0xFF);
   writeByte(2,48,0xFF);
   writeByte(3,77,0xFF);
   writeByte(2,77,0xFF);
   writeByte(4,59,0x05);
   writeByte(4,66,0x05);
   writeByte(1,77,0xFF);
}


void estatinicial(){
   clearGLCD(0,0,0,40);
   writeTxt(0,0,stat[0]);
   contorn();
   creacio_barra();
   creacio_botons();
   creacio_tassa();
   creacio_surtidor(); 
}

void animacio_augmentar(){
   for (int i = 0; i < 7; ++i){ //borra 7
      ClearDot(44,69+i);
   }
   __delay_ms(75);
   for (int i = 0; i < 5; ++i){ //borra 5
      ClearDot(43,70+i);
   }
   __delay_ms(75);
   for (int i = 0; i < 7; ++i){ //posa 7
      SetDot(44,69+i);
   }
   __delay_ms(75);
   for (int i = 0; i < 5; ++i){ //borra 5
      ClearDot(42,70+i);
   }
   __delay_ms(75);
   for (int i = 0; i < 5; ++i){	//posa 5
      SetDot(43,70+i);
   }
   __delay_ms(75);
   for (int i = 0; i < 3; ++i){ //borra 3
      ClearDot(41,71+i);
   }
   __delay_ms(75);
   for (int i = 0; i < 5; ++i){	//posa 5
      SetDot(42,70+i);
   }
   __delay_ms(75);
   for (int i = 0; i < 3; ++i){ //borra 3
      ClearDot(40,71+i);
   }
   __delay_ms(75);
   for (int i = 0; i < 3; ++i){ //posa 3
      SetDot(41,71+i);
   }
   __delay_ms(75);
   ClearDot(39,72);		//borra 1
   __delay_ms(75);
   for (int i = 0; i < 3; ++i){	//posa 3
      SetDot(40,71+i);
   }
   __delay_ms(75);
   SetDot(39,72);	//posa 1
}


void animacio_disminuir(){
   for (int i = 0; i < 7; ++i){ //borra 7
      ClearDot(39,50+i);
   }
   __delay_ms(75);
   for (int i = 0; i < 5; ++i){ //borra 5
      ClearDot(40,51+i);
   }
   __delay_ms(75);
   for (int i = 0; i < 7; ++i){ //posa 7
      SetDot(39,50+i);
   }
   __delay_ms(75);
   for (int i = 0; i < 5; ++i){ //borra 5
      ClearDot(41,51+i);
   }
   __delay_ms(75);
   for (int i = 0; i < 5; ++i){	//posa 5
      SetDot(40,51+i);
   }
   __delay_ms(75);
   for (int i = 0; i < 3; ++i){ //borra 3
      ClearDot(42,52+i);
   }
   __delay_ms(75);
   for (int i = 0; i < 5; ++i){	//posa 5
      SetDot(41,51+i);
   }
   __delay_ms(75);
   for (int i = 0; i < 3; ++i){ //borra 3
      ClearDot(43,52+i);
   }
   __delay_ms(75);
   for (int i = 0; i < 3; ++i){ //posa 3
      SetDot(42,52+i);
   }
   __delay_ms(75);
   ClearDot(44,53);		//borra 1
   __delay_ms(75);
   for (int i = 0; i < 3; ++i){	//posa 3
      SetDot(43,52+i);
   }
   __delay_ms(75);
   SetDot(44,53);	//posa 1
}


void augmentar(){
   percentatgenum += 5;
   ++posbarra;
   ++segons;
   SetDot(59,posbarra);
   SetDot(60,posbarra);
   escriure_percentatge();
   animacio_augmentar();
}


void disminuir(){
   percentatgenum -= 5;
   --segons;
   ClearDot(59,posbarra);
   ClearDot(60,posbarra);
   --posbarra;
   escriure_percentatge();
   animacio_disminuir();
}


void actualitzacio(){
   __delay_ms(50);
   if (actualitzar){
      updateGLCD();
      actualitzar = 0;
   }
   __delay_ms(25);
}

void animacio_cafe(){
   while (fentcafe==1){
      SetDot(14,62);	//frame 1
      SetDot(14,63);
      SetDot(15,63);
      writeByte(2,62,0xFC);
      writeByte(2,63,0x87);
      SetDot(24,62);
      SetDot(24,63);
      actualitzacio();
      SetDot(15,62);	//frame 2
      writeByte(2,62,0xF1);
      writeByte(2,63,0x3F);
      ClearDot(24,63);
      actualitzacio();
      ClearDot(14,63);	//frame 3
      ClearDot(15,63);
      writeByte(2,62,0x8F);
      writeByte(2,63,0xFF);
      actualitzacio();
      ClearDot(24,62);	//frame 4
      SetDot(24,63);
      SetDot(14,63);
      writeByte(2,62,0x3F);
      writeByte(2,63,0xFC);
      actualitzacio();
      ClearDot(14,62);	//frame 5
      SetDot(15,63);
      writeByte(2,62,0xFF);
      writeByte(2,63,0xE1);
      actualitzacio();
   }
}

void cafe(){
   clearGLCD(0,0,0,40);
   writeTxt(0,0,stat[1]);
   fentcafe = 1;
   actualitzar = 1;
   TMR0ON = 1;
   animacio_cafe();
}

void animacio_acabat(){
   char i = 4;
   SetDot(15,61);
   writeByte(2,61,0xE3);
   SetDot(15,64);
   writeByte(2,64,0xE3);
   
   while (i){
      writeByte(2,60,0x1C);
      writeByte(2,63,0x1C);
      __delay_ms(750);
      clearGLCD(2,2,60,60);
      clearGLCD(2,2,63,63);
      
      writeByte(2,65,0x1C);
      writeByte(2,62,0x1C);
      __delay_ms(750);
      clearGLCD(2,2,65,65);
      clearGLCD(2,2,62,62);
      --i;
   }
}

void acaba(){
   ClearDot(14,62);
   ClearDot(15,62);
   ClearDot(24,62);
   ClearDot(14,63);
   ClearDot(15,63);
   ClearDot(24,63);
   clearGLCD(2,2,62,64);
   actualitzar = 0;
   final = 0;
   TMR0ON = 0;
   TMR0 = 15536;
   percentatgenum = 50;
   posbarra = 62;
   segons = 15;
   decimes = 0;
   clearGLCD(6,7,46,78);
   creacio_barra();
   clearGLCD(0,0,0,40);
   writeTxt(0,0,stat[2]);
   animacio_acabat();
   ClearDot(15,61);
   ClearDot(15,64);
   clearGLCD(2,2,60,65);
   clearGLCD(0,0,0,40);
   writeTxt(0,0,stat[0]);
}
