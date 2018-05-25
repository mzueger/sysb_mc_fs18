// Aufgabe 6.3
// (modifiziert für nur einen Schalter)

#include <avr/interrupt.h>
#include <led.h>
#include <button.h>

ISR(INT1_vect){
    static uint8_t ctr = 0;
    ctr++;
    if(ctr % 10 == 0) {
        usartWriteInt8(ctr);
        usartWriteByte('\n');
    }
}

int main(void){
	clock_prescale_set(clock_div_1);	// clock auf 8MHz
	
    buttonInit(BUTTON_EXT); // Externen Taster initialisieren
    
    usartInit96008N1();     // RS232-Schnittstelle initialisieren
    usartWriteString("Ready");
    
    EICRA |= ~(1 << ISC10); // INT1 reagiert nur auf fallende Flanke
    EICRA |= 1 << ISC11;
    
    EIMSK |= 1 << INT1;     // Interrupt INT1 (BUTTON_EXT) aktivieren
    
    SREG |= 0x80;           // Interrupts global aktivieren
    
    while(1) { }            // main() muss aktiv bleiben -> leere Endlosschleife
    
    return 0;
}
