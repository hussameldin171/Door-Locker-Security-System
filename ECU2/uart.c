/******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: Source file for the AVR UART driver
 *
 * Author: Hussam Eldin Wael
 *
 *******************************************************************************/


#include "avr/io.h"
#include "avr/interrupt.h"
#include "uart.h"
#include "Macros.h"


/*******************************************************************************
 *                        Interrupt Service Routines                           *
 *******************************************************************************/
#ifdef INTERRUPT_MODE

static volatile uint16 data ;

ISR(USART_RXC_vect) {

	data = UDR;
}
#endif


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */

void UART_init(UART_configType *a_ptr){

	uint16 ubrr_value = 0;
	/*Double Transmission Speed*/
	UCSRA = (1<<U2X);
	/*Enable UART*/
	UCSRB = (1<<RXEN) | (1<<TXEN);

	/*Enable Interrupt Mode if required*/
#ifdef INTERRUPT_MODE
	SET_BIT(UCSRB , RXCIE);
	SREG |= 1<<7 ;
#endif

	/*Set Character Size and Parity Mode*/
	if(a_ptr->charSize == NINE)
		SET_BIT(UCSRB , UCSZ2);

	UCSRC = (1<<URSEL) | (  ((a_ptr->charSize)&0x03)<<UCSZ0 )|((a_ptr->mode) <<UPM0)  ;



	/*Set the number of Stop Bits*/
	if(a_ptr->stopBits == 2)
		SET_BIT(UCSRC , USBS);

	/*Set the baud rate*/
	ubrr_value = (uint16)(((F_CPU / (a_ptr->baud_rate * 8UL))) - 1);

	UBRRH = ubrr_value>>8;
	UBRRL = ubrr_value;
}

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint16 byte){

	while( BIT_IS_CLEAR(UCSRA , UDRE) ){}

	UDR = (uint8)byte ;


}

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint16 UART_receiveByte(void){

#ifdef INTERRUPT_MODE
	return data ;
#else
	while( BIT_IS_CLEAR(UCSRA , RXC) ){}
	return UDR ;
#endif

}

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(uint8 * str){

	for(uint8 i = 0 ; str[i]!= '\0' ; i++)
		UART_sendByte(str[i]);

}

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 * str){ // Receive until #

	uint8 i = 0 ;
	while(1) {
		str[i] = UART_receiveByte();
		if(str[i] == '#')
			break;
	}

	str[i] = '\0';
}



