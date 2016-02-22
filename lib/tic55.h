/*
 * tic55.h
 *
 * TIC55 LCD library for MSP430 (header)
 * 
 *  Created on: 05.07.2013
 *      @author: techncreo
 * 	Based on source from http://radiokot.ru/circuit/digital/home/52/
 * 
 * 	techncreo.blogspot.com
 */


#ifndef _TIC55_INCLUDED_
#define _TIC55_INCLUDED_  

#include <msp430g2553.h>

#define TIC_DIR			P2DIR
#define TIC_OUT			P2OUT

#define TIC_LOAD        BIT1 // MOSI
#define TIC_DATA        BIT2 // MISO
#define TIC_DCLK        BIT0 // SCK

void tic_control_on();
void tic_control_off();
void tic_set_char(unsigned char Data, unsigned char Pos);
void tic_print_num (unsigned int Num, unsigned char Pos);
void tic_clear(void);
void tic_send(void);
void tic_print_char(unsigned char Char, unsigned char Pos);


#endif
