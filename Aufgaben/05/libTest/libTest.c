/*
 * SysB Mikrocontroller
 *
 * Library tests
 */

#include <led.h>
#include <button.h>
#include <string.h>
#include <avr/power.h>
#include <util/delay.h>
#include <stdint.h>
#include <usart.h>

#define STRLEN 8

int main(void) {
	char str[STRLEN];
	clock_prescale_set(clock_div_1);

	usartInit96008N1();

	for(int8_t i = FIRST_BUTTON; i <= LAST_BUTTON; ++i) {
		buttonInit(i);
	}

	for(int8_t i = FIRST_LED; i <= LAST_LED; ++i) {
		ledInit(i);
	}

	usartWriteString("Test application started\n");

	usartWriteString("Testing string functions...\n");
	usartWriteString("string_equals:\n");
	if(stringEquals("hello", "hello")) usartWriteString("string 1: OK\n");
	else usartWriteString("string 1: Failure\n");
	if(!stringEquals("hello", "heLlo")) usartWriteString("string 2: OK\n");
	else usartWriteString("string 2: Failure\n");

	usartWriteString("int16_to_string:\n");
	int16ToString(0, str, STRLEN);
	usartWriteString(str);
	usartWriteByte('\n');

	int16ToString(12345, str, STRLEN);
	usartWriteString(str);
	usartWriteByte('\n');

	int16ToString(-12345, str, STRLEN);
	usartWriteString(str);
	usartWriteByte('\n');

	usartWriteString("string_to_int16:\n");
	char a1[] = "12345"; char a2[] = "-12345";
	int16_t v1, v2;

	stringToInt16(a1, &v1);
	stringToInt16(a2, &v2);
	if(v1 == 12345) usartWriteString("a1[] -> v1: OK\n");
	else usartWriteString("a1[] -> v1: Failure\n");
	if(v2 == -12345) usartWriteString("a2[] -> v2: OK\n");
	else usartWriteString("a2[] -> v2: Failure\n");

	usartWriteString("All LEDs on...\n");
	for(int8_t i = FIRST_LED; i <= LAST_LED; ++i) {
		ledOn(i);
		_delay_ms(300);
	}
	_delay_ms(2000);

	usartWriteString("All LEDs off...\n");
	for(int8_t i = FIRST_LED; i <= LAST_LED; ++i) {
		ledOff(i);
		_delay_ms(300);
	}

	usartWriteString("Reading buttons:\n");
	int8_t b = FIRST_BUTTON;
	while(1) {
		if(buttonGet(b) == BUTTON_PRESSED) {
			usartWriteString("Button S_");
			usartWriteByte(b + '0' - FIRST_BUTTON);
			usartWriteString(" pressed\n");
		}
		b = ((b + 1) % 4) + FIRST_BUTTON;
		_delay_ms(200);
	}

	return 0;
}
