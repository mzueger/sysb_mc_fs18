/*
 * A9 Aufgabe 3
 * a9-3.c
 * 
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include <usart.h>
#include <adc.h>

int16_t counter = 0;

ISR(TIMER0_COMPA_vect) {
	counter ++;
	if(counter >= 5000) {
		float r = 330.0 * ((1023.0 / adc_read()) - 1);
		float t = -1;
		
		if(r >= 330.0 && r <424.5) { // 20...25°C
			t = (r - 424.5) / (330.0 - 424.5) * 5 + 20.0;
		}

		else if(r >= 258.2 && r < 330.0) { // 25...30°C
			t = (r - 330.0) / (258.2 - 330.0) * 5 + 25.0;
		}
		else if(r >= 203.4 && r < 258.2) { // 30... 35°C
			t = (r - 258.2) / (203.4 - 258.2) * 5 + 30.0;
		}
		else if(r >= 258.2 && r <161.1) { // 35...40°C
			t = (r - 161.1) / (258.2 - 161.1) * 5 + 35.0;
		}
		
		if(t > 0) {
			uart_write_string("Temperature: ");
			int16_t t1 = (int16_t)t;
			int16_t t2 = (int16_t)((t + 0.005) * 100) - t1;
			
			uart_write_int16(t1);
			uart_write_string(".");
			uart_write_int16(t2);
			uart_write_string("°C)\n");
		}
		else {
			uart_write_string("Temperature out of range (R = ");
			uart_write_int16((int16_t)((r + 0.0005) * 1000));
			uart_write_string(" mOhm)\n");
		}
		counter = 0;
	}
}

int main(void) {
	
	uart_init_96008N1();
	adc_init(0, ADC_REF_AVCC);
	
	TCCR0A = 0x00;
	TCCR0B = 0x00;
	TCNT0 = 0;
	TCCR0A |= 0x2;
	OCR0A = 125;
	TIMSK0 |= (1 << OCIE0A);
	SREG |= 0x80;
	TCCR0B |= 0x03;
	
	while(1) { }
	
	return 0;
}
