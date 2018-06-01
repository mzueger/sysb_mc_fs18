/*
 * Aufgabe 8.2
 * 
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <stdint.h>
#include <usart.h>
#include <adc.h>

int16_t counter = 0;

ISR(TIMER0_COMPA_vect) {
    counter ++;
    if(counter >= 5000) {
        int16_t v = adcRead();
        float r = 330.0 * ((1023.0 / v) - 1);
        float t = -1;
        
        if(r >= 1248.0 && r < 1665.0) { // -5...0°C
            t = (r - 1665.0) / (1248.0 - 1665.0) * 5 - 5.0;
        }
        else if(r >= 942.3 && r < 1248.0) { // 0...5°C
            t = (r - 1248.0) / (942.3 - 1248.0) * 5 + 0.0;
        }
        else if(r >= 717.1 && r < 942.3) { // 5...10°C
            t = (r - 942.3) / (717.1 - 942.3) * 5 + 5.0;
        }
        else if(r >= 549.8 && r < 717.1) { // 10...15°C
            t = (r - 717.1) / (549.8 - 717.1) * 5 + 10.0;
        }
        else if(r >= 424.5 && r < 549.8) { // 15...20°C
            t = (r - 549.8) / (424.5 - 549.8) * 5 + 15.0;
        }
        else if(r >= 330.0 && r < 424.5) { // 20...25°C
            t = (r - 424.5) / (330.0 - 424.5) * 5 + 20.0;
        }
        else if(r >= 258.2 && r < 330.0) { // 25...30°C
            t = (r - 330.0) / (258.2 - 330.0) * 5 + 25.0;
        }
        else if(r >= 203.4 && r < 258.2) { // 30... 35°C
            t = (r - 258.2) / (203.4 - 258.2) * 5 + 30.0;
        }
        else if(r >= 258.2 && r < 161.1) { // 35...40°C
            t = (r - 161.1) / (258.2 - 161.1) * 5 + 35.0;
        }
        
        if(t > 0) {
            usartWriteString("Temperature: ");
            int16_t t1 = (int16_t)t;
            int16_t t2 = (int16_t)((t - t1 + 0.005) * 100);
            
            usartWriteInt16(t1);
            usartWriteString(".");
            usartWriteInt16(t2);
            usartWriteString("°C)\n");
        }
        else {
            usartWriteString("Temperature out of range (");
            usartWriteInt16(v);
            usartWriteString(" -> ");
            usartWriteInt16((int16_t)((r + 0.0005) * 1000));
            usartWriteString(" mOhm)\n");
        }
        counter = 0;
    }
}

int main(void) {
    
    clock_prescale_set(clock_div_1);     // 8 MHz clock

    usartInit96008N1();
    adcInit(0);

    TCCR0A = 0x00;
    TCCR0B = 0x00;
    TCNT0 = 0;
    TCCR0A |= 0x2;
    OCR0A = 125;
    TIMSK0 |= (1 << OCIE0A);
    SREG |= 0x80;
    TCCR0B |= 0x03;

    while(1) { }

    return 0;
}
