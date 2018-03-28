/*
 * Systemtechnik B: Mikrocontroller
 *
 * Übung 4, Aufgabe 3
 * Strings vergleichen
 *
 * Testprogramm fuer den AVR!
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

void usartWriteString(const char string[]) {
    char i = 0;
    while(string[i] != '\0') {
        usartWriteChar(string[i++]);
    }
}

void usartWriteInt8(int8_t value) {
    if(value < 0) {                        // Falls Zahl negativ
        usartWriteChar('-');               // Minuszeichen ausgeben
        value = -value;                    // und dann positiv machen
    }                                      // ACHTUNG: Problem wenn value = -128!

    if(value >= 100) {                     // Wenn dreistellig,
        usartWriteChar(value / 100 + '0'); // 100er Stelle ausgeben
    }
    if(value >= 10) {                      // Wenn min. zweistellig
        value = value % 100;               // 100er Stelle wegschneiden
        usartWriteChar(value / 10 + '0');  // und 10er Stelle ausgeben
    }
    value = value % 10;                    // Zehner Stelle wegschneiden
    usartWriteChar(value + '0');           // und letzte Stelle ausgeben
}

/**
 * Zwei Strings vergleichen.
 * @param str1 String 1
 * @param str2 String 2
 * @return 1 wenn beide Strings identisch, sonst 0
 */
int8_t stringEquals(const char str1[], const char str2[]) {
    int i = 0;
    while(str1[i] == str2[i]) {
        if(str1[i] == '\0') {
            return 1;
        }
        i++;
    }
    return 0;
}

int main(void) {

	clock_prescale_set(clock_div_1);	// set clock prescaler to 1 (8MHz)
	usartInit();	// init USART

    char str1[] = "Hello";
    char str2[] = "HEllo";
    char str3[] = "Hello, World";

    int error = 0;

    if(!stringEquals(str1, str1)) {
        error++;
        usartWriteString("ERROR in test 1\n");
    }

    if(stringEquals(str1, str2)) {
        error++;
        usartWriteString("ERROR in test 2\n");
    }

    if(stringEquals(str1, str3)) {
        error++;
        usartWriteString("ERROR in test 3\n");
    }

    usartWriteString("Test finished with ");
    usartWriteInt8(error);
    usartWriteString(" error(s)\n");

    return 0;
}


