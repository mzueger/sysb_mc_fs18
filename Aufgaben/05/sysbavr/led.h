/**********************************************************
 * MME: Embedded Systems                                  *
 *                                                        *
 * Driver for LEDs                                        *
 *                                                        *
 **********************************************************/

#include <stdint.h>

#define NOF_LEDS 4

#define LED_ON   1
#define LED_OFF  0

#define LED_1   0
#define LED_2   1
#define LED_3   2
#define LED_4   3


void ledInit(int8_t led);

void ledSet(int8_t led, int8_t state);

void ledOn(int8_t led);
void ledOff(int8_t led);