/**********************************************************
 * MME: Embedded Systems                                  *
 *                                                        *
 * Driver for LEDs                                        *
 *                                                        *
 **********************************************************/

#include "led.h"
#include <avr/io.h>

/**
 * @brief Initialize LED at Port B
 * 
 * @param led LED to initialize (0..3)
 */
void ledInit(int8_t led) {
	if((led >= 0) && (led < NOF_LEDS)) {
		DDRB |= (1 << (DDB0 + led));
	}
}

/**
 * @brief Turn LED on or off
 * 
 * @param led LED to turn on or off (0..3)
 * @param state LED_ON or LED_OFF
 */
void ledSet(int8_t led, int8_t state) {
	if(led >= 0 && led < NOF_LEDS) {
		if(state == LED_ON)
			ledOn(led);
		else if(state == LED_OFF)
			ledOff(led);
	}
}

/**
 * @brief TurnLED on
 * 
 * @param led LED to turn on (0..3)
 */
void ledOn(int8_t led) {
	if(led >= 0 && led < NOF_LEDS) {
		PORTB  |= (1 << (PORTB0 + led));
	}
}

/**
 * @brief TurnLED off
 * 
 * @param led LED to turn off (0..3)
 */
void ledOff(int8_t led) {
	if(led >= 0 && led < NOF_LEDS) {
		PORTB &= ~(1 << (PORTB0 + led));
	}
}
