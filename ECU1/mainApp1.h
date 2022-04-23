 /******************************************************************************
 *File Name: mainApp1.h
 *
 * Description: Header file for the main application functions of the first MCU
 *
 * Author: Hussam Eldin Wael
 *
 *******************************************************************************/

#ifndef MAINAPP1_H_
#define MAINAPP1_H_

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
 * Sends the password to MCU2 using UART.
 */
void sendPassword(uint8 *pass);


/*
 * Description :
 * Asks for the new password and re-entering it correctly.
 * If both passwords match, it sends the password to MCU2.
 * If they don't, The operation is repeated until Password Match.
 */
void setPassword(void);


/*
 * Description :
 * Asks for the system password with a maximum of three times.
 * Sends the password to MCU2 and waits for validation.
 * returns the result of operation (either SUCCESS or FAILURE).
 */
uint8 validatePassword(void);


/*
 * Description :
 * Displays the options for the user.
 * returns the command entered by the user.
 */

uint8 DisplayMenu();


/*
 * Description :
 * Displays : -Door Unlocking for DOOR_UNLOCKING_TIME
 * 			  -Door Open for DOOR_PAUSE_TIME
 * 			  -Door Locking for DOOR_LOCKING_TIME
 */

void System_Unlock(void);

/*
 * Description :
 * Displays ALERT!! for BLOCKING_SYSTEM_TIME.
 */

void System_Block(void);

#endif /* MAINAPP1_H_ */
