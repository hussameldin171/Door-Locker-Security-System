/******************************************************************************
 *
 * Module: DC Motor
 *
 * File Name: DcMotor.h
 *
 * Description: Header file for the DC Motor driver
 *
 * Author: Hussam Eldin Wael
 *
 *******************************************************************************/
#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include "std_types.h"
#include "gpio.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define DC_MOTOR_PORT	PORTA_ID
#define DC_MOTOR_PIN1	PIN0_ID
#define DC_MOTOR_PIN2	PIN1_ID


/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum{
	STOP , CLOCKWISE , ANTI_CLOCKWISE

}DcMotor_state;


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Initializes the DC Motor at the configured pins.
 * The initial state of the motor is OFF.
 */
void DcMotor_init(void);

/*
 * Description :
 * Rotates the motor whether Clockwise , Anti-clockwise , or stops it.
 * Sets the speed of the motor according to the passed argument.
 */
void DcMotor_rotate(DcMotor_state state);


#endif /* DCMOTOR_H_ */
