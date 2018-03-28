/*
 * Systemtechnik B: Mikrocontroller
 *
 * Übung 4, Aufgaben 5
 * String zu Integer (16 Bit)
 *
 * Testprogramm für den AVR!
 */

#include <avr/io.h>
#include <avr/power.h>
#include <limits.h>

/**
 * Wandelt einen Null-terminierten String
 * in einen vorzeichenbehafteten 16 Bit
 * Integer.
 * @param str String, muss eine dezimale Zahl repräsentieren
 * @return Repräsentierter Wert oder INT16_MIN im Fehlerfall
 */
int16_t stringToInt16(const char str[]) {
    int8_t i = 0;
    int16_t v = 0;
	int8_t is_negative = 0;

	while(str[i] != '\0') {
		if(str[i] == '-') {
			is_negative = 1;
		}
		else if(str[i] >= '0' && str[i] <= '9') {
            v = v * 10 + str[i] - '0';
        }
		else {
			return INT16_MIN;
		}
        i++;
     }
	 if(is_negative) v = -v;
	 return v;
}

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

int main(void) {
	clock_prescale_set(clock_div_1);	// set clock prescaler to 1 (8MHz)
	usartInit();	// init USART

	char str1[] = "123";
	char str2[] = "-9";
	char str3[] = "0";
	char str4[] = "32767";
	char str5[] = "-32768";
	char str6[] = "abc";

	int16_t v1 = stringToInt16(str1);
    int16_t v2 = stringToInt16(str2);
    int16_t v3 = stringToInt16(str3);
    int16_t v4 = stringToInt16(str4);
    int16_t v5 = stringToInt16(str5);
    int16_t v6 = stringToInt16(str6);

	if(v1 != 123)    usartWriteString("ERROR for str1\n");
	if(v2 != -9)     usartWriteString("ERROR for str2\n");
	if(v3 != 0)      usartWriteString("ERROR for str3\n");
	if(v4 != 32767)  usartWriteString("ERROR for str4\n");
	if(v5 != -32768) usartWriteString("ERROR for str5\n");
	if(v6 != -32768) usartWriteString("ERROR for str6\n");

	usartWriteString(str1);
	usartWriteString(" = ");
	usartWriteInt8(v1);
	usartWriteChar('\n');

	usartWriteString(str2);
	usartWriteString(" = ");
	usartWriteInt8(v2);
	usartWriteChar('\n');

	usartWriteString(str3);
	usartWriteString(" = ");
	usartWriteInt8(v3);
	usartWriteChar('\n');

	usartWriteString(str4);
	usartWriteString(" = ");
	usartWriteInt8(v4);
	usartWriteChar('\n');

	usartWriteString(str5);
	usartWriteString(" = ");
	usartWriteInt8(v5);
	usartWriteChar('\n');

	usartWriteString(str6);
	usartWriteString(" = ");
	usartWriteInt8(v6);
	usartWriteChar('\n');
}
