/*
 * tic55.c
 *
 * TIC55 LCD library for MSP430 (source)
 * 
 *  Created on: 05.07.2013
 *      @author: techncreo
 * 	Based on source from http://radiokot.ru/circuit/digital/home/52/
 * 
 * 	techncreo.blogspot.com
 */

#include <tic55.h>
#include <delay.h>

                  
unsigned int Buffer[8] = {0,0,0,0,0,0,0,0}; // ����� ����������


/*     ������� ��������     */
unsigned int code[] = 
{ 
   444,     //  0 
   12,      //  1 
   472,     //  2 
   348,     //  3 
   108,     //  4 
   372,     //  5 
   500,     //  6 
   28,      //  7 
   508,     //  8 
   380,     //  9 
   0,       //  10 blank 
   //252,     //  A     
   //484,     //  b
   //448,     //  c
   //460,     //  d
   496,     //  E
   //240,     //  F
   //436,     //  G
   //432,     //  C
   120,     //  "*" ������
   //192,     //  r 
   //64,      //  -
   //452,      //  o
   236,     // H   
   416      // L
}; 
/*--------------------------*/


void tic_control_on(){
	TIC_OUT &= ~(TIC_LOAD | TIC_DATA | TIC_DCLK);
	TIC_DIR |=  (TIC_LOAD | TIC_DATA | TIC_DCLK);
}

void tic_control_off(){
	TIC_DIR &= ~(TIC_LOAD | TIC_DATA | TIC_DCLK);
	TIC_OUT |=  (TIC_LOAD | TIC_DATA | TIC_DCLK);

}

/* ����� �����, ��������(int) /������� */
void tic_print_num (unsigned int Num, unsigned char Pos)
{
	unsigned char a[10], i;
	i=0;
	do
		{
			a[i]=Num%10;
			i++;
			Num /= 10;
		}
	while (Num != 0);
	while(i!=0)
		{
			tic_set_char(a[i-1], Pos++);
			Pos &= 7;
			i--;
		}
	tic_send();
} 
/*-----------------------------------------*/

/* ����� ������� � ������� */
void tic_print_char(unsigned char Char, unsigned char Pos)
{
	tic_set_char(Char, Pos);
	tic_send();
}

void tic_clear(void)
{
	unsigned char c;
	for (c=0;c<8;c++)Buffer[c] = 0;
	tic_send();
}         
/*-----------------------------*/  

/* ���������� ������ ������ */
void tic_set_char(unsigned char Data, unsigned char Pos) 
{
// Pos &= 7;
switch (Data)
    { 
    case ',' : Buffer[Pos] ^= 1; break; 
    case 'E' : Buffer[Pos] |= code[11]; break; 
    case 'H' : Buffer[Pos] |= code[13]; break;
    case 'L' : Buffer[Pos] |= code[14]; break;
    case '-' : Buffer[Pos] |= 64; break;
    case 'd' : Buffer[Pos] |= 460; break;
    default :  Buffer[Pos] = code[Data];
    }
}
/*----------------------------*/

/* ������� ������ */
void tic_send(void)
{   
char b, c;  
for (c=0;c<9;c++)
    { 
		TIC_OUT &= ~TIC_DATA;//DATA = 0x00
		TIC_OUT |=  TIC_DCLK;//DCLK = 1
		DELAY_US(5);
		TIC_OUT &= ~TIC_DCLK;//DCLK = 0
    }       
for (b=8;b>0;b--)
    {  
    for (c=0;c<9;c++)
        { 
    		if((0x01 & (Buffer[b-1] >> c))==1)
    			TIC_OUT |=  TIC_DATA;
    		else
    			TIC_OUT &= ~TIC_DATA;

			TIC_OUT |=  TIC_DCLK;//DCLK = 1
			DELAY_US(5);
			TIC_OUT &= ~TIC_DCLK;//DCLK = 0
        } 
    }     
	TIC_OUT |=  TIC_LOAD;//LOAD = 1
	DELAY_US(5);
	TIC_OUT &= ~TIC_LOAD;//LOAD = 0
}
/*-------------------------------*/
