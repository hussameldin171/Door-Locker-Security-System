 /******************************************************************************
 *
 * Module:  Macros
 *
 * File Name: Macros.h
 *
 * Description: Commonly Used Macros and Extended Functions
 *
 * Author: Hussam Eldin Wael
 *
 *******************************************************************************/


#ifndef MACROS_H_
#define MACROS_H_

#include "std_types.h"
#include <stdarg.h>


/* 1- Set a bit to 1 in a register.*/
#define SET_BIT(REG,BIT) (REG |= (1<<BIT))

/*2- Clear a bit to 0 in a register.*/
#define CLEAR_BIT(REG , BIT) (REG &=~(1<<BIT))

/*3-Toggle a bit in a register.*/
#define TOGGLE_BIT(REG , BIT) (REG ^= (1<<BIT))


/*4- Write a logic value to a bit in a register.*/
#define WRITE_BIT(REG , BIT , VAL){\
	switch(VAL) {\
	case 0 : CLEAR_BIT(REG , BIT); break; \
	case 1: SET_BIT(REG , BIT); } }

/*5- Rotate bits right NUM times in a register.*/
#define ROR(REG , NUM) (REG = (REG>>NUM) | (REG<< (8*sizeof(REG)-NUM) ) )

/*6- Rotate bits left NUM times in a register.*/
#define ROL(REG , NUM) (REG = (REG<<NUM) | (REG>> (8*sizeof(REG)-NUM) ) )

/*7- Checks if a bit is set to 1 in a register, returns 1 in that case and 0 in the other case.*/
#define BIT_IS_SET(REG ,BIT) (REG & (1<<BIT))?1:0

/*8- Checks if a bit is cleared to 0 in a register, returns 1 in that case and 0 in the other case.*/
#define BIT_IS_CLEAR(REG ,BIT) !(BIT_IS_SET(REG , BIT))?1:0


/*9- Gets the value of the bit in a register (1 or 0).*/

#define GET_BIT(REG , BIT) BIT_IS_SET(REG , BIT)?1:0



/*******************************************************************************
 *                      Variadic Functions Prototypes                          *
 *******************************************************************************/


void SET_BITS(uint8 *reg , uint8 noOfBits , ...);

void CLEAR_BITS(uint8 *reg , uint8 noOfBits , ...);






#endif /* MACROS_H_ */
