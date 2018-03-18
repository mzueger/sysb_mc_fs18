// Aufgabe 4.1

#include <avr/io.h>
#include <avr/power.h>

void usartInit() {
    UBRR1 = 51;                              // 9600 Baud (bei fosc = 8 MHz)
    UCSR1B |= 1 << TXEN1;                    // Transmitter aktivieren
    UCSR1B |= 1 << RXEN1;                    // Receiver aktivieren
    UCSR1C |= (1 << UCSZ11) | (1 << UCSZ10); // 8 Data Bits (dazu müssen UCSZ10 und UCSZ11 gesetzt,
    UCSR1B &= ~(1 << UCSZ12);                // und UCSZ12 gelöscht werden)
    UCSR1C &= ~(1 << USBS1);                 // 1 Stop Bit

    char dummy;
    while(UCSR1A & (1 << RXC1)) {            // Eingangsbuffer leeren:
        dummy = UDR1;                        // solange lesen bis nichts mehr da ist
    }
}

void usartWriteChar(char c) {
    while((UCSR1A & (1 << UDRE1)) == 0) {
        // UDRE1 = 0 bedeutet es sind noch
        // Daten im Ausgangsbuffer.
        // Daher nichts tun bis UDRE1 = 1
    }
    UDR1 = c; // Zeichen in den Ausgangsbuffer schreiben
}

void usartWriteString(const char string[]) {
    char i = 0;
    while(string[i] != '\0') {
        usartWriteChar(string[i++]);
    }
}

int main(void){
    clock_prescale_set(clock_div_1); // set the system clock prescaler to 1 (8MHz)
    usartInit();
    
    usartWriteString("Hello, NTB");

    return 0;
}
