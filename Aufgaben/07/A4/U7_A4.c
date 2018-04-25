/*
 * U7_A4.c
 * SysB Mikrocontroller
 *
 */

#include <led.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <stdint.h>

static int8_t led = 0;

ISR(TIMER1_COMPB_vect) {
	TCNT1 = 0;	// reset timer
	ledOff(led);
	led = (led + 1) % NOF_LEDS;
	ledOn(led);
}

int main(void) {
	clock_prescale_set(clock_div_1);

	for(int i = 0; i < NOF_LEDS; i++) {
		ledInit(i);
		ledSet(i, LED_OFF);
	}

	ledOn(led);

	TCCR1B = 0x00;	// clear TCCR1B, sets normal timer mode, disable timer
	TCCR1A = 0x00;	// clear TCCR0A, normal port operation, clear compare match
	TCNT1 = 0;	// clear timer register
	OCR1B = 3125;	// 0.1s / 256 (prescaler) * 8MHz (clk)
	TIMSK1 |= (1 << OCIE1B);	// compare B match interrupt enable

	SREG |= 0x80;	// global interrupt enable
	TCCR1B |= (1 << CS12);	// clk / 256 (prescaler)

	while(1) { }

	return 0;
}
