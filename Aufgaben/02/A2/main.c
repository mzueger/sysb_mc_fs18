// Aufgabe 2.2

#include <avr/io.h>

int main() {
    
    // Ein- und Ausgänge konfigurieren
	DDRD &= ~(1 << DDD4);		// Switch S1 -> PD4 als Eingang konfigurieren 
	DDRD &= ~(1 << DDD5);		// Switch S2 -> PD5 als Eingang konfigurieren
	DDRD &= ~(1 << DDD6);		// Switch S3 -> PD6 als Eingang konfigurieren
	DDRD &= ~(1 << DDD7);		// Switch S4 -> PD7 als Eingang konfigurieren
	DDRB = DDRB | (1 << DDB0);	// LED 1 -> PortB0 als Ausgang konfigurieren
	DDRB = DDRB | (1 << DDB1);	// LED 1 -> PortB1 als Ausgang konfigurieren
	DDRB = DDRB | (1 << DDB2);	// LED 1 -> PortB2 als Ausgang konfigurieren
	DDRB = DDRB | (1 << DDB3);	// LED 1 -> PortB3 als Ausgang konfigurieren
    
    // Endlos-Schleife
	while(1) {
		// S1 / LED1
		if((PIND & (1 << PIND4)) == 0) {
			PORTB  = PORTB | (1 << PORTB0);
		}
		else {
			PORTB  = PORTB & ~(1 << PORTB0);
		}

		// S2 / LED2
		if((PIND & (1 << PIND5)) == 0) {
			PORTB  = PORTB | (1 << PORTB1);
		}
		else {
			PORTB  = PORTB & ~(1 << PORTB1);
		}

		// S3 / LED3
		if((PIND & (1 << PIND6)) == 0) {
			PORTB  = PORTB | (1 << PORTB2);
		}
		else {
			PORTB  = PORTB & ~(1 << PORTB2);
		}

		// S4 / LED4
		if((PIND & (1 << PIND7)) == 0) {
			PORTB  = PORTB | (1 << PORTB3);
		}
		else {
			PORTB  = PORTB & ~(1 << PORTB3);
		}
	}
	return 0;
}
