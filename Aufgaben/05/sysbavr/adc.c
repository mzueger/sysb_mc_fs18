/*
 * adc.c
 *
 *  SysB Mikrocontroller Treiber ADC
 */

#include <avr/io.h>
#include <adc.h>

void adcInit(int8_t channel) {
    if(channel < 0 || channel > 13 ||
       channel == 2 || channel == 3) return;

    ADMUX = channel < 8 ? channel : channel + 24;
    ADMUX |= (1 << REFS1) | (1 << REFS0);

    ADCSRA = 0;
    ADCSRA |= (1 << ADEN);
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1); // div64
    ADCSRB = 0;

    if(channel < 8) DIDR0 = 1 << channel;
    else DIDR1 = 1 << (channel - 8);
}

uint16_t adcRead(void) {
    ADCSRA |= (1 << ADSC);
    while(!(ADCSRA & (1 << ADIF)));
    return (uint16_t)ADCL + (uint16_t)(ADCH << 8);
}
