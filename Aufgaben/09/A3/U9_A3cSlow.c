/*
 * Übungsaufgabe 9.3c
 * 
 */

#include <avr/interrupt.h>
#include <avr/power.h>
#include <pwm.h>

#define PERIOD 20000
#define HIGHTIME_MIN 1200
#define HIGHTIME_MAX 2200

ISR(TIMER0_COMPA_vect) { // alle 8.064 ms (1 / 8 MHz * 1024 * 32)
    static uint16_t highTime = HIGHTIME_MIN;
    static uint8_t dir = 0;
    
    TCNT0 = 0;
    	if(!dir)	// dir == 0: positiv, dir == 1: negative Richtung
    	{
    		highTime++;
    		if(highTime > HIGHTIME_MAX) {
    			dir = 1;
    			highTime = HIGHTIME_MAX-1;	// go down first step
    		}
    	}
    	else {	// negativ
    		highTime--;
    		if(highTime < HIGHTIME_MIN) {
    			dir = 0;
    			highTime = HIGHTIME_MIN+1;	// count up first step
    		}
    	}
        pwmUpdateOC1A(PERIOD, highTime);
}

void timer0Init() {
    TCCR0B = 0x00;                       // clear TCCR0B, sets normal timer mode, disable timer
    TCCR0A = 0x00;                       // clear TCCR0A -> normal port operation, no compare match
    TCNT0 = 0;                           // clear timer counter value
    OCR0A = 32;                          // Compare value A
    TIMSK0 |= (1 << OCIE0A);             // Compare match A interrupt
    TCCR0B |= (1 << CS02) | (1 << CS00); // clock / 1024 -> start timer
}

int main() {
    clock_prescale_set(clock_div_1);     // 8 MHz clock
    
    timer0Init();                        // initialize Timer0
    pwmInitOC1A(PERIOD, HIGHTIME_MIN);   // initialize PWM: T = 20ms, ht = 1.2ms
    
    SREG |= 0x80;                        // Global Interrupt Enable

    while(1) {
        // nothing to do...
    }
    return 0;
}
