/******************************************************************************
 *
 * Module: Timer0
 *
 * File Name: timer0.c
 *
 * Description: Source file for the AVR Timer0 driver
 *
 * Author: Hussam Eldin Wael
 *
 *******************************************************************************/

#include "std_types.h"
#include "Timer0.h"
#include "Macros.h"
#include "avr/io.h"
#include "avr/interrupt.h"


/*******************************************************************************
 *                            Global Variables                                 *
 *******************************************************************************/

static volatile void (*g_ptr)(void) = NULL_PTR ;

static volatile uint8 ovf_init_value = 0 ;

/*******************************************************************************
 *                        Interrupt Service Routines                           *
 *******************************************************************************/

ISR(TIMER0_COMP_vect) {

	if(g_ptr != NULL_PTR)
		(*g_ptr)();

}


ISR(TIMER0_OVF_vect) {

	TCNT0 = ovf_init_value;
	if(g_ptr != NULL_PTR)
		(*g_ptr)();

}

/*******************************************************************************
 *                             Functions Definitions                           *
 *******************************************************************************/

/*
 * Description :
 * Initializes Timer0 according to the desired configuration:
 * Configures the mode : Normal Mode or Compare Mode.
 * Sets the pre-scaler value , initial timer value , and compare value.
 */

void Timer0_init(Timer0_configType *ptr){

	/*Non PWM Mode*/
	SET_BIT(TCCR0 , FOC0);

	/*Configure Timer0 Mode*/

	CLEAR_BIT(TCCR0 , WGM00);

	if(ptr->mode == COMPARE_MODE)
		SET_BIT(TCCR0 , WGM01);

	else
		CLEAR_BIT(TCCR0 , WGM01);


	/*Configure Clock Select Bits*/

	TCCR0 = (TCCR0 & 0xF8)| (ptr->prescaler);

	/*Set the initial value*/

	TCNT0 = ptr->initial_value ;

	/*Set compare value*/

	OCR0 = ptr->compare_value ;

	/*Enable Timer0 Interrupt*/

	SET_BIT(TIMSK , ptr->mode);

	/*Set ovf init value*/
	ovf_init_value = ptr->initial_value ;
}


/*
 * Description :
 * Sets the Call Back Function of the timer.
 */

void Timer0_setCallBack(void (*a_ptr)(void) ) {

	g_ptr = a_ptr;
}


/*
 * Description :
 * Turns the timer off and returns to its default state.
 */
void Timer0_deInit(void){

	TCCR0 = 0 ;

	TCNT0 = 0 ;

	OCR0  = 0 ;

	TIMSK &= ~0xFC ;
}
