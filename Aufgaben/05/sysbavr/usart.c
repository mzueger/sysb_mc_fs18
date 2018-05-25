/**********************************************************
 * SysB: Mikrocontroller                                  *
 *                                                        *
 * Driver for UART1                                       *
 *                                                        *
 **********************************************************/

#include "string.h"
#include <avr/io.h>
#include "usart.h"

/**
 * @brief Initialize UART1.
 * This driver riqures that the microcontroller is running
 * with a base clock of 8 MHz. This means the clock prescaler
 * has to be 1 (CLKPR == 0).
 * 
 * @param br Baudrate (2400 to 460800)
 * @param db Number of data bits (5, 6, 7 or 8)
 * @param p Parity (NO_PARITY, ODD_PARITY or EVEN_PARITY)
 * @param sb Number of stop bits (1 or 2)
 * @return Negative error code on failure
 */
int8_t usartInit(int32_t br, int8_t db, int8_t p, int8_t sb) {
	// check clock prescaler
	if((CLKPR & 0x0F) != 0) return ERR_UART_BASECLK; // check prescaler
	
	// configure baudrate
	if(br < 2400 || br > 460800) return ERR_UART_BAUDRATE;
	UBRR1 = (8000000 + br * 8) / (16 * br) - 1;
	
	// configure data bits
	if(db < 5 || db > 8) return ERR_UART_DATABITS;
	UCSR1C = (UCSR1C & 0xF9) | ((db - 5) << 1);
	
	// configure parity
	switch(p) {
		case NO_PARITY:
			UCSR1C &= ~(1 << UPM10);
			UCSR1C &= ~(1 << UPM11);
			break;
		case ODD_PARITY:
			UCSR1C |= 1 << UPM10;
			UCSR1C |= 1 << UPM11;
			break;
		case EVEN_PARITY:
			UCSR1C &= ~(1 << UPM10);
			UCSR1C |= 1 << UPM11;
			break;
		default:
			return ERR_UART_PARITY;
	}
	
	// configure stop bits
	switch(sb) {
		case 1:
			UCSR1C &= ~(1 << USBS1);
			break;
		case 2:
			UCSR1C |= (1 << USBS1);
			break;
		default:
			return ERR_UART_STOPBITS;
	}
	
	// enable receiver and transmitter
	UCSR1B |= 1 << TXEN1; 
	UCSR1B |= 1 << RXEN1;
	
	// flush receive buffer
	uint8_t dummy;
	while(UCSR1A & (1 << RXC1)) dummy = UDR1;
	return 0;
}

/**
 * @brief Initialize UART1 with default parameters.
 * Default values: 9600 Baud per second, 8 data bits,
 * no parity bit and a single stop bit.
 * 
 * @return Negative error code on failure
 */
int8_t usartInit96008N1(void) {
	return usartInit(9600, 8, NO_PARITY, 1);
}

/**
 * @brief Read a single byte from the receive buffer.
 * This method blocks until a byte is received!
 * 
 * @return Received byte
 */
uint8_t usartReadByte(void) {
	while((UCSR1A & (1 << RXC1)) == 0);
	uint8_t receivedByte = UDR1;
	return receivedByte;
}

/**
 * @brief Write a single byte to the transmit buffer.
 * This method blocks until the byte is transmitted!
 * 
 * @param b byte to transmit
 */
void usartWriteByte(uint8_t b) {
	while((UCSR1A & (1 << UDRE1)) == 0);
	UDR1 = b;
}

/**
 * @brief Write a string to the UART.
 * This method blocks until the whole string is transmitted!
 * 
 * @param str Null terminated string to transmit
 * @return Number of transmitted bytes or a negative error code
 */
int8_t usartWriteString(const char* str) {
	if(!str) return -1;
	int8_t i = 0;
	while(str[i] != '\0' && i <= INT8_MAX) {
		usartWriteByte(str[i]);
		i++;
	}
	return i;
}

/**
 * @brief Read a string from the UART.
 * This method blocks until the given end character is received!.
 * 
 * @param sb Buffer to write the received string into (null terminated)
 * @param l Length of the buffer (max. length of the string)
 * @param e Character which terminates the received string
 * @return Number of received bytes or a negative error code
 */
int8_t usartReadString(char* sb, uint8_t l, char e) {
	if(!sb) return -1;
	int8_t i;
	for(i = 0; i < l && i < INT8_MAX; i++) {
		sb[i] = usartReadByte();
		if(sb[i] == e) break;
	}
	sb[i] = '\0';
	return i;
}

void usartWriteInt8(int8_t value) {
    if(value < 0) {                        // Falls Zahl negativ
    	usartWriteByte('-');               // Minuszeichen ausgeben
        value = -value;                    // und dann positiv machen
    }                                      // ACHTUNG: Problem wenn value = -128!

    if(value >= 100) {                     // Wenn dreistellig,
    	usartWriteByte(value / 100 + '0'); // 100er Stelle ausgeben
    }
    if(value >= 10) {                      // Wenn min. zweistellig
        value = value % 100;               // 100er Stelle wegschneiden
        usartWriteByte(value / 10 + '0');  // und 10er Stelle ausgeben
    }
    value = value % 10;                    // Zehner Stelle wegschneiden
    usartWriteByte(value + '0');           // und letzte Stelle ausgeben
}

#define UART_WRITE_INT16_BUFLEN 8
int8_t usartWriteInt16(int16_t v) {
	char buf[UART_WRITE_INT16_BUFLEN];
	
	int8_t len = int16ToString(v, buf, UART_WRITE_INT16_BUFLEN);
	if(len < 0) return len;
	
	return usartWriteString(buf);
}

void usartWriteFloat(float f) { //f = 1.234
	short s = (short)f; // s = 1
	float d = f-(float)s; // d = 0.234
	short t = d * 1000; // t = 234
	usartWriteInt16(s);
	usartWriteByte('.');
	usartWriteInt16(t);
}
