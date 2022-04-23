/******************************************************************************
 *
 * Module: LCD
 *
 * File Name: LCD.h
 *
 * Description: Header file for the LCD driver
 *
 * Author: Hussam Eldin Wael
 *
 *******************************************************************************/
#ifndef LCD_H_
#define LCD_H_

#include "gpio.h"
#include "std_types.h"


/*******************************************************************************
 *                             Types Declarations                              *
 *******************************************************************************/
typedef enum {

	LEFT , RIGHT , CENTER

}LCD_wordAlignment;


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define LCD_CONTROL_PORT PORTB_ID
#define LCD_DATA_PORT    PORTC_ID

#define LCD_RS_PIN 		 PIN0_ID
#define LCD_RW_PIN 		 PIN1_ID
#define LCD_E_PIN 		 PIN2_ID

#define TWO_LINES_8_BIT_MODE 0x38
#define CURSOR_OFF 		     0x0C
#define CLEAR_SCREEN 		 0x01

#define LCD_SET_CURSOR_LOCATION 0x80

#define ROW1_ADDRESS 0x00
#define ROW2_ADDRESS 0x40
#define ROW3_ADDRESS 0x10
#define ROW4_ADDRESS 0x50

#define LCD_LENGTH 	32

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Sends a command to be performed by the LCD.
 */
void LCD_sendCommand(uint8 command);

/*
 * Description :
 * Displays an ASCII character on the LCD.
 */
void LCD_displayCharacter(uint8 character);

/*
 * Description :
 * Initializes the LCD at the required pins.
 */
void LCD_init(void);

/*
 * Description :
 * Displays a String on the LCD.
 */
void LCD_displayString(uint8 *str);

/*
 * Description :
 * Displays a number on the LCD.
 */
void LCD_displayNumber(uint16 number);

/*
 * Description :
 * Moves the cursor to the desired location on the LCD.
 */
void LCD_moveCursor(uint8 row,uint8 col);

/*
 * Description :
 * Displays a String at the desired location on the LCD.
 */
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *str);

/*
 * Description :
 * Clears the LCD Screen.
 */
void LCD_clearScreen(void);

void LCD_displayStringAligned(uint8 *str , uint8 row , LCD_wordAlignment align);

#endif /* LCD_H_ */
