/**********************************************************
 * SysB: Mikrocontroller                                  *
 *                                                        *
 * Driver for Buttons at Port D                           *
 *                                                        *
 **********************************************************/

#include "button.h"
#include <avr/io.h>

/**
 * @brief Initialize Button at Port D
 * 
 * @param button Button to initialize (use BUTTON_Sx)
 */
void buttonInit(int8_t button) {
    if((button >= FIRST_BUTTON && button <= LAST_BUTTON) || button == BUTTON_EXT) {
        DDRD &= ~(1 << button);
    }
}

/**
 * @brief Read button
 * 
 * @param button Button to read from PIND (4..7)
 * @return 1 if button pressed, 0 if not pressed and -1 in case of error
 */
int8_t buttonGet(int8_t button) {
	if((button >= FIRST_BUTTON && button <= LAST_BUTTON) || button == BUTTON_EXT) {
        return (PIND & (1 << button)) == 0;
    }
    else {
        return BUTTON_INV;
    }
}
