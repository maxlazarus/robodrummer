/*
        Universal definitions for master_controller project
        Written using microC PRO v.6.0.0
        Jan 04, 2014        
        max.prokopenko@gmail.com
*/

#ifndef UNIVERSAL_H
#define UNIVERSAL_H

#define STEPS 16
#define CHANNELS 5 // leave last channel blank because of LED14/15 issues - overflow?
#define BRIGHTNESS 60
#define HIGHLIGHT 3

#define BLINK_TIME 50

// weird stuff going on with timing, crystal used is 40Mhz
// acting like a ~13Mhz crystal, below compensates using 4xPLL
// should be accurate to within +/-.1% or so
#define CRYSTAL 52800000
#define T_DIVIDE 4
#define ONE_MS_COUNT (0xffff - (CRYSTAL/(1000*T_DIVIDE)))
#define TEMPO_DIV 

// MIDI UART
#define BAUDRATE 25

// state
#define STOPPED 0
#define FORWARD 1
#define BACKWARD -1

#define MIDI_RECEIVED 1
#define IDLE 0

// timer0
#define PRESCALE_256 0x7
#define PRESCALE_128 0x6
#define PRESCALE_64 0x5
#define PRESCALE_32 0x4
#define PRESCALE_16 0x3
#define PRESCALE_8 0x2
#define PRESCALE_4 0x1
#define PRESCALE_2 0x0

// rotary controls
#define rot_0a PORTB.B0 // pin 21
#define rot_0b PORTB.B1 // pin 22
#define rot_0a_dir TRISB.B0
#define rot_0b_dir TRISB.B1
#define rot_1a PORTC.B2 // pin 13
#define rot_1b PORTC.B3 // pin 14
#define rot_1a_dir TRISC.B2
#define rot_1b_dir TRISC.B3

// switch 
#define switch_0 PORTC.B1 // pin 12
#define switch_0_dir TRISC.B1
#define switch_up PORTA.B5 // pin 7
#define switch_up_dir TRISA.B5
#define switch_down PORTC.B0 // pin 11
#define switch_down_dir TRISC.B0

// drum output
#define drum_0 PORTC.B4 // pin 15
#define drum_1 PORTC.B5 // pin 16
#define drum_2 PORTC.B6 // pin 17
#define drum_3 PORTC.B7 // pin 18
#define drum_0_dir TRISC.B4
#define drum_1_dir TRISC.B5
#define drum_2_dir TRISC.B6
#define drum_3_dir TRISC.B7

// additional misc defines
#define SLOW_BLINK 2
#define FAST_BLINK 3
#define MS_BPM 15000
#define INIT_BPM 100
#define DOWN 0
#define UP 1
#define down 0
#define up 1
#define off 0
#define on 1
#define _set 1
#define _clr 0
#define bit_out 0
#define bit_in 1
#define byte_out 0
#define byte_in 0xff

#endif