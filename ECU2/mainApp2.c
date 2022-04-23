
#define F_CPU 8000000
#include "timer0.h"
#include "mainApp2.h"
#include "DcMotor.h"
#include "buzzer.h"
#include "external_eeprom.h"
#include "util/delay.h"
#include "uart.h"
#include "Macros.h"

static Timer0_configType timer0 = {COMPARE_MODE , F_CPU_1024, 0 , 194} ;
volatile uint8 state = 0 ;
volatile uint16 g_count = 0 ;


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description :
 * Receives a password using UART in an array.
 */
void receivePassword(uint8 *pass) {

	for(uint8 i = 0 ; i < PASSWORD_SIZE ; i++) {

		pass[i] = UART_receiveByte();
	}

}



/*
 * Description :
 * Stores the password in EEPROM to a specific address.
 */
void storePassword(uint16 address , uint8 *pass) {

	for(uint8 i = 0 ; i < PASSWORD_SIZE ; i++) {

		EEPROM_writeByte(address + i, pass[i]);
		_delay_ms(10);

	}

}


/*
 * Description :
 * Reads the password from EEPROM from a specific address.
 */
void retrievePassword(uint16 address , uint8 *pass) {

	for(uint8 i = 0 ; i < PASSWORD_SIZE ; i++) {

		EEPROM_readByte(address + i, pass+i);
		_delay_ms(10);

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
 * 1-Reads the password from EEPROM.
 * 2-Compares it to the password received by UART.
 * 3-Sends the validity of the Password using UART. (PASSWORD_MATCH or PASSWORD_MISMATCH)
 */
void SendPasswordConfirmation(uint8 *pass) {

	uint8 memory_pass[PASSWORD_SIZE];

	retrievePassword(0x311, memory_pass);

	uint8 check = checkPassword(memory_pass, pass);

	UART_sendByte(check);

}

/***********************Call Back Functions*************************/


void UnlockDoorCallBack(void) {
	g_count++ ;

	if(g_count == 40*DOOR_UNLOCKING_TIME) {

		DcMotor_rotate(STOP);
		g_count = 0 ;
		Timer0_deInit();
		state = 1 ;

	}

}


void PauseCallBack(void) {
	g_count++ ;

	if(g_count == 40 * DOOR_PAUSE_TIME) {

		Timer0_deInit();
		g_count = 0 ;

		DcMotor_rotate(CLOCKWISE);


		state = 1 ;
	}

}



void LockDoorCallBack(void) {

	g_count++ ;
	if(g_count == 40*DOOR_LOCKING_TIME) {

		Timer0_deInit();
		DcMotor_rotate(STOP);
		g_count = 0 ;

		state = 1;
	}

}



void SystemBlockingCallBack(void) {

	g_count++ ;

	if(g_count == 40*BLOCKING_SYSTEM_TIME) {


		Timer0_deInit() ;
		g_count = 0 ;

		state = 1 ;

	}


}

/*
 * Description :
 * Initializes the System Modules.
 */

void System_init(void) {
	UART_configType uart = {DISABLED , 9600 , EIGHT , 1};
	UART_init(&uart);
	EnableInterrupts();
	EEPROM_init();
	DcMotor_init();
	BUZZER_init();

}


/*
 * Description :
 * 1- Motor Rotates Clockwise for DOOR_UNLOCKING_TIME.
 * 2- Motor stops for DOOR_PAUSE_TIME.
 * 3- Motor rotates Anti-clockwise for DOOR_LOCKING_TIME.
 */
void System_Unlock(void) {

	DcMotor_rotate(ANTI_CLOCKWISE);

	Timer0_setCallBack(UnlockDoorCallBack);
	Timer0_init(&timer0);
	while(state == 0) ;

	state = 0 ;
	Timer0_setCallBack(PauseCallBack);
	Timer0_init(&timer0);
	while(state == 0) ;

	state = 0 ;
	Timer0_setCallBack(LockDoorCallBack);
	Timer0_init(&timer0);
	while(state == 0) ;

	state = 0;
}


/*
 * Description :
 * Buzzer is On for BLOCKING_SYSTEM_TIME.
 */
void System_Block(void) {

	BUZZER_ON();

	Timer0_setCallBack(SystemBlockingCallBack);
	Timer0_init(&timer0);

	while(state == 0);

	BUZZER_OFF();
	state = 0 ;
}


