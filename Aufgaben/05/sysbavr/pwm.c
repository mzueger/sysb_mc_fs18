#include <avr/io.h>
#include <avr/interrupt.h>

static uint16_t nextPeriod;

void pwmInitOC1A(uint16_t period, uint16_t hightime) {
    
    // Stop Timer1:
    TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
    
    // Compare output mode for OC1A: Clear on compare match
    TCCR1A &= ~(1 << COM1A0);
    TCCR1A |= 1 << COM1A1;
    
    // Compare output mode for OC1B: Normal port operation
    TCCR1A &= ~((1 << COM1B1) | (1 << COM1B0));
    
    // Compare output mode for OC1C: Normal port operation
    TCCR1A &= ~((1 << COM1C1)| (1 << COM1C0));
    
    // Waveform generation mode: Fast PWM (mode 14)
    TCCR1A &= ~(1 << WGM10);
    TCCR1A |= 1 << WGM11;
    TCCR1B |= (1 << WGM12) | (1 << WGM13);

    // PWM period time
    ICR1  = period;
    
    // PWM high time
    OCR1A = hightime;
    
    // Configure PD5 as output (for PWM signal)
    DDRB |= 1 << DDB5;
    
    // Clock select: clkI/0 / 8 -> start timer
    TCCR1B |= 1 << CS11;
}


ISR(TIMER1_COMPA_vect) {
    ICR1 = nextPeriod;        // update period time
    TIMSK1 &= ~(1 << OCIE1A); // disable compare A match interrupt
}

void pwmUpdateOC1A(uint16_t period, uint16_t hightime) {
    SREG &= 0x7F;          // Global Interrupt disable
    OCR1A = hightime;      // Update hightime
    nextPeriod = period;   // Update period if counter reaches top next time by
    TIMSK1 |= (1<<OCIE1A); // enabling compare A match interrupt temporarily
    SREG |= 0x80;          // Global Interrupt enable
}
