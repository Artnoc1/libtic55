/*
 * main.c
 *
 * 	TIC55 demo project for MSP430
 * 
 *  Created on: 05.07.2013
 *      @author: techncreo
 * 	@license: MIT
 * 
 * 	techncreo.blogspot.com
 */

#include  <msp430g2553.h>
#include <signal.h>
#include <stdint.h>

#include <tic55.h>

int main(void){

	WDTCTL = WDTPW + WDTHOLD;
	tic_control_on();

	tic_print_char('H', 0);
	tic_print_char('E', 1);
	tic_print_char('L', 2);
	tic_print_char('L', 3);
	tic_print_char( 0,  4);

	tic_control_off();
       _BIS_SR(LPM0_bits + GIE);  // Enter Low power mode 0*/
}
