/**********************
 * Aufgabe 3.4        *
 * Tastenzähler RS232 * 
 * Einfache Lösung    *
 **********************/

#include <avr/io.h>
#include <avr/power.h>

/**
 * Alle vier LEDs initialisieren
 */
void ledInitAll() {
    DDRB = DDRB | (1 << DDB0); // LED 1 -> Pin B0 als Ausgang konfigurieren
    DDRB = DDRB | (1 << DDB1); // LED 2 -> Pin B1 als Ausgang konfigurieren
    DDRB = DDRB | (1 << DDB2); // LED 3 -> Pin B2 als Ausgang konfigurieren
    DDRB = DDRB | (1 << DDB3); // LED 4 -> Pin B3 als Ausgang konfigurieren
}

/**
 * Taster S1 initialisieren
 */
void buttonInit() {
    DDRD &= ~(1 << DDD4); // Switch S1 -> PD4 als Eingang konfigurieren
}

/**
 * USART1 initialisieren mit
 * - 19200 baud
 * - 8 Data Bits
 * - 1 Stop Bit
 * - Kein Paritätsbit
 */
void usartInit() {
    UBRR1 = 25;                              // 19200 Baud (bei fosc = 8 MHz)
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

/**
 * Einzelnes Zeichen über USART1 ausgeben
 */
void usartWriteChar(char c) {
    while((UCSR1A & (1 << UDRE1)) == 0) {
        // UDRE1 = 0 bedeutet es sind noch
        // Daten im Ausgangsbuffer.
        // Daher nichts tun bis UDRE1 = 1
    }
    UDR1 = c; // Zeichen in den Ausgangsbuffer schreiben
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
    clock_prescale_set(clock_div_1);      // Clock prescaler auf 1 setzen -> 8 MHz
    ledInitAll();                         // LEDs initialisieren
    buttonInit();                         // Button S1 initialisieren
    usartInit();                          // USART1 initialisieren
    
    int8_t wasPressed = 0;                // Benötigte Variablen für Schleife
    int8_t counter = 0;                   // definieren und initialisieren
    while(1) {                            // Endlosschleife
        if((PIND & (1 << PIND4)) == 0) {  // S1 ist gedrückt
            if(wasPressed == 0) {         // Wenn vorhin nicht gedrückt,
                counter++;                // dann Zähler erhöhen
                PORTB = (PORTB & 0xF0) |  // Ausgabe der minderwertigsten 4 Bits
                        (counter & 0x0F); // der counter Variable auf LEDs
                usartWriteInt8(counter);  // Ausgabe von counter über USART
                usartWriteChar('\n');     // mit zusätzlichem Zeilenumbruch
            }
            wasPressed = 1;               // Merken für nächsten Durchgang
        }
        else {                            // S1 ist nicht gedrückt
            wasPressed = 0;               // Merken für nächsten Durchgang
        }
    }

    return 0;
}
