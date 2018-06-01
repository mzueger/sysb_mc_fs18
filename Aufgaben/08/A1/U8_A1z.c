/*
 * Aufgabe 8.1 (mit Poti)
 *
 */

#include <avr/io.h>
#include <avr/power.h>
#include <stdint.h>
#include "adc.h"
#include "button.h"
#include "usart.h"

int main(void) {
	buttonInit(BUTTON_S1);
	clock_prescale_set(clock_div_1);
	usartInit96008N1();

	adcInit(1); // Poti an PF1 (ADC1)
	int16_t val = 0;
	uint8_t wasPressed = 0;

	while(1) {
		if(buttonGet(BUTTON_S1) && !wasPressed) {
			val = adcRead();
			usartWriteInt16(val);
			usartWriteByte('\n');
			wasPressed = 1;
		}
		else if(!buttonGet(BUTTON_S1)) {
			wasPressed = 0;
		}
	}

	return 0;
}
