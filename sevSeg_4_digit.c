/*
        Set of functions for 4 digit mis-wired 7 segment LED display
        Written for PIC18f26k22 using microC PRO v.6.0.0
        Jan 04, 2014        
        max.prokopenko@gmail.com
*/

#include "sevSeg_4_digit.h"
#include "universal.h"

// dec to 7seg decoding array
unsigned short sev[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x67, 0x77, 0x7c, 0x58, 0x5e, 0x79, 0x71};

void init_7_seg_4_digit() {
    SER_dir = bit_out;
    nOE_dir = bit_out;
    RCLK_dir = bit_out;
    SRCLK_dir = bit_out;
        nOE = 0;
}

void pulse_SRCLK() {
        SRCLK = 0;
        SRCLK = 1;
        SRCLK = 0;
}

void pulse_RCLK() {
        RCLK = 0;
        RCLK = 1;
        RCLK = 0;
}

void send_7seg(unsigned int val) {

    unsigned int buffer = sev[(val >> 4) & 0xf] | (sev[val & 0xf] << 8);
    unsigned short count = 16;
    
    while(count-- > 0){
        SER = (0x8000 & buffer) >> 15;
        buffer = buffer << 1;
        pulse_SRCLK();
    }

    buffer = sev[(val >> 8) & 0xf] | (sev[(val >> 12) & 0xf] << 8);
        count = 16;
    
    while(count-- > 0){
        SER = (0x8000 & buffer) >> 15;
        buffer = buffer << 1;
        pulse_SRCLK();
    }

    pulse_RCLK();
}

unsigned int to_BCD(unsigned int val) {
    
	val = 0xffff & (val % 10 | (((val / 10) % 10) << 4) | (((val / 100) % 10) << 8) | (((val / 1000) % 10) << 12));     
    return val;
}