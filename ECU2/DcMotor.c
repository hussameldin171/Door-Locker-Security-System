/******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: DcMotor.c
 *
 * Description: Source file for the DC Motor driver
 *
 * Author: Hussam Eldin Wael
 *
 *******************************************************************************/
#include "DcMotor.h"


/*
 * Description :
 * Initializes the DC Motor at the configured pins.
 * The initial state of the motor is OFF.
 */
void DcMotor_init(void){

	/*Initialize Motor Pins as Output pins*/
	GPIO_setupPinDirection(DC_MOTOR_PORT , DC_MOTOR_PIN1 ,PIN_OUTPUT );
	GPIO_setupPinDirection(DC_MOTOR_PORT , DC_MOTOR_PIN2 ,PIN_OUTPUT );

	/*The motor's initial state is set to be OFF*/
	GPIO_writePin(DC_MOTOR_PORT , DC_MOTOR_PIN1 ,LOGIC_LOW );
	GPIO_writePin(DC_MOTOR_PORT , DC_MOTOR_PIN2 ,LOGIC_LOW );


}


void DcMotor_rotate(DcMotor_state state){

	/*set the motor's state*/
	switch(state){

	/* Case 1 : The motor is stopped */
	case STOP:
		GPIO_writePin(DC_MOTOR_PORT , DC_MOTOR_PIN1 ,LOGIC_LOW );
		GPIO_writePin(DC_MOTOR_PORT , DC_MOTOR_PIN2 ,LOGIC_LOW );
		break ;

		/* Case 2 : The motor rotates clockwise */
	case CLOCKWISE:
		GPIO_writePin(DC_MOTOR_PORT , DC_MOTOR_PIN1 ,LOGIC_LOW );
		GPIO_writePin(DC_MOTOR_PORT , DC_MOTOR_PIN2 ,LOGIC_HIGH );
		break ;
		/* Case 3 : The motor rotates anti-clockwise */
	case ANTI_CLOCKWISE:
		GPIO_writePin(DC_MOTOR_PORT , DC_MOTOR_PIN1 ,LOGIC_HIGH );
		GPIO_writePin(DC_MOTOR_PORT , DC_MOTOR_PIN2 ,LOGIC_LOW );
		break ;


	}



}



