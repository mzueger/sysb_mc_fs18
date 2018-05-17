#ifndef PWM_H_
#define PWM_H_

/**********************************************************
 * SysB: Mikrocontroller                                  *
 *                                                        *
 * Driver for PWM output with Timer1                      *
 *                                                        *
 **********************************************************/

#include <stdint.h>

void pwmInitOC1A(uint16_t period, uint16_t hightime);
void pwmUpdateOC1A(uint16_t period, uint16_t hightime);

#endif /* PWM_H_ */
