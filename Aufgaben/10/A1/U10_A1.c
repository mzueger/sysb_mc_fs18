/*
 * U10_A1.c
 *
 *  SysB Mikrocontroller
 *
 */

#include <avr/io.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <pwm.h>
#include <button.h>

#define PERIOD 50
#define HIGHTIME_MIN 0
#define HIGHTIME_MAX 50
#define HIGHTIME_DELTA 1

ISR(TIMER0_OVF_vect) { // alle 32.64 ms (1 / 8 MHz * 1024 * 255)
    static int16_t ht = 25;	// motor stopped first
    static int count = 0;
    count++;
    if(count > 3) {	// alle 97.92 ms -> in 2.5s full speed
		if(buttonGet(BUTTON_S1) == BUTTON_PRESSED) {
			ht += HIGHTIME_DELTA;
			if(ht > HIGHTIME_MAX) ht = HIGHTIME_MAX;
			pwmUpdateOC1A(PERIOD, ht);
		}
		else if(buttonGet(BUTTON_S2) == BUTTON_PRESSED) {
			ht -= HIGHTIME_DELTA;
			if(ht < HIGHTIME_MIN) ht = HIGHTIME_MIN;
			pwmUpdateOC1A(PERIOD, ht);
		}
		count = 0;
    }
}

void timer0Init() {
    TCCR0B = 0x00;                       // clear TCCR0B, sets normal timer mode, disable timer
    TCCR0A = 0x00;                       // clear TCCR0A -> normal port operation, no compare match
    TCNT0 = 0;                           // clear timer counter value
    TIMSK0 |= (1 << TOIE0);              // Timer Overflow Interrupt Enable 0
    TCCR0B |= (1 << CS02) | (1 << CS00); // clock / 1024 (from prescaler), enable timer
}

int main(void) {
	clock_prescale_set(clock_div_1);	// 8MHz clock

    buttonInit(BUTTON_S1);             	// S1 -> increase hightime
    buttonInit(BUTTON_S2);             	// S2 -> decrease hightime

    timer0Init();                      	// initialize Timer0
	pwmInitOC1A(PERIOD, 25);		   	// init 50% duty cycle -> motor stopped

    SREG |= 0x80;                    	// Global Interrupt Enable

	while(1) {
		// nothing to do
	}

	return 0;
}
