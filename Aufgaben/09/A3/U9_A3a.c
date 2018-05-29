/*
 * Übungsaufgabe 9.3a
 * 
 */

#include <avr/interrupt.h>
#include <avr/power.h>
#include <pwm.h>

int main() {
    clock_prescale_set(clock_div_1); // 8 MHz clock
    pwmInitOC1A(20000, 1500);        // T = 20ms, th = 1.5ms
    SREG |= 0x80;                    // Global Interrupt Enable

    while(1) {
        // nothing to do...
    }
    return 0;
}
