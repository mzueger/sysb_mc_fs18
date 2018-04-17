/*
 * U6_A3.c
 * SysB_Mikrocontroller
 *
 *  Created on: 17.04.2018
 *
 */

#include <avr/power.h>
#include <avr/interrupt.h>
#include <led.h>
#include <usart.h>

int8_t numb = 0;

ISR(INT0_vect) {
	if ((PIND & (1 << PIND0)) != 0) {
		ledOn(LED_1);
		numb++;
	}
	else {
		ledOff(LED_1);
	}
}

ISR(INT1_vect) {
	usartWriteInt8(numb);
}

int main(void) {
	clock_prescale_set(clock_div_1);
	ledInit(LED_1);
	usartInit96008N1();
	EICRA |= (1 << ISC00); // Ext-Interrupt 0 konfigurieren (beide Flanken)
	EICRA &= ~(1 << ISC01);
	EICRA |= (1 << ISC11);	// Ext-Interrupt 1 konfigurieren (fallende Flanke)
	EICRA &= ~(1 << ISC10);
	EIMSK |= (1 << INT0) | (1 << INT1);    // Interrupt INT0 und INT1 aktivieren
	SREG |= 0x80;         // global interrupt enable
	while (1) {
	}          // main() muss aktiv bleiben

	return 0;
}

