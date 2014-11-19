/*
        Set of functions for RGB matrix
        Written for PIC18f26k22 using microC PRO v.6.0.0
        April 23rd, 2014        
        max.prokopenko@gmail.com
*/

#include "light_matrix.h"
#include "universal.h"

unsigned short light_matrix[CHANNELS * STEPS * 3];
unsigned int hex[CHANNELS];

void send_one () {
            
            DOUT = 1;
        asm { 
                nop 
        nop 
        nop 
        nop 
        nop }   
        asm { 
                nop 
        nop }                
        
        DOUT = 0;
        asm { 
                nop 
        nop }
}

void send_zero () {
            
            DOUT = 1;
        asm { nop }       
        
            DOUT = 0;
        asm { 
                nop 
        nop 
        nop 
        nop 
        nop }
        asm {
        nop 
        nop 
        nop }            
}

void send_colour(unsigned short C){

        if( C & 0x80 ) send_one(); else send_zero();
        if( C & 0x40 ) send_one(); else send_zero();
        if( C & 0x20 ) send_one(); else send_zero();
        if( C & 0x10 ) send_one(); else send_zero();
        if( C & 0x08 ) send_one(); else send_zero();
        if( C & 0x04 ) send_one(); else send_zero();
        if( C & 0x02 ) send_one(); else send_zero();
        if( C & 0x01 ) send_one(); else send_zero();
}

void update_light_matrix(unsigned short i, 
                                                unsigned short j,
                                                unsigned short R,
                                                unsigned short G,
                                                unsigned short B){
        int l_chan = 0;
        l_chan = CHANNELS - i - 1;

        if( i % 2 ){
                light_matrix[(l_chan * STEPS) + STEPS - j - 1] = G;
                light_matrix[(CHANNELS * STEPS) + (l_chan * STEPS) + STEPS - j - 1] = R;
                light_matrix[(2 * CHANNELS * STEPS) + (l_chan * STEPS) + STEPS - j - 1] = B;
        } else {
                light_matrix[(l_chan * STEPS) + j] = G;
                light_matrix[(CHANNELS * STEPS) + (l_chan * STEPS) + j] = R;
                light_matrix[(2 * CHANNELS * STEPS) + (l_chan * STEPS) + j] = B;        
        }                        
}

void show_light_matrix() {

    int i;      

	
	TMR0ON_bit = 0;

    for( i = 0; i < (CHANNELS * STEPS); i++ ){
            send_colour( light_matrix[i] );
            send_colour( light_matrix[i + (CHANNELS * STEPS)] );
            send_colour( light_matrix[i + (2 * CHANNELS * STEPS)] );
    }
    TMR0ON_bit = 1;

    DOUT = 0;
}

// hexbump displays a stack of hex values
// each one sent shifts the last value down the stack
void hexbump_light_matrix(unsigned int value){
	
	int i = 0, j = 0, R = 0, G = 0, B = 0;
	unsigned int temp = 0, moving_mask = 0;
	
    for(j = CHANNELS - 1; j > 0; j--){
		hex[j] = hex[j-1];
    }
	
	hex[0] = value;

	for(j = 0; j < CHANNELS; j++){

		for(i = 0, moving_mask = 0x8000; i < STEPS; i++){

		    if((hex[j] & moving_mask) > 0)
				temp = BRIGHTNESS;
	    	else
				temp = 0;
			
			if(i < 8)
			{
				R = temp;
				G = 0;
			}
			else
			{
				R = 0;
				G = temp;
			}

			moving_mask /= 2;

			update_light_matrix( j, i, R, G, B );
		}
	}
}