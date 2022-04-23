/******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.c
 *
 * Description: Source file for the buzzer driver
 *
 * Author: Hussam Eldin Wael
 *
 *******************************************************************************/


#include "buzzer.h"

/*
 * Description :
 * Initializes the Buzzer according to the configuration.
 */
void BUZZER_init(){

GPIO_setupPinDirection(BUZZER_PORT_ID ,BUZZER_PIN_ID , PIN_OUTPUT);
}


/*
 * Description :
 * Turns the Buzzer On.
 */
void BUZZER_ON(){
	GPIO_writePin(BUZZER_PORT_ID , BUZZER_PIN_ID , LOGIC_HIGH);
}


/*
 * Description :
 * Turns the Buzzer Off.
 */
void BUZZER_OFF(){
	GPIO_writePin(BUZZER_PORT_ID , BUZZER_PIN_ID , LOGIC_LOW);
}


