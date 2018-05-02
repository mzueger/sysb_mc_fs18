/*
 * Uebung_7.5.c
 *
 * SysB Mikrocontroller
 */

#include <avr/interrupt.h>
#include <avr/power.h>
#include <usart.h>

volatile uint16_t time_ms = 0;
volatile uint8_t time_sec = 0;
volatile uint8_t time_min = 0;

ISR(INT0_vect) {	// start stop watch
	TCCR0B |= (1 << CS01) | (1 << CS00); // timer prescaler to 64 and start timer
}

ISR(INT1_vect) {	// stop stop watch
	TCCR0B &= ~(1 << CS01) & ~(1 << CS00); // stop timer

	usartWriteInt16(time_min);
	usartWriteString(":");
	usartWriteInt16(time_sec);
	usartWriteString(":");
	usartWriteInt16(time_ms);
	usartWriteString("\n \r");
}

ISR(TIMER0_COMPA_vect) {
	TCNT0 = 0;
	time_ms++;

	if (time_ms >= 1000) {
		time_sec++;
		time_ms = 0;
	}
	if (time_sec >= 60) {
		time_min++;
		time_sec = 0;
	}
}

int main(void) {
	clock_prescale_set(clock_div_1);	// 8MHz clock

	usartInit96008N1();

	DDRD &= ~(1 << DDD0);	// PIND0 als Eingang konfigurieren
	DDRD &= ~(1 << DDD1);	// PIND1 als Eingang konfigurieren
	EICRA |= (1 << ISC01); // Ext-Interrupt 0 konfigurieren (fallende Flanke) -> Start Timer
	EICRA &= ~(1 << ISC00);
	EICRA |= (1 << ISC11);	// Ext-Interrupt 1 konfigurieren (fallende Flanke) -> Stop Timer
	EICRA &= ~(1 << ISC10);
	EIMSK |= (1 << INT0) | (1 << INT1);  // INT0 und INT1 aktivieren
	SREG |= 0x80;        // Global Interrupt Enable

	TCCR0B = 0x00;  // clear TCCR0B
	TCCR0A = 0x00;  // clear TCCR0A
	TCNT0 = 0;      // clear Timer Register
	OCR0A = 125;     // set Output Compare Register
	//(Timer value== 1ms);
	TIMSK0 |= (1 << OCIE0A); // Compare Match Interrupt
	SREG |= 0x80;            // global interrupt enable
	while (1) {
	}
	return 0;
}
