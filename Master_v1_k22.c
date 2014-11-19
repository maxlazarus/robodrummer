/*
        Master drum controller
        Written for PIC18f26k22 using microC PRO v.6.0.0
        Jan 04, 2014        
        max.prokopenko@gmail.com
*/
#include "TLC5940_functions.h" // uses PORTA.B0-B4
#include "sevSeg_4_digit.h" // uses PORTB.B2-B5
#include "universal.h" 
#include "light_matrix.h"
#include "characters.h"

typedef struct colour{
	unsigned short red;
	unsigned short green;
	unsigned short blue;
};

volatile signed short state, MIDI_state;
volatile unsigned int blinkcount, sixteenthcount, tempo;
volatile unsigned short hex_out[3];
volatile unsigned short this_MIDI_note, this_MIDI_vel;
signed short current_step, selected_step, channel;
unsigned short i, j, k, red, green, blue, temp; // iterators and temp colour
unsigned short blink;
unsigned short this_rot_0, last_rot_0;
unsigned short this_rot_1, last_rot_1;
unsigned short switch_0_flag;
unsigned short direction;
unsigned short current_status;
unsigned int moving_mask = 0; // for displaying hex
code struct colour colour_red = { BRIGHTNESS, 0, 0 };
code struct colour colour_green = { 0, BRIGHTNESS, 0 };
code struct colour colour_blue= { 0, 0, BRIGHTNESS };

void interrupt ();
void init();
void init_timer();
signed short check_rotary(unsigned int this_rot, unsigned int last_rot);
void init_rot();
void push_light_matrix(unsigned short matrix[][], unsigned short selection);
void draw_char(
	unsigned char c, 
	unsigned short offset, 
    unsigned short red, 
	unsigned short green, 
	unsigned short blue
);
void clear_pattern();
void show_message(unsigned char message[], struct colour message_colour);

unsigned short pattern[CHANNELS][STEPS] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0}
};

void main() {
        
    // TLC5940 dependent // init_5940();
    init_7_seg_4_digit();        
    init_rot();
    init_timer();
        init();

        TRISA.B0 = bit_out; // testing light matrix

        /* TLC5940 dependent
                                
    for(i = 0; i < STEPS; i++){
            change(sData, i, pattern[channel][i]);
    }

    sendData(sData, bitcount);  
        */

    INTCON2 = 0x04; 
	GIEH_bit = 1;
	GIEL_bit = 1;
    T0IE_bit = 1; // RE-ENABLE AFTER TESTING MIDI!
    TMR0ON_bit = 1; // clocks every 10us
	RC2IE_bit = 0; // MIDI receive interrupt

        drum_0 = 0;
        drum_1 = 0;   
        drum_2 = 0;
        drum_3 = 0;

        delay_ms(100);

        // init display
        push_light_matrix(pattern, channel);
        show_light_matrix();        

	state = FORWARD;

        // main loop
    while(1){
        
        if(switch_up == 0) state = FORWARD;
        else if(switch_down == 0) state = BACKWARD;
        else {
                state = STOPPED;
                        current_step = 0;
                }

		if(MIDI_state == MIDI_RECEIVED){
			pattern[0][this_MIDI_note - 0x24] = (~pattern[0][this_MIDI_note - 0x24] & 1);
			MIDI_state = IDLE;
			update_light_matrix( channel, selected_step, BRIGHTNESS, 0, 0);
		}
        
        // flip the pattern's selected_step with switch_0
        if ((switch_0 == _set) && (switch_0_flag != _set)) {
                pattern[channel][selected_step] = (~pattern[channel][selected_step] & _set);
                                update_light_matrix( channel, selected_step, BRIGHTNESS, 0, 0 );
                switch_0_flag = _set;
        }
        else if (switch_0 == _clr) {
                switch_0_flag = _clr;
        }

        // advance or retreat one step if running
        if (sixteenthcount >= (MS_BPM / tempo) && state != STOPPED) {
            sixteenthcount = 0;
                        drum_0 = pattern[0][current_step];
                        drum_1 = pattern[1][current_step];
                        drum_2 = pattern[2][current_step];
                        drum_3 = pattern[3][current_step];
              
       
                    current_step += state; // forward or backwards
            if(current_step <= -1){current_step = 15;}
                else if(current_step >= 16){current_step = 0;}
        }

        if (state != STOPPED) send_7seg(to_bcd(current_step * 100 + selected_step));
                else send_7seg(to_bcd(tempo));

                // turns off all outputs after uh, whatever that time is?
        if (sixteenthcount >= ((MS_BPM / tempo) / 4)) {
                drum_0 = off;
                drum_1 = off;
                drum_2 = off;
                drum_3= off;
        }   

                // shows blinking cursor
                current_status = pattern[channel][selected_step];
        if (blinkcount >= (BLINK_TIME /*>> (current_status * 2)*/)){
            blinkcount = 0;
            blink = ~blink;
            
                        push_light_matrix(pattern, channel);

            if(blink == 0) update_light_matrix(channel, selected_step, current_status * BRIGHTNESS, 0, 0);
            else update_light_matrix(channel, selected_step, 0, 0, BRIGHTNESS);

                        show_light_matrix();
        }
 
        // rotary left controls selected step
        last_rot_0 = this_rot_0;           
        this_rot_0 = (rot_0b << 1) | rot_0a;  
        selected_step += check_rotary(this_rot_0, last_rot_0);
        if(selected_step <= -1){selected_step = 15;}
        else if(selected_step >= 16){selected_step = 0;}
        
        // rotary right adjusts channel if running, tempo if stopped
        if(state != STOPPED){
            last_rot_1 = this_rot_1;           
            this_rot_1 = (rot_1a << 1) | rot_1b;  
            channel += check_rotary(this_rot_1, last_rot_1);
            if(channel <= -1){channel = 0;}
                        else if(channel >= 5){channel = 4;}
                }else{
            last_rot_1 = this_rot_1;           
            this_rot_1 = (rot_1a << 1) | rot_1b;  
            tempo += check_rotary(this_rot_1, last_rot_1);
            if(tempo <= 9){tempo = 10;}
                else if(tempo >= 251){tempo = 250;}                    
                }
        
        // TLC 5940 dep //sendData(sData, bitcount);
        // TLC 5940 dep //gsClock();
    }
}

