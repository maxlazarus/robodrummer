/*
	Written for PIC18f26k22 using microC PRO v.6.0.0
	Jan 04, 2014	
	max.prokopenko@gmail.com
*/

#ifndef SEVSEG_4_DIGIT_H
#define SEVSEG_4_DIGIT_H

#define SER PORTB.B5
#define nOE PORTB.B4
#define RCLK PORTB.B3
#define SRCLK PORTB.B2
#define SER_dir TRISB.B5
#define nOE_dir TRISB.B4
#define RCLK_dir TRISB.B3
#define SRCLK_dir TRISB.B2

void init_7_seg_4_digit();
void pulse_SRCLK();
void pulse_RCLK();
void send_7seg(unsigned int val);
unsigned int to_BCD(unsigned int val);

#endif