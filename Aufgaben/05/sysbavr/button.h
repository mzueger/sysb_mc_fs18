/**********************************************************
 * MME: Embedded Systems                                  *
 *                                                        *
 * Driver for Buttons                                     *
 *                                                        *
 **********************************************************/

#include <stdint.h>

#define NOF_BUTTONS        4
#define BUTTON_PRESSED     1
#define BUTTON_NOT_PRESSED 0
#define BUTTON_S1          0
#define BUTTON_S2          1
#define BUTTON_S3          2
#define BUTTON_S4          3

void button_init(int8_t button);

int8_t button_get(int8_t button);