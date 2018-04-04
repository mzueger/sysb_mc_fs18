/**********************************************************
 * SysB: Mikrocontroller                                  *
 *                                                        *
 * Driver for UART1                                       *
 *                                                        *
 **********************************************************/

#include <stdint.h>

#define NO_PARITY 0
#define ODD_PARITY 1
#define EVEN_PARITY 2

#define ERR_UART_BASECLK  -1
#define ERR_UART_BAUDRATE -2
#define ERR_UART_DATABITS -3
#define ERR_UART_PARITY   -4
#define ERR_UART_STOPBITS -5

int8_t usartInit(int32_t br, int8_t db, int8_t p, int8_t sb);
int8_t usartInit96008N1(void);

uint8_t usartReadByte(void);
void usartWriteByte(uint8_t b);

int8_t usartWriteString(const char* str);
int8_t usartReadString(char* sb, uint8_t l, char e);

int8_t usartWriteInt16(int16_t v);
