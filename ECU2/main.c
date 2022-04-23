/*
 * main.c
 *
 *  Created on: Oct 5, 2021
 *      Author: Hussam Eldin Wael
 */



#define F_CPU 8000000

#include "mainApp2.h"
#include "util/delay.h"
#include "UART.h"


volatile uint8 received_pass[PASSWORD_SIZE] = {0}  ;


int main(void) {

	uint8 order ;

	System_init();

	/*Store the first password in EEPROM*/
	while(UART_receiveByte()!= MCU_READY);
	UART_receiveByte();
	receivePassword(received_pass);
	storePassword(0x311 , received_pass);

	while(1) {
		/*Wait for the ready signal*/
		while(UART_receiveByte()!= MCU_READY);
		order = UART_receiveByte();

		/*Perform the operation sent by the other MCU*/

		if(order == CHECK_PASSWORD) {
			receivePassword(received_pass);
			SendPasswordConfirmation(received_pass);
		}

		else if(order == UNLOCK_THE_SYSTEM) {

			System_Unlock();

		}

		else if(order == BLOCK_THE_SYSTEM) {

			System_Block();
		}

		else if(order == CHANGE_PASSWORD) {
			receivePassword(received_pass);
			storePassword(0x311 , received_pass);
		}
	}


	return 0 ;
}
