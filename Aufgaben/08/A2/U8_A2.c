/*
 * Übungsaufgabe 8.2
 * 
 */

#include <avr/interrupt.h>
#include <avr/power.h>
#include <button.h>
#include <pwm.h>

#define PERIOD 20000
#define HIGHTIME_4 (PERIOD / 4)

ISR(INT1_vect) {
    static uint8_t f = 1;
    pwmUpdateOC1A(PERIOD, HIGHTIME_4 * f);
    f++;
    if(f > 3) f = 1;
}

int main() {
    clock_prescale_set(clock_div_1); // 8 MHz clock
    
    buttonInit(BUTTON_EXT); // Externen Taster initialisieren
    EICRA |= ~(1 << ISC10); // INT1 reagiert nur auf fallende Flanke
    EICRA |= 1 << ISC11;
    EIMSK |= 1 << INT1;     // Interrupt INT1 (BUTTON_EXT) aktivieren
    
    pwmInitOC1A(PERIOD, 0);          // T = 20ms, th = 0ms
    
    SREG |= 0x80;                    // Global Interrupt Enable

    while(1) {
        // nothing to do...
    }
    return 0;
}
