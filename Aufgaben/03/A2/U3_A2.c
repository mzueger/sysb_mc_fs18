/*
 * U3_A2.c
 */

#include <avr/io.h>
#include <avr/power.h>

void usartWriteChar(char c){
	while((UCSR1A & (1 << UDRE1)) == 0); // UDRE1 = 0 indicates buffer not empty -> wait
	UDR1 = c; // add character to data register
}

int main(void){
	clock_prescale_set(clock_div_1); // set the system clock prescaler to 1 (8MHz)

	UBRR1 = 51; // set baud rate to 9600 (fosc = 8 MHz)

	UCSR1B |= 1 << TXEN1; // Enable Transmitter only
	UCSR1C |= (1 << UCSZ11) | (1 << UCSZ10); // set 8 databits
	UCSR1B &= ~(1 << UCSZ12); // set 8 databits
	UCSR1C &= ~(1 << USBS1); // set 1 stop bit

	usartWriteChar('h');
	usartWriteChar('a');
	usartWriteChar('l');
	usartWriteChar('l');
	usartWriteChar('o');

	return 0;
}
