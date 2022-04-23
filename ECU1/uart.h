 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the AVR UART driver
 *
 * Author: Hussam Eldin Wael
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_


#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum{
	DISABLED , EVEN_PARITY = 2 , ODD_PARITY = 3
}UART_parityMode;

typedef enum{
	FIVE , SIX , SEVEN, EIGHT , NINE = 7
}UART_charSize;

typedef struct{

	UART_parityMode mode ;
	uint32 baud_rate;
	UART_charSize charSize ;
	uint8 stopBits ;

}UART_configType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(UART_configType *a_ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint16 byte);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint16 UART_receiveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(uint8 * str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 * str); // Receive until #



#endif /* UART_H_ */
