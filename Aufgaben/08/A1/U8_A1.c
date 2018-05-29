/*
 * U8_A1.c
 *
 *  SysB Mikrocontroller
 *
 */

#include <avr/io.h>
#include <avr/power.h>
#include <adc.h>
#include <button.h>
#include <usart.h>

int main(void) {
	buttonInit(BUTTON_S1);
	clock_prescale_set(clock_div_1);
	usartInit96008N1();

	adcInit(5);
	uint16_t val = 0;
	float u = 0.0;
	uint8_t wasPressed = 0;

	while(1) {
		if(buttonGet(BUTTON_S1) && !wasPressed) {
			val = adcRead();
			u = val * 2.56 / 1023;
			usartWriteFloat(u);
			usartWriteByte('V');
			usartWriteByte('\r');
			usartWriteByte('\n');
			wasPressed = 1;
		}
		else if(!buttonGet(BUTTON_S1)) {
			wasPressed = 0;
		}
	}



	return 0;
}
