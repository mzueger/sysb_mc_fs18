/*
 * SysB Mikrocontroller
 *
 * U7-A3: Blinklicht mit Timer1
 */

#include <led.h>
#include <avr/power.h>
#include <avr/interrupt.h>

static int8_t ledState = LED_OFF;

ISR(TIMER1_COMPB_vect) {	// 1/1MHz * 64 * 15625 = 1s
	ledState = !ledState;
	ledSet(LED_1, ledState);
	TCNT1 = 0;
}

int main(void) {
	clock_prescale_set(clock_div_8);

	ledInit(LED_1);

	TCCR1A = 0x00;	// clear TCCR1B, sets normal timer mode, disable timer
	TCCR1B = 0x00;	// clear TCCR0A, normal port operation, clear compare match
	TCNT1 = 0;	// clear timer register
	OCR1B = 15625;	// set output compare register
	TIMSK1 |= (1 << OCIE1B);	// enable output compare match interrupt
	SREG |= 0x80;	// global interrupt enable
	TCCR1B |= (1 << CS11) | (1 << CS10);	// clock / 64 (from prescaler)

	while(1) { }

	return 0;
}
