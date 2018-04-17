/*
 * U6_A4.c
 * SysB_Mikrocontroller
 *
 *  Created on: 17.04.2018
 *
 */


#include <avr/interrupt.h>
#include <avr/power.h>
#include <usart.h>

ISR(USART1_RX_vect) {
	usartWriteByte(UDR1);
}


int main(void) {
	clock_prescale_set(clock_div_1);	// clock auf 8MHz
	usartInit96008N1();		// USART Init
	UCSR1B|=(1<<RXCIE1);	// Receive Interrupt enable
	SREG |= 1 << 7;			// enable global Interrupt
	while (1) {}          	// main() muss aktiv bleiben
	return 0;
}
