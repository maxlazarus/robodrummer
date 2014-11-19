#define grayCount 1024
#define bitcount 192
#define dtime 2
#define numLEDS 16
#define bitDepth 12
#define XLAT PORTA.B1
#define SCLK PORTA.B2
#define SOUT PORTA.B0
#define GSCLK PORTA.B3
#define BLANK PORTA.B4
#define down 0
#define up 1
#define _set 1
#define _clr 0

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

void interrupt(void){

         char in;

     INT1E_BIT = 0;


     //TXREG1 = 0x01;

     RBIE_bit = 0;


     PORTA = ~PORTA;

     delay_us(45);

     in = PORTB.B1*0x01 | in;

     delay_us(30);

     in = PORTB.B1*0x02 | in;

     delay_us(30);

     in = PORTB.B1*0x04 | in;

     delay_us(30);

     in = PORTB.B1*0x08 | in;

     delay_us(30);

     in = PORTB.B1*0x10 | in;

     delay_us(30);

     in = PORTB.B1*0x20 | in;

     delay_us(30);

     in = PORTB.B1*0x40 | in;

     delay_us(30);

     in = PORTB.B1*0x80 | in;

     TXREG1 = in;

     delay_us(200);

     RBIF_bit = 0;

     RBIE_bit = 0;

     INT1F_BIT = 0;
     INT1E_BIT = 1;
}

void setData() {}

volatile unsigned int gcount = grayCount;

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

unsigned short bitaddress[16] = {
         bit15,bit14,bit13,bit12,bit11,bit10,bit9,bit8,
         bit7,bit6,bit5,bit4,bit3,bit2,bit1,bit0
     };

int change(unsigned short matrix[], unsigned short changebit, unsigned short value){

     int x = bitaddress[changebit];
     while(x >= bitaddress[changebit] - bitDepth){

                x--; matrix[x] = value;
     }
}

int changeall(unsigned short matrix[], unsigned short value){

     int x = bitcount - 1;
     while(x >= 0){

                x--; matrix[x] = value;
     }
}

int sendData(unsigned short matrix[], unsigned short length){

              unsigned short count = length;

              while(count != 0){

                  SOUT = matrix[length - count];

                  SCLK = 0;
                  SCLK = 1;

                  count--;
              }
}

void txwait(){while(RC1IF_bit == 0){delay_us(1);}}

void main() {

unsigned short sData[bitcount] = {
0,0,0,0,0,0,0,0,0,0,1,1, // Channel 15
0,0,0,0,0,0,0,0,0,1,1,0, // Channel 14
0,0,0,0,0,0,0,0,1,1,0,0, // Channel 13
0,0,0,0,0,0,0,0,1,1,0,0, // Channel 12
0,0,0,0,0,0,0,1,1,0,0,0, // Channel 11
0,0,0,0,0,0,1,1,0,0,0,0, // Channel 10
0,0,0,0,0,0,1,1,0,0,0,0, // Channel 9
0,0,0,0,0,1,1,0,0,0,0,0, // Channel 8
0,0,0,0,1,1,0,0,0,0,0,0, // Channel 7
0,0,0,0,1,1,0,0,0,0,0,0, // Channel 6
0,0,0,1,1,0,0,0,0,0,0,0, // Channel 5
0,0,1,1,0,0,0,0,0,0,0,0, // Channel 4
0,0,1,1,0,0,0,0,0,0,0,0, // Channel 3
1,0,0,0,0,0,0,0,0,0,0,0, // Channel 2
1,1,0,0,0,0,0,0,0,0,0,0, // Channel 1
1,1,0,0,0,0,0,0,0,0,0,0, // Channel 0
};

    short direction = down;

    unsigned int slowcount = 0;
    unsigned int slowercount = 0;
    unsigned char countup = 0;

    ANSELA = 0;
    TRISA = 0;
    PORTA = 0;

    ANSELB = 0;

    TRISB = 0x02;

    //SOUT = 1;

    TXEN1_bit = 1;
    SYNC1_bit = 0;
    SPEN1_bit = 1;
    
    IPEN_bit = 0;//interrupt priority enabled
    GIEH_bit = 0;
    GIEL_bit = 0;


    INTEDG1_BIT = 0;
    INT1IP_BIT = 1;
    INT1IE_BIT = 1;


    RC1IE_bit = 0; //rx int enable
    RC1IP_bit = 1; //high priority
    RBIE_bit = 0; //port b int on change
    RBIP_bit = 1; //high priority
    IOCB = 0x20;

    ANSELC = 0;
    TRISC6_bit = 0; //pin 17 tx
    TRISC7_bit = 1; //pin 18 rx

    TXREG1 = 0x00;

    TX9_bit = 0;

    RX9_bit = 0;
    ADCON1 = 0xff;
    BAUDCON1.B3 = 0; //8-bit
    //BAUDCON1.B4 = 0;
    BAUDCON1.B5 = 0;


    SPBRGH = 0;
    SPBRG = 24; // 6 for 31250 KHz op?  24?  WTF

    PORTA = 0;

    //while(1){delay_us(100);porta=~porta;}

    while(1){

        porta=~porta;

        delay_us(2);

    }

    while(1){


        slowcount++;

        //porta.b0 = rc1if_bit;

        if(slowcount % 256 == 0){

            slowercount++;
        }

        if(slowercount % 256 == 0){

            //spbrg++;

        }

        //spbrg++;

        PORTA = ~porta;

        CREN_bit = 1;

        countup++;

        TXREG1 = countup;//slowcount;

        delay_ms(200);

        //asm nop;

        //while(tx1if == 0){};
         //test for frequency to check spbrg

        //txwait(); //<-THIS IS WHAT YOU WANT TO WORK

        if(RCREG1 == 0x90){

                txwait();

                PORTA = ~PORTA;
        }

                //PORTB = 0; PORTD = 0;
                CREN_bit = 0;
    }

     while(1){

              slowcount++;

              if(slowcount % 128 == 0){

                   if(direction == down){

                       change(sData, 5, _clr);
                       direction = up;
                       changeall(sData, _clr);
                   }
                   else{

                        change(sData, 5, _set);
                        changeall(sData, _set);
                        direction = down;
                   }
              }

              sendData(sData, bitcount);

              gcount = grayCount;

              while(gcount != 0){

                  GSCLK = 1;
                  GSCLK = 0;

                  gcount--;
              }

              XLAT = 1;
              XLAT = 0;

              BLANK = 1;
              BLANK = 0;

     }
}