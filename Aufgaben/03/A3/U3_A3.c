/*
 * U3_A3.c
 */

#include <avr/io.h>
#include <avr/power.h>

void usartInit(void) {
	UBRR1 = 51; // set baud rate to 9600 (fosc = 8 MHz)
	UCSR1B |= 1 << TXEN1; // enable transmitter
	UCSR1B |= 1 << RXEN1; // enable receiver
	UCSR1C |= (1 << UCSZ11) | (1 << UCSZ10); // set 8 databits
	UCSR1B &= ~(1 << UCSZ12); // set 8 databits
	UCSR1C &= ~(1 << USBS1); // set 1 stop bit
	// flush receive buffer
	uint8_t dummy;
	while(UCSR1A & (1 << RXC1)) dummy = UDR1;
}

void usartWriteChar(char c){
	while((UCSR1A & (1 << UDRE1)) == 0); // UDRE1 = 0 indicates buffer not empty -> wait
	UDR1 = c; // add character to data register
}

char usartReadChar(void) {
	while((UCSR1A & (1 << RXC1)) == 0);	// wait until RXC1 bit is set (data ready)
	uint8_t receivedByte = UDR1;	// read data
	return receivedByte;
}

int main(void) {
	clock_prescale_set(clock_div_1);	// set clock prescaler to 1 (8MHz)
	usartInit();	// init USART
	while(1) {
		char c = usartReadChar();	// read char
		usartWriteChar(c); // write char back to host
	}

	return 0;
}
