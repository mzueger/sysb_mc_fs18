/*
 * U6_A2.c
 *
 *  Created on: 16.04.2018
 *      Author: Andreas
 */


#include <avr/interrupt.h>
#include <avr/io.h>
#include <led.h>


ISR(INT0_vect) {
	if((PIND & (1<<PIND0)) == 1) {
		ledOn(LED_1);
	}
	else {
		ledOff(LED_1);
	}
}

ISR(INT1_vect) {
	if((PIND & (1<<PIND1)) == 1) {
		ledOn(LED_1);
	}
	else {
		ledOff(LED_1);
	}
}

int main(void) {
	DDRD &= ~(1 << DDD0);	// PIND0 als Eingang konfigurieren
	DDRD &= ~(1 << DDD1);	// PIND1 als Eingang konfigurieren
	ledInit(LED_1);		// LED_1 initialisieren
	ledInit(LED_2);		// LED_2 initialisieren
	EICRA |= (1 << ISC00); // Ext-Interrupt 0 konfigurieren (beide Flanken)
	EICRA &= ~(1 << ISC01);
	EICRA |= (1 << ISC11);	// Ext-Interrupt 1 konfigurieren (fallende Flanke)
	EICRA &= ~(1 << ISC10);
	EIMSK |= (1 << INT0) | (1 << INT1);  // INT0 und INT1 aktivieren
	SREG |= 0x80;        // Global Interrupt Enable
	while(1);
	return 0;
}
