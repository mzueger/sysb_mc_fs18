/*
 * U10_A2.c
 *
 *  SysB Mikrocontroller
 *
 */

#include <avr/io.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <usart.h>
#include <fqd.h>

volatile uint8_t printOutFlag = 0;

ISR(TIMER1_COMPB_vect) {	// 1/1MHz * 64 * 15625 = 1s
	printOutFlag = 1;
	TCNT1 = 0;
}

void initTimer1_1s() {
	TCCR1B = 0x00;	// clear TCCR1B, sets normal timer mode, disable timer
	TCCR1A = 0x00;	// clear TCCR0A, normal port operation, clear compare match
	TCNT1 = 0;	// clear timer register
	OCR1B = 15625;	// set output compare register
	TIMSK1 |= (1 << OCIE1B);	// enable output compare match interrupt
	TCCR1B |= (1 << CS11) | (1 << CS10);	// clock / 64 (from prescaler)
}

int main(void) {
	clock_prescale_set(clock_div_1);
	usartInit96008N1();
	initTimer1_1s();
	fqdInit();

	SREG |= 0x80;	// global interrupt enable

	while(1) {
		if(printOutFlag) {
			printOutFlag = 0;
			usartWriteString("Cnt: ");
			usartWriteInt16(fqdGetCounter());
			usartWriteString("\r\n");
		}
	}

	return 0;
}
