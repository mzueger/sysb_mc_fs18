/*
 * adc.h
 *
 *  Created on: 24.05.2018
 *      Author: Andreas
 */

#ifndef INCLUDE_ADC_H_
#define INCLUDE_ADC_H_

void adcInit(int8_t channel);

uint16_t adcRead(void);

#endif /* INCLUDE_ADC_H_ */
