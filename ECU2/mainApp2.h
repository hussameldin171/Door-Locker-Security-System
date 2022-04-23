/******************************************************************************
 *File Name: mainApp1.h
 *
 * Description: Header file for the main application functions of the second MCU
 *
 * Author: Hussam Eldin Wael
 *
 *******************************************************************************/

#ifndef MAINAPP2_H_
#define MAINAPP2_H_

#include "std_types.h"


/*******************************************************************************
 *                            Definitions                                      *
 *******************************************************************************/
#define MCU_READY             0xE1

#define SUCCESS				  1
#define FAILURE 		      0

#define CHECK_PASSWORD		  0xA8
#define PASSWORD_MATCH		  0xA3
#define PASSWORD_MISMATCH     0xA2

#define PASSWORD_SIZE	      0x05
#define READ_PASSWORD         0xB0

#define CHANGE_PASSWORD		  0xC2
#define UNLOCK_THE_SYSTEM	  0xC4
#define BLOCK_THE_SYSTEM	  0xC6

#define DOOR_LOCKING_TIME       5
#define DOOR_UNLOCKING_TIME     5
#define DOOR_PAUSE_TIME         3
#define BLOCKING_SYSTEM_TIME	5


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


/*
 * Description :
 * Initializes the System Modules.
 */
void System_init(void) ;

/*
 * Description :
 * 1- Motor Rotates Clockwise for DOOR_UNLOCKING_TIME.
 * 2- Motor stops for DOOR_PAUSE_TIME.
 * 3- Motor rotates Anti-clockwise for DOOR_LOCKING_TIME.
 */
void System_Unlock(void);

/*
 * Description :
 * Buzzer is On for BLOCKING_SYSTEM_TIME.
 */
void System_Block(void);

/*
 * Description :
 * Receives a password using UART in an array.
 */
void receivePassword(uint8 *pass);

/*
 * Description :
 * Stores the password in EEPROM to a specific address.
 */
void storePassword(uint16 address , uint8 *pass);

/*
 * Description :
 * Reads the password from EEPROM from a specific address.
 */
void retrievePassword(uint16 address , uint8 *pass);

/*
 * Description :
 * 1-Reads the password from EEPROM.
 * 2-Compares it to the password received by UART.
 * 3-Sends the validity of the Password using UART. (PASSWORD_MATCH or PASSWORD_MISMATCH)
 */
void SendPasswordConfirmation(uint8 *pass);



#endif /* MAINAPP2_H_ */
