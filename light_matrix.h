/*
        Written for PIC18f26k22 using microC PRO v.6.0.0
        April 23rd, 2014        
        max.prokopenko@gmail.com
*/

#ifndef LIGHT_MATRIX_H
#define LIGHT_MATRIX_H

#define DOUT PORTA.B0 // pin 2
#define NUMLIGHTS 80

void send_zero();
void send_one();
void send_colour(unsigned short C);
void update_light_matrix(unsigned short i, 
                                                unsigned short j,
                                                unsigned short R,
                                                unsigned short G,
                                                unsigned short B);
void show_light_matrix();
void hexbump_light_matrix(unsigned int value);

#endif