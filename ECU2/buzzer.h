 /******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.h
 *
 * Description: Header file for the buzzer driver
 *
 * Author: Hussam Eldin Wael
 *
 *******************************************************************************/
#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"
#include "gpio.h"


/*******************************************************************************
 *                            Definitions                                      *
 *******************************************************************************/

#define BUZZER_PORT_ID    	PORTA_ID
#define BUZZER_PIN_ID		PIN2_ID


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


/*
 * Description :
 * Initializes the Buzzer according to the configuration.
 */
void BUZZER_init(void);

/*
 * Description :
 * Turns the Buzzer On.
 */
void BUZZER_ON(void);

/*
 * Description :
 * Turns the Buzzer Off.
 */
void BUZZER_OFF(void);




#endif /* BUZZER_H_ */
