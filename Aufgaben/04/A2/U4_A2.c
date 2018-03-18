// Aufgabe 4.2

#include <avr/io.h>
#include <avr/power.h>

#define MAX_LENGTH 80

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

char usartReadChar() {
    while((UCSR1A & (1 << RXC1)) == 0); // wait until RXC1 bit is set (data ready)
    uint8_t receivedByte = UDR1;        // read data
    return receivedByte;
}

int8_t usartReadLine(char string[], int8_t maxLength) {
    int8_t i = 0;
    while(i < maxLength - 1) {       // Ein Zeichen wird noch für '\0' benötigt
        char c = usartReadChar();    // Zeichen lesen
        if(c == '\r' || c == '\n') { // Wenn Zeilenumbruch gelesen wurde,
                break;               // dann Schleife abbrechen
        }
        else {                       // Ansonsten
            string[i] = c;           // Zeichen in String kopieren
            i++;                     // und Laufvariable erhöhen
        }
    }
    string[i] = '\0';                // String-Terminierungszeichen anfügen
    return i;                        // Anzahl gelesener Zeichen zurückgeben
}

int main(){
    clock_prescale_set(clock_div_1); // System clock prescaler auf 1 setzen
    usartInit();                     // USART1 initialisieren
    
    char line[MAX_LENGTH];           // Zwischenspeicher für Zeile
    usartReadLine(line, MAX_LENGTH); // Zeile lesen
    usartWriteString(line);          // Gelesene Zeile wieder ausgeben
    usartWriteChar('\n');            // Zeilenumbruch anfügen

    return 0;
}
