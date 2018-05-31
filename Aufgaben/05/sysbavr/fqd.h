/***************************************************************		           *
 * SysB Mikrocontroller
 *
 * FQD driver source code	                                   *
 *                                                    		   *
 **************************************************************/

#ifndef INCLUDE_FQD_H_
#define INCLUDE_FQD_H_

#define ENC_A 	0
#define ENC_B 	1

/**
 * Init FQD on Pin PD0 (ENC_A) and PD1 (ENC_B)
 */
void fqdInit(void);

/**
 * Get Value of ENC_A
 * @return	value of ENC_A
 */
int8_t fqdGetA(void);

/**
 * Get Value of ENC_B
 * @return value of ENC_B
 */
int8_t fqdGetB(void);

/**
 * Get counter value of FQD
 * @return counter value
 */
int16_t fqdGetCounter();

#endif /* INCLUDE_FQD_H_ */
