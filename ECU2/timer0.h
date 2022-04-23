 /******************************************************************************
 *
 * Module: Timer0
 *
 * File Name: timer0.h
 *
 * Description: Header file for the AVR Timer0 driver
 *
 * Author: Hussam Eldin Wael
 *
 *******************************************************************************/
#ifndef TIMER0_H_
#define TIMER0_H_


#include "std_types.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum {

	NORMAL_MODE , COMPARE_MODE

}Timer0_Mode;

typedef enum {

	NO_CLOCK , F_CPU_1 , F_CPU_8 , F_CPU_64 , F_CPU_256 , F_CPU_1024

}Timer0_prescaler;


typedef struct{
	Timer0_Mode mode ;
	Timer0_prescaler prescaler;
	uint8 initial_value ;
	uint8 compare_value ;
}Timer0_configType;


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Initializes Timer0 according to the desired configuration:
 * Configures the mode : Normal Mode or Compare Mode.
 * Sets the pre-scaler value , initial timer value , and compare value.
 */
void Timer0_init(Timer0_configType *ptr);


/*
 * Description :
 * Sets the Call Back Function of the timer.
 */
void Timer0_setCallBack(void (*ptr)(void) ) ;

/*
 * Description :
 * Turns the timer off and returns to its default state.
 */
void Timer0_deInit(void);

#endif /* TIMER0_H_ */
