/*
        Set of functions for TLC5940 IC
        Written for PIC18f26k22 using microC PRO v.6.0.0
        Jan 04, 2014        
        max.prokopenko@gmail.com
*/

#include "TLC5940_functions.h"
#include "universal.h"

volatile unsigned int gcount = grayCount;

unsigned short bitaddress[16] = {
    bit15,bit14,bit13,bit12,bit11,bit10,bit9,bit8,
    bit7,bit6,bit5,bit4,bit3,bit2,bit1,bit0
};

//inits 16-LED array of 10-bit intensity in a test pattern
unsigned short sData[bitcount] = {
    0,0,0,0,0,0,0,0,0,0,0,0, // Channel 15
    0,0,0,0,0,0,0,0,0,0,0,0, // Channel 14
    0,0,0,0,0,0,0,0,0,0,0,0, // Channel 13
    0,0,0,0,0,0,0,0,0,0,0,0, // Channel 12
    0,0,0,0,0,0,0,0,0,0,0,0, // Channel 11
    0,0,0,0,0,0,0,0,0,0,0,0, // Channel 10
    0,0,0,0,0,0,0,0,0,0,0,0, // Channel 9
    0,0,0,0,0,0,0,0,0,0,0,0, // Channel 8
    0,0,0,0,0,0,0,0,0,0,0,0, // Channel 7
    0,0,0,0,0,0,0,0,0,0,0,0, // Channel 6
    0,0,0,0,0,0,0,0,0,0,0,0, // Channel 5
    0,0,0,0,0,0,0,0,0,0,0,0, // Channel 4
    0,0,0,0,0,0,0,0,0,0,0,0, // Channel 3
    0,0,0,0,0,0,0,0,0,0,0,0, // Channel 2
    0,0,0,0,0,0,0,0,0,0,0,0, // Channel 1
    0,0,0,0,0,0,0,0,0,0,0,0, // Channel 0
};

void init_5940() {

    XLAT_dir = bit_out;
    SCLK_dir = bit_out;
    SOUT_dir = bit_out;
    GSCLK_dir = bit_out;
    BLANK_dir = bit_out;
}
		
void gsClock() {
    
    while(gcount != 0){
        GSCLK = 1;
        GSCLK = 0;
        gcount--;
    }
    gcount = grayCount;
    XLAT = 1;
    XLAT = 0;
    BLANK = 1;
    BLANK = 0;
}

void change(unsigned short matrix[], unsigned short changebit, unsigned short value){

     int x = bitaddress[changebit];

     while(x >= bitaddress[changebit] - bitDepth){
         x--; matrix[x] = value;
     }
}

void flip(unsigned short matrix[], unsigned short changebit){

    int x = bitaddress[changebit];
    
    while(x >= bitaddress[changebit] - bitDepth){
        x--; 
                if (matrix[x] == _set) {
                matrix[x] = _clr;
        }
        else {
                matrix[x] = _set;
        }
    }
}

void changeall(unsigned short matrix[], unsigned short value){

     int x = bitcount - 1;

     while(x >= 0){
               x--; matrix[x] = value;
     }
}

void sendData(unsigned short matrix[], unsigned short length){

    unsigned short count = length;
    
    while(count != 0){
      SOUT = matrix[length - count];
      SCLK = 0;
      SCLK = 1;
      count--;
    }
}