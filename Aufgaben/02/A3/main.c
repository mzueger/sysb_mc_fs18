// Aufgabe 2.3

#include <avr/io.h>

int main() {
    
    // Ein- und Ausgänge konfigurieren
    DDRD &= ~(1 << DDD4);      // Switch S1 -> PD4 als Eingang konfigurieren 
    DDRB = DDRB | (1 << DDB0); // LED 1 -> PortB0 als Ausgang konfigurieren
    DDRB = DDRB | (1 << DDB1); // LED 1 -> PortB1 als Ausgang konfigurieren
    DDRB = DDRB | (1 << DDB2); // LED 1 -> PortB2 als Ausgang konfigurieren
    DDRB = DDRB | (1 << DDB3); // LED 1 -> PortB3 als Ausgang konfigurieren
    
    // Variablen definieren und initialisieren
    char wasPressed = 0;
    char counter = 0;

    // Endlos-Schleife
    while(1) {
        if((PIND & (1 << PIND4)) == 0) {  // S1 ist gedrückt
            if(wasPressed == 0) {         // Wenn vorhin nicht gedrückt,
                counter++;                // Zähler erhöhen
                PORTB = (PORTB & 0xF0) |  // Die minderwertigsten 4 Bit
                        (counter & 0x0F); // des Counters ins PORTB
                                          // ins PORTB Register schreiben
            }
            wasPressed = 1;               // Merken für nächsten Durchgang
        }
        else {                            // S1 ist nicht gedrückt
            wasPressed = 0;               // Merken für nächsten Durchgang
        }
    }
    return 0;
}
