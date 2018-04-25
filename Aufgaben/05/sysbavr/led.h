/**********************************************************
 * SysB: Mikrocontroller                                  *
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

#define FIRST_LED LED_1
#define LAST_LED  LED_4

void ledInit(int8_t led);

void ledSet(int8_t led, int8_t state);

void ledOn(int8_t led);
void ledOff(int8_t led);

void ledToggle(int8_t led);
