/*
 * main.c
 *
 *  Created on: Oct 5, 2021
 *      Author: Hussam Eldin Wael
 */
#define F_CPU 8000000

#include "util/delay.h"
#include"mainApp1.h"
#include "LCD.h"
#include "avr/io.h"
#include "uart.h"
#define EnableInterrupts() SREG|=1<<7 ;


int main(void) {

	/*Modules Initialization*/
	UART_configType uart = {DISABLED , 9600 , EIGHT , 1};
	UART_init(&uart);

	EnableInterrupts();
	LCD_init();

	/*Set Password*/
	setPassword();

	while(1) {

		uint8 order = DisplayMenu();

		uint8 operation = validatePassword();

		if(operation == FAILURE) {

			UART_sendByte(MCU_READY);

			UART_sendByte(BLOCK_THE_SYSTEM);

			System_Block();

			continue ;
		}


		switch(order) {

		case CHANGE_PASSWORD :

			setPassword();

			break ;

		case UNLOCK_THE_SYSTEM:

			UART_sendByte(MCU_READY);

			UART_sendByte(UNLOCK_THE_SYSTEM);

			System_Unlock();

			break;

		}

	}

	return 0 ;
}

