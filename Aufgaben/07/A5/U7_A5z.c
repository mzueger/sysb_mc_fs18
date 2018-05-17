/*
 * Übungsaufgabe 7.5
 * 
 * Lösungsvariante mit nur einem
 * Interupt-fähigen Taster
 *
 */

#include <avr/interrupt.h>
#include <avr/power.h>
#include <usart.h>

volatile uint16_t time_ms = 0;
volatile uint8_t time_s = 0;
volatile uint8_t time_min = 0;
volatile char running = 0;

ISR(INT1_vect) { // Start/Stop
    if(running) {
        TCCR0B &= ~(1 << CS01) & ~(1 << CS00); // stop timer
        
        usartWriteInt8(time_min);
        usartWriteByte(':');
        usartWriteInt8(time_s);
        usartWriteByte(':');
        usartWriteInt16(time_ms);
        usartWriteByte('\n');
    }
    else {
        time_ms = 0;
        time_s = 0;
        time_min = 0;
        TCCR0B |= (1 << CS01) | (1 << CS00); // timer prescaler to 64 -> start timer
    }
    
    running = !running;
}

ISR(TIMER0_COMPA_vect) {
    TCNT0 = 0;
    time_ms++;

    if(time_ms >= 1000) {
        time_s++;
        time_ms = 0;
    }
    if(time_s >= 60) {
        time_min++;
        time_s = 0;
    }
}

void initExtInt1() {
    DDRD &= ~(1 << DDD1);   // PIND1 als Eingang konfigurieren
    EICRA |= (1 << ISC11);  // Interrupt bei fallender Flanke
    EICRA &= ~(1 << ISC10);
    EIMSK |= (1 << INT1);   // INT1 aktivieren
}

void initTimer0() {
    TCCR0B = 0x00;              // clear TCCR0B
    TCCR0A = 0x00;              // clear TCCR0A
    TCNT0 = 0;                  // clear Timer Register
    OCR0A = 125;                // set Output Compare Register -> Timer value: 1ms;
    TIMSK0 |= (1 << OCIE0A);    // Compare Match Interrupt
}

int main() {
    clock_prescale_set(clock_div_1); // 8 MHz clock
    usartInit96008N1();              // USART initialisieren
    initExtInt1();                   // INT1 für Start/Stop
    initTimer0();                    // Timer0 initialisieren
    SREG |= 0x80;                    // Global Interrupt Enable

    while(1) {
        // Nichts zu tun...
    }
    return 0;
}
