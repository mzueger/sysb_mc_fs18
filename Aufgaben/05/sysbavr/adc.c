/*
 * adc.c
 *
 *  SysB Mikrocontroller Treiber ADC
 */

#include <avr/io.h>
#include <adc.h>

void adcInit(int8_t channel) {
    if(channel < 0 || channel > 13 || channel == 2 || channel == 3) return;
    
    ADCSRA = 0;
    ADCSRB = 0;
    
    ADMUX = channel & 0x07;
    if(channel >= 8) ADCSRB |= 1 << MUX5;
    ADMUX |= 1 << REFS0;    // AVCC
    ADMUX &= ~(1 << REFS1);
    
    ADCSRA |= (1 << ADEN); // enable
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1); // div64
    
    if(channel < 8) DIDR0 |= 1 << channel;
    else DIDR2 |= 1 << (channel - 8);
}

uint16_t adcRead() {
    ADCSRA |= (1 << ADSC);
    while(!(ADCSRA & (1 << ADIF)));
    return (uint16_t)ADCL + (uint16_t)(ADCH << 8);
}
