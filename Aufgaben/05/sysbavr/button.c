/**********************************************************
 * MME: Embedded Systems                                  *
 *                                                        *
 * Driver for Buttons                                     *
 *                                                        *
 **********************************************************/

#include <button.h>
#include <avr/io.h>

static int8_t buttonToPin(int8_t button) {
	switch(button) {
		case BUTTON_S1: return 4;
		case BUTTON_S2: return 5;
		case BUTTON_S3: return 6;
		case BUTTON_S4: return 7;
		default: return -1;
	}
}

/**
 * @brief Initialize button at Port D
 * 
 * @param button Button to initialize (4..7)
 */
void buttonInit(int8_t button) {
	int8_t pin = buttonToPin(button);
	if(pin >= 0)
		DDRD &= ~(1 << pin);
}

/**
 * @brief Read button
 * 
 * @param button Button to read from PIND (4..7)
 * @return 1 if button pressed, 0 if not pressed and -1 in case of error
 */
int8_t buttonGet(int8_t button) {
	int8_t pin = buttonToPin(button);
	if(pin < 0) return -1;
	return (PIND & (1 << pin)) == 0;
}