signed short check_rotary(unsigned int this_rot, unsigned int last_rot){

    if(this_rot != last_rot){
        
        if(last_rot == 0 && this_rot == 2){return -1;}
        else if(last_rot == 2 && this_rot == 3){return -1;}
        else if(last_rot == 3 && this_rot == 1){return -1;}
        else if(last_rot == 1 && this_rot == 0){return -1;}
        else if(last_rot == 0 && this_rot == 1){return 1;}
        else if(last_rot == 1 && this_rot == 3){return 1;}
        else if(last_rot == 3 && this_rot == 2){return 1;}
        else if(last_rot == 2 && this_rot == 0){return 1;}
        }
        
        return 0;
}

void init_rot() {

    rot_0a_dir = bit_in;
    rot_0b_dir = bit_in;
    rot_1a_dir = bit_in;
    rot_1b_dir = bit_in;
}

void init_timer() {

    TMR0L = ONE_MS_COUNT % 0x100;
    TMR0H = ONE_MS_COUNT / 0x100;
    T0CON = 0; // no prescaler value
    PSA_bit = _set; // prescaler unassigned
    T08BIT_bit = _clr; // 16-bit mode
    T0CS_bit = _clr; // internal clock selected
}

void init() {

    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;

    state = STOPPED;

    switch_0_dir = bit_in;
    switch_up_dir = bit_in;
    switch_down_dir = bit_in;

    drum_0_dir = bit_out;
    drum_1_dir = bit_out;
    drum_2_dir = bit_out;
    
    blinkcount = 0;
    sixteenthcount = 0;
    tempo = INIT_BPM;
    current_step = 0;
    selected_step = 0;
    i = 0;
    blink = off;
    this_rot_0 = 0;
    last_rot_0 = 0;
    this_rot_1 = 0;
    last_rot_1 = 0;
    switch_0_flag = _clr;
    channel = 0;

	//UART
	TRISB.B6 = bit_out;
	TRISB.B7 = bit_in;
    CREN2_bit = 1;
	SYNC2_bit = 0;
	SPEN2_bit = 1;
	BRGH2_bit = 0;
	BAUDCON2.B3 = 0;// BRG16
	SPBRG2 = BAUDRATE; 
	RX2_bit = 1;
	DT2_bit = 1;
}

void interrupt () {

	if(T0IF_bit){
    	TMR0L = ONE_MS_COUNT % 0x100;
    	TMR0H = ONE_MS_COUNT / 0x100;        
    	TMR0IF_bit = _clr;

    	blinkcount++;
     	 sixteenthcount++;
	}
	if(RC2IF_bit){
		RC2IE_bit = 0;	
		hex_out[2] = hex_out[1];
		hex_out[1] = hex_out[0];
  		hex_out[0] = RCREG2;
		if(hex_out[2] == 0x90){
			MIDI_state = MIDI_RECEIVED;
			this_MIDI_note = hex_out[1];
			this_MIDI_vel = hex_out[0];
		}
		CREN2_bit = 0;
		CREN2_bit = 1;		
		RC2IE_bit = 1;
	}
}

// updates the light matrix with a copy of the argument matrix
// passed selected channel is red, others green
// global current step is brightened
void push_light_matrix(unsigned short matrix[CHANNELS][STEPS], unsigned short selection) {
        
    int red, green, blue = 0;
    int i, j, highlight;
    
    for( i = 0; i < CHANNELS; i++ ){
        for( j = 0; j < STEPS; j++ ){
                if( j == current_step )
                                highlight = HIGHLIGHT;        
                        else
                                highlight = 1;                                        

            if( i == selection){
                    red = matrix[i][j] * BRIGHTNESS * highlight;
                    green = 0;
            }
            else {
                    green = matrix[i][j] * BRIGHTNESS * highlight;
                    red = 0;
            }
            update_light_matrix( i, j, red, green, blue );                
        }
    }        
}

void draw_char(
	unsigned char c, 
	unsigned short offset, 
	unsigned short red, 
	unsigned short green, 
	unsigned short blue
){

	unsigned short n = c - 0x40;
    int i, j;

	offset *= 4;
	offset %= STEPS - WIDTH;

	if(n > NUMCHARS - 1)
		n = 0;
    
    for( i = 0; i < HEIGHT; i++ ){
        for( j = 0; j < WIDTH; j++ ){
            if(character[n][i][j])
                update_light_matrix( i, j + offset, red, green, blue );       
            else
                update_light_matrix( i, j + offset, 0, 0, 0 );                                                   
        }
    }    
}

void clear_pattern(){

    int i, j;
    
    for( i = 0; i < CHANNELS; i++ ){
        for( j = 0; j < STEPS; j++ ){
            pattern[i][j] = 0;                                                         
        }
    }  	
}

void show_message(unsigned char message[], struct colour msg_colour){
	
	int i = 0;
	
	for(i = 0; i < (STEPS / (WIDTH + 1)); i++){
		draw_char(
			message[i], 
			i ,
			msg_colour.red, 
			msg_colour.green, 
			msg_colour.blue);
	}
}