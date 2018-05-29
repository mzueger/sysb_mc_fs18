/*
 * Uebungsaufgabe 9.2 (Taster S1)
 * 
 */

#include <avr/interrupt.h>
#include <avr/power.h>
#include <button.h>
#include <pwm.h>

#define PERIOD 20000
#define HIGHTIME_4 (PERIOD / 4)

int main() {
    static uint8_t f = 1;
    uint8_t s1Pressed = 0;

    clock_prescale_set(clock_div_1); // 8 MHz clock
    
    buttonInit(BUTTON_S1); // Externen Taster initialisieren
    
    pwmInitOC1A(PERIOD, 0);          // T = 20ms, th = 0ms
    
    SREG |= 0x80;                    // Global Interrupt Enable

    while(1) {
        if(buttonGet(BUTTON_S1) && !s1Pressed) {
            pwmUpdateOC1A(PERIOD, HIGHTIME_4 * f);
            f++;
            if(f > 3) f = 1;
            s1Pressed = 1;
        }
        else if(!buttonGet(BUTTON_S1)){
        	s1Pressed = 0;	// reset
        }
    }
    return 0;
}
