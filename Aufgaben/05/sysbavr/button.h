/**********************************************************
 * SysB: Mikrocontroller                                  *
 *                                                        *
 * Driver for Buttons                                     *
 *                                                        *
 **********************************************************/

#include <stdint.h>

#define BUTTON_PRESSED     1
#define BUTTON_NOT_PRESSED 0

#define BUTTON_S1          4
#define BUTTON_S2          5
#define BUTTON_S3          6
#define BUTTON_S4          7

#define FIRST_BUTTON       BUTTON_S1
#define LAST_BUTTON        BUTTON_S4

#define BUTTON_EXT         1

#define BUTTON_INV         -1

void buttonInit(int8_t button);

int8_t buttonGet(int8_t button);
