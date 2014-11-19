/*
        Written for PIC18f26k22 using microC PRO v.6.0.0
        Jan 04, 2014        
        max.prokopenko@gmail.com
*/

#ifndef TLC5940_FUNCTIONS_H
#define TLC5940_FUNCTIONS_H

#define grayCount 1024
#define bitcount 192
#define dtime 2
#define numLEDS 16
#define bitDepth 12
#define XLAT PORTA.B0
#define SCLK PORTA.B2
#define SOUT PORTA.B4
#define GSCLK PORTA.B1
#define BLANK PORTA.B3
#define XLAT_dir TRISA.B0
#define SCLK_dir TRISA.B2
#define SOUT_dir TRISA.B4
#define GSCLK_dir TRISA.B1
#define BLANK_dir TRISA.B3

//some bit stuff for addressing LEDS

#define bit15 191
#define bit14 191-12
#define bit13 191-24
#define bit12 191-36
#define bit11 191-48
#define bit10 191-60
#define bit9 191-72
#define bit8 191-84
#define bit7 191-96
#define bit6 191-108
#define bit5 191-120
#define bit4 191-132
#define bit3 191-144
#define bit2 191-156
#define bit1 191-168
#define bit0 191-180

extern unsigned short sData[bitcount];

void init_5940();
void gsClock();
void change(unsigned short matrix[], unsigned short changebit, unsigned short value);
void flip(unsigned short matrix[], unsigned short changebit);
void changeall(unsigned short matrix[], unsigned short value);
void sendData(unsigned short matrix[], unsigned short length);

#endif