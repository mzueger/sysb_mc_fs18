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


void led_init(int8_t led);

void led_set(int8_t led, int8_t state);

void led_on(int8_t led);
void led_off(int8_t led);