 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: LCD.c
 *
 * Description: Source file for the LCD driver
 *
 * Author: Hussam Eldin Wael
 *
 *******************************************************************************/


#include "LCD.h"
#include "GPIO.h"
#include "util/delay.h"
#include <stdlib.h>

/*
 * Description :
 * Sends a command to be written in the command register of the LCD.
 */
void LCD_sendCommand(uint8 command){
	/*  Enable command register (RS = 0). */
	GPIO_writePin(LCD_CONTROL_PORT , LCD_RS_PIN , LOGIC_LOW);

	/* Enable Write Mode (R/W = 0). */
	GPIO_writePin(LCD_CONTROL_PORT , LCD_RW_PIN , LOGIC_LOW);
	_delay_ms(1);
	/*  Enable On (E = 1). */
	GPIO_writePin(LCD_CONTROL_PORT , LCD_E_PIN , LOGIC_HIGH);
	_delay_ms(1);

	/*  Send the command to the LCD. */
	GPIO_writePort(LCD_DATA_PORT, command);
	_delay_ms(1);

	/*  Enable Off (E = 0). */
	GPIO_writePin(LCD_CONTROL_PORT , LCD_E_PIN , LOGIC_LOW);
	_delay_ms(1);


}

/*
 * Description :
 * Displays an ASCII character on the LCD.
 */
void LCD_displayCharacter(uint8 character){
	/*  Enable data register (RS = 1). */
	GPIO_writePin(LCD_CONTROL_PORT , LCD_RS_PIN , LOGIC_HIGH);

	/* Enable Write Mode (R/W = 0). */
	GPIO_writePin(LCD_CONTROL_PORT , LCD_RW_PIN , LOGIC_LOW);
	_delay_ms(1);

	/*  Enable On (E = 1). */
	GPIO_writePin(LCD_CONTROL_PORT , LCD_E_PIN , LOGIC_HIGH);
	_delay_ms(1);

	/*  Send the character to the LCD. */
	GPIO_writePort(LCD_DATA_PORT, character);
	_delay_ms(1);

	/*  Enable Off (E = 0). */
	GPIO_writePin(LCD_CONTROL_PORT , LCD_E_PIN , LOGIC_LOW);
	_delay_ms(1);


}

/*
 * Description :
 * Initializes the LCD at the required pins.
 */

void LCD_init(void) {

	/* Set RS , R/W and E as output pins.*/
	GPIO_setupPinDirection(LCD_CONTROL_PORT , LCD_E_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_CONTROL_PORT , LCD_RS_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_CONTROL_PORT , LCD_RW_PIN, PIN_OUTPUT);

	/* Set LCD port as output.*/
	GPIO_setupPortDirection(LCD_DATA_PORT, PORT_OUTPUT);

	/*2 Lines , 8 bit mode.*/
	LCD_sendCommand(TWO_LINES_8_BIT_MODE);

	/*Cursor Initialize.*/
	LCD_sendCommand(CURSOR_OFF);

	/*Clear the screen.*/
	LCD_sendCommand(CLEAR_SCREEN);


}


/*
 * Description :
 * Displays a String on the LCD.
 */
void LCD_displayString(uint8 *str){


	for(uint8 i = 0 ; str[i]!= '\0' ; i++) {
		LCD_displayCharacter(str[i]);
	}

}

/*
 * Description :
 * Displays a number on the LCD.
 */

void LCD_displayNumber(uint16 number) {

	uint16 buff[16];
	itoa(number , buff , 10);
	LCD_displayString(buff);

}

/*
 * Description :
 * Moves the cursor to the desired location on the LCD.
 */

void LCD_moveCursor(uint8 row,uint8 col){
	uint8 lcd_memory_address;


	switch(row)
	{
		case 0:
			lcd_memory_address= col + ROW1_ADDRESS;
				break;
		case 1:
			lcd_memory_address=col + ROW2_ADDRESS;
				break;
		case 2:
			lcd_memory_address=col + ROW3_ADDRESS;
				break;
		case 3:
			lcd_memory_address=col + ROW4_ADDRESS;
				break;
	}
	LCD_sendCommand(lcd_memory_address | LCD_SET_CURSOR_LOCATION);
}

/*
 * Description :
 * Displays a String at the desired location on the LCD.
 */
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *str){


	LCD_moveCursor(row, col);

	LCD_displayString(str);

}

/*
 * Description :
 * Clears the LCD Screen.
 */
void LCD_clearScreen(void){

	LCD_sendCommand(CLEAR_SCREEN);
}

void LCD_displayStringAligned(uint8 *str , uint8 row , LCD_wordAlignment align){

	uint8 str_length = strlen(str);

	switch(align) {

	case LEFT:
		LCD_displayStringRowColumn(row, 0, str);
		return ;

	case RIGHT:
		LCD_displayStringRowColumn(row,	LCD_LENGTH - str_length , str);
		return ;

	case CENTER:
		LCD_displayStringRowColumn(row,	(LCD_LENGTH/2) - (str_length/2) , str);
				return ;


	}

}
