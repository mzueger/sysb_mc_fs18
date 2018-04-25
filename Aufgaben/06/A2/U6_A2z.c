// Aufgabe 6.2
// (modifiziert für nur einen Schalter)

#include <avr/interrupt.h>
#include <led.h>
#include <button.h>

ISR(INT1_vect){
    ledToggle(LED_2);
}

int main(void){
    buttonInit(BUTTON_EXT); // Externen Taster initialisieren
    
    ledInit(LED_2);         // LED_2 initialisieren
    
    EICRA |= ~(1 << ISC10); // INT1 reagiert nur auf fallende Flanke
    EICRA |= 1 << ISC11;
    
    EIMSK |= 1 << INT1;     // Interrupt INT1 (BUTTON_EXT) aktivieren
    
    SREG |= 0x80;           // Interrupts global aktivieren
    
    while(1) { }            // main() muss aktiv bleiben -> leere Endlosschleife
    
    return 0;
}
