#include <avr/interrupt.h>
#include <led.h>
#include <button.h>

ISR(INT1_vect){
    if(buttonGet(BUTTON_EXT) == BUTTON_PRESSED) {
		ledOn(LED_1);
	}
	else {
		ledOff(LED_1);
	}
}

int main(void){
    buttonInit(BUTTON_EXT); // Externen Taster initialisieren
    ledInit(LED_1);         // LED_1 initialisieren
    
    EICRA |= 1 << ISC10;    // INT1 reagiert auf jede Flanke
    EIMSK |= 1 << INT1;     // Interrupt INT1 (BUTTON_EXT) aktivieren
    SREG |= 0x80;           // Interrupts global aktivieren
    while(1) { }            // main() muss aktiv bleiben
    return 0;
}
