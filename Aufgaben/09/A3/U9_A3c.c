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

ISR(TIMER0_COMPA_vect) { // alle 9.984 ms (1 / 8 MHz * 1024 * 78)
    static uint8_t counter = 0;
    static char x = 0;
    
    TCNT0 = 0;
    counter++;
    if(counter >= 200) {
        pwmUpdateOC1A(PERIOD, x ? HIGHTIME_MAX : HIGHTIME_MIN);
        counter = 0;
        x = !x;
    }
}

void timer0Init() {
    TCCR0B = 0x00;                       // clear TCCR0B, sets normal timer mode, disable timer
    TCCR0A = 0x00;                       // clear TCCR0A -> normal port operation, no compare match
    TCNT0 = 0;                           // clear timer counter value
    OCR0A = 78;                          // Compare value A
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
