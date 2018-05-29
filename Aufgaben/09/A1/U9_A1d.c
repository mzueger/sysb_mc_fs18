/*
 * Übungsaufgabe 9.1d
 * 
 */

#include <avr/interrupt.h>
#include <avr/power.h>
#include <pwm.h>

int main() {
    clock_prescale_set(clock_div_1); // 8 MHz clock
    pwmInitOC1A(20000, 2000);        // T = 20ms, th = 2ms
    SREG |= 0x80;                    // Global Interrupt Enable

    while(1) {
        // nothing to do...
    }
    return 0;
}
