
#define F_CPU 8000000
#include "mainApp1.h"
#include "std_types.h"
#include "LCD.h"
#include "uart.h"
#include "keypad.h"
#include "util/delay.h"
#include "timer0.h"


static Timer0_configType timer0 = {COMPARE_MODE , F_CPU_1024, 0 , 194} ;
static volatile uint16 g_count = 0;
static volatile uint8 state = 0 ;


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Sends the password to MCU2 using UART.
 */
void sendPassword(uint8 *pass) {

	for(uint8 i = 0 ;i < PASSWORD_SIZE ;i++) {
		UART_sendByte(pass[i]);
		_delay_ms(1);
	}

}



/*
 * Description :
 * Compares 2 passwords two check if they are the same.
 */
static uint8 checkPassword(uint8 *real_pass , uint8 *entered_pass) {

	for(uint8 i = 0 ; i  < PASSWORD_SIZE ; i++) {

		if(real_pass[i] != entered_pass[i])

			return PASSWORD_MISMATCH ;

	}
	return PASSWORD_MATCH ;
}


/*
 * Description :
 * Stores the input password in the array passed as an argument.
 */

 static void getPasswordFromKeypad(uint8 *pass) {

	for(uint8 i = 0 ; i < PASSWORD_SIZE ; i++) {

		pass[i] = KEYPAD_getPressedKey();
		LCD_displayCharacter('*');
		_delay_ms(500);
	}

	while(KEYPAD_getPressedKey() != '=');
	_delay_ms(500);
}




 /*
  * Description :
  * Asks for the new password and re-entering it correctly.
  * If both passwords match, it sends the password to MCU2.
  * If they don't, The operation is repeated until Password Match.
  */
 void setPassword(void) {

	uint8 check;

	uint8 first_pass[PASSWORD_SIZE] ;
	uint8 second_pass[PASSWORD_SIZE] ;

	while(1) {

		/*Get the first Password*/
		LCD_displayStringRowColumn(0,0,"Please Set a Password:");
		LCD_moveCursor(1,0);

		getPasswordFromKeypad(first_pass);
		LCD_clearScreen();

		/*Get the second Password*/
		LCD_displayStringRowColumn(0,0,"Please Re-enter Password:");
		LCD_moveCursor(1,0);
		getPasswordFromKeypad(second_pass);

		/*Compare the two passwords*/
		check = checkPassword( first_pass, second_pass);

		if(check == PASSWORD_MATCH) {

			break ;
		}

		/*Case Mismatch*/
		LCD_clearScreen();
		LCD_displayStringRowColumn(0 , 12,"MISMATCH!");
		_delay_ms(500);
		LCD_clearScreen();
	}

	/*Case Match*/
	LCD_clearScreen();
	LCD_displayString("SUCCESS");
	_delay_ms(500);
	LCD_clearScreen();

	/*Send Password to MCU2*/
	UART_sendByte(MCU_READY);
	_delay_ms(1);
	UART_sendByte(CHANGE_PASSWORD);
	_delay_ms(1);
	sendPassword(first_pass);
}




 /*
  * Description :
  * Asks for the system password with a maximum of three times.
  * Sends the password to MCU2 and waits for validation.
  * returns the result of operation (either SUCCESS or FAILURE).
  */

uint8 validatePassword(void) {

	uint8 check;
	uint8 count = 0 ;

	uint8 real_pass[PASSWORD_SIZE] ;
	uint8 entered_pass[PASSWORD_SIZE];


	do{
		/*Get Password from the user*/
		LCD_displayStringRowColumn(0,0,"Please Enter Password:");
		LCD_moveCursor(1,0);

		getPasswordFromKeypad(entered_pass);

		/*Send Password to MCU2*/
		UART_sendByte(MCU_READY);
		_delay_ms(1);
		UART_sendByte(CHECK_PASSWORD);
		_delay_ms(1);
		sendPassword(entered_pass);
		_delay_ms(1);

		/*Receive Password Validation from MCU2*/
		check = UART_receiveByte();

		if(check == PASSWORD_MATCH) {
			LCD_clearScreen();
			return SUCCESS ;
		}

		count++;

		LCD_clearScreen();
		LCD_displayStringRowColumn(0 , 12,"MISMATCH!");
		_delay_ms(500);
		LCD_clearScreen();



	}while(count<3);

	return FAILURE ;

}

/*
 * Description :
 * Displays the options for the user.
 * returns the command entered by the user.
 */
uint8 DisplayMenu() {

	uint8 command ;
	while(1) {


		LCD_displayStringRowColumn(0, 0, "+: Change Password");
		LCD_displayStringRowColumn(1, 0, "-: Unlock The System");

		command = KEYPAD_getPressedKey();

		switch(command) {

		case '+':
			while(KEYPAD_getPressedKey() != '=');
			_delay_ms(500);
			LCD_clearScreen();
			return CHANGE_PASSWORD ;

		case '-':
			while(KEYPAD_getPressedKey() != '=');
			_delay_ms(500);
			LCD_clearScreen();
			return UNLOCK_THE_SYSTEM;

		}
	}
}

/***********************Call Back Functions*************************/


static void UnlockDoorCallBack(void) {
	g_count++ ;

	if(g_count == 40*DOOR_UNLOCKING_TIME) {

		Timer0_deInit();
		LCD_clearScreen();
		LCD_displayString("Door Open");
		g_count = 0 ;
		state = 1 ;

	}

}


static void PauseCallBack(void) {
	g_count++ ;

	if(g_count == 40 * DOOR_PAUSE_TIME) {

		Timer0_deInit();
		g_count = 0 ;
		LCD_clearScreen();
		LCD_displayString("Door Locking...");


		state = 1 ;
	}

}



static void LockDoorCallBack(void) {

	g_count++ ;
	if(g_count == 40*DOOR_LOCKING_TIME) {

		Timer0_deInit();
		LCD_clearScreen();
		g_count = 0 ;

		state = 1;
	}

}



static void SystemBlockingCallBack(void) {

	g_count++ ;

	if(g_count == 40*BLOCKING_SYSTEM_TIME) {

		LCD_clearScreen();
		Timer0_deInit() ;
		g_count = 0 ;

		state = 1 ;

	}


}

/***********************************************************/
/*
 * Description :
 * Displays : -Door Unlocking for DOOR_UNLOCKING_TIME
 * 			  -Door Open for DOOR_PAUSE_TIME
 * 			  -Door Locking for DOOR_LOCKING_TIME
 */
void System_Unlock() {

	LCD_clearScreen();
	LCD_displayString("Door Unlocking...");

	state = 0 ;
	Timer0_setCallBack(UnlockDoorCallBack);
	Timer0_init(&timer0);
	while(state == 0);

	state = 0 ;
	Timer0_setCallBack(PauseCallBack);
	Timer0_init(&timer0);
	while(state == 0);

	state = 0 ;
	Timer0_setCallBack(LockDoorCallBack);
	Timer0_init(&timer0);
	while(state == 0);

	LCD_clearScreen();
	state = 0;
}

/*
 * Description :
 * Displays ALERT!! for BLOCKING_SYSTEM_TIME.
 */
void System_Block(void){


	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 12, "ALERT!!!");

	state = 0 ;
	Timer0_setCallBack(SystemBlockingCallBack);
	Timer0_init(&timer0);
	while(state == 0);
	state = 0 ;

}



