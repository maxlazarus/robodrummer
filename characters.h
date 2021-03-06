/*
        Character definitions for master_controller project
        Written using microC PRO v.6.0.0
        May 18th, 2014        
        max.prokopenko@gmail.com
*/

#ifndef CHARACTERS_H
#define CHARACTERS_H

#define NUMCHARS 27
#define HEIGHT 5
#define WIDTH 3

code unsigned short character[NUMCHARS][HEIGHT][WIDTH] = 
{
{//space
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0}
},
{//A
  {0,1,0},
  {1,0,1},
  {1,1,1},
  {1,0,1},
  {1,0,1}
},
{//B
  {1,1,0},
  {1,0,1},
  {1,1,0},
  {1,0,1},
  {1,1,0}
},
{//C
  {0,1,0},
  {1,0,1},
  {1,0,0},
  {1,0,1},
  {0,1,0}
},
{//D
  {1,1,0},
  {1,0,1},
  {1,0,1},
  {1,0,1},
  {1,1,0}
},
{//E
  {1,1,1},
  {1,0,0},
  {1,1,0},
  {1,0,0},
  {1,1,1}
},
{//F
  {1,1,1},
  {1,0,0},
  {1,1,0},
  {1,0,0},
  {1,0,0}
},
{//G
  {0,1,0},
  {1,0,1},
  {1,0,0},
  {1,0,1},
  {0,1,1}
},
{//H
  {1,0,1},
  {1,0,1},
  {1,1,1},
  {1,0,1},
  {1,0,1}
},
{//I
  {1,1,1},
  {0,1,0},
  {0,1,0},
  {0,1,0},
  {1,1,1}
},
{//J
  {0,0,1},
  {0,0,1},
  {0,0,1},
  {1,0,1},
  {0,1,0}
},
{//K
  {1,0,1},
  {1,1,0},
  {1,1,0},
  {1,1,0},
  {1,0,1}
},
{//L
  {1,0,0},
  {1,0,0},
  {1,0,0},
  {1,0,0},
  {1,1,1}
},
{//M
  {1,0,1},
  {1,1,1},
  {1,0,1},
  {1,0,1},
  {1,0,1}
},
{//N
  {1,1,0},
  {1,0,1},
  {1,0,1},
  {1,0,1},
  {1,0,1}
},
{//O
  {0,1,0},
  {1,0,1},
  {1,0,1},
  {1,0,1},
  {0,1,0}
},
{//P
  {1,1,0},
  {1,0,1},
  {1,1,0},
  {1,0,0},
  {1,0,0}
},
{//Q
  {0,1,0},
  {1,0,1},
  {1,0,1},
  {0,1,0},
  {0,0,1}
},
{//R
  {1,1,0},
  {1,0,1},
  {1,1,0},
  {1,0,1},
  {1,0,1}
},
{//S
  {1,0,1},
  {1,0,1},
  {1,1,1},
  {1,0,1},
  {1,0,1}
},
{//T
  {1,1,1},
  {0,1,0},
  {0,1,0},
  {0,1,0},
  {0,1,0}
},
{//U
  {1,0,1},
  {1,0,1},
  {1,0,1},
  {1,0,1},
  {1,1,1}
},
{//v
  {1,0,1},
  {1,0,1},
  {1,0,1},
  {1,0,1},
  {0,1,0}
},
{//W
  {1,0,1},
  {1,0,1},
  {1,0,1},
  {1,1,1},
  {1,0,1}
},
{//X
  {1,0,1},
  {1,0,1},
  {0,1,0},
  {1,0,1},
  {1,0,1}
},
{//Y
  {1,0,1},
  {1,0,1},
  {1,0,1},
  {0,1,0},
  {1,0,0}
},
{//Z
  {1,1,1},
  {0,0,1},
  {0,1,0},
  {1,0,0},
  {1,1,1}
},
};

code unsigned short charA[5][3] = {
    {0,1,0},
    {1,0,1},
    {1,1,1},
    {1,0,1},
    {1,0,1}
};

code unsigned short charB[5][3] = {
    {1,1,0},
    {1,0,1},
    {1,1,0},
    {1,0,1},
    {1,1,0}
};

code unsigned short charC[5][3] = {
    {0,1,0},
    {1,0,1},
    {1,0,0},
    {1,0,1},
    {0,1,0}
};

code unsigned short charD[5][3] = {
    {1,1,0},
    {1,0,1},
    {1,1,1},
    {1,0,1},
    {1,1,0}
};

code unsigned short charE[5][3] = {
    {1,1,1},
    {1,0,0},
    {1,1,0},
    {1,0,0},
    {1,1,1}
};

code unsigned short charF[5][3] = {
    {1,1,1},
    {1,0,0},
    {1,1,0},
    {1,0,0},
    {1,0,0}
};

#endif