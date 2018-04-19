/*
 * SysB Mikrocontroller
 *
 * U7_A2: Blinklicht mit Timer0 und Ueberlauf
 */

#include <led.h>
#include <avr/power.h>
#include <avr/interrupt.h>

static int16_t counter = 0;
static int8_t ledState = LED_OFF;

ISR(TIMER0_OVF_vect) {
	counter++;
	if(counter >= 490) {	// 1/1MHz * 8 * 255 * 490 = 0.9996s abgelaufen
		ledState = !ledState;
		ledSet(LED_1, ledState);
		counter = 0;
	}
}

int main(void) {
	clock_prescale_set(clock_div_8);
	ledInit(LED_1);

	TCCR0B = 0x00;	// clear TCCR0B, sets normal timer mode, disable timer
	TCCR0A = 0x00;	// clear TCCR0A, normal port operation, no compare match
	TCNT0 = 0;		// clear Timer Register
	TIMSK0 |= (1 << TOIE0);	// Timer Overflow Interrupt Enable 0
	SREG |= 0x80;	// global interrupt enable
	TCCR0B |= (1 << CS01);	// clock / 8 (from prescaler), enable timer

	while(1) { }

	return 0;
}
