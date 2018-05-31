/***************************************************************
 * SysB Mikrocontroller								           *
 *                                                        	   *
 * FQD driver source code	                                   *
 *                                                    		   *
 * Init, FQD source code, uses external Interrupt 0 and 1 for  *
 * counter													   *
 * 															   *
 **************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <fqd.h>

//fqd variables
volatile int16_t counter = 0;
volatile int8_t a_old;
volatile int8_t b_old;

ISR(INT0_vect) {
	if(!a_old) {				//rising edge of a
		if(fqdGetB()) {
			counter++;
		}
		else {
			counter--;
		}
	}
	else {						//falling edge of a
		if(fqdGetB()) {
			counter--;
		}
		else {
			counter++;
		}
	}

	a_old = fqdGetA();
}

ISR(INT1_vect) {
	if(!b_old) {				//rising edge of b
		if(fqdGetA()) {
			counter--;
		}
		else {
			counter++;
		}
	}
	else {						//falling edge of b
		if(fqdGetA()) {
			counter++;
		}
		else {
			counter--;
		}
	}

	b_old = fqdGetB();
}

/**
 * Get Value of ENC_A
 * @return	value of ENC_A
 */
int8_t fqdGetA(void){
	return (PIND & (1 << ENC_A)) == 0;
}

/**
 * Get Value of ENC_B
 * @return value of ENC_B
 */
int8_t fqdGetB(void) {
	return (PIND & (1 << ENC_B)) == 0;
}

/**
 * Init FQD on Pin PE5 (ENC_A) and PE6 (ENC_B)
 */
void fqdInit(void) {
	DDRD &= ~(1 << ENC_A);
	DDRD &= ~(1 << ENC_B);

	EICRB |= (1 << ISC00) | (1 << ISC10);
	EIMSK |= (1 << INT0) | (1 << INT1);
	SREG |= 0x80;

	a_old = fqdGetA();
	b_old = fqdGetB();
}

/**
 * Get counter value of FQD
 * @return counter value
 */
int16_t fqdGetCounter(){
	return counter;
}
