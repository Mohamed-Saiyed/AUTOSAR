 /******************************************************************************
 *
 * Module: Common - Macros
 *
 * File Name: Common_Macros.h
 *
 * Description: Commonly used Macros
 *
 ********************************************************************************/

#ifndef COMMON_MACROS
#define COMMON_MACROS

#include "STD_Types.h"

/* Set a certain bit in any register */
#define SET_BIT(REG,BIT) (*((volatile uint32_t *)REG)|=(1<<BIT))

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT) (*((volatile uint32 *)REG)&=(~(1<<BIT)))

/* Get a certain bit in any register */
#define GET_BIT(REG,BIT)      ((*((volatile uint32 *)REG) >> BIT) & 1)

/* Get any register */
#define GET_PORT(REG)      		(*((volatile uint32 *)REG))

/* Get any register */
#define SET_PORT(REG,VAL)      		(*((volatile uint32 *)REG) = VAL )

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT) (*((volatile uint32_t *)REG)^=(1<<BIT))

/* Rotate right the register value with specific number of rotates */
#define ROR(REG,num) ( *((volatile uint32 *)REG)= (*((volatile uint32 *)REG)>>num) | (*((volatile uint32 *)REG)<<(8-num)) )

/* Rotate left the register value with specific number of rotates */
#define ROL(REG,num) ( *((volatile uint32 *)REG)= (*((volatile uint32 *)REG)<<num) | (*((volatile uint32 *)REG)>>(8-num)) )

/* Check if a specific bit is set in any register and return true if yes */
#define BIT_IS_SET(REG,BIT) ( *((volatile uint32 *)REG) & (1<<BIT) )

/* Check if a specific bit is cleared in any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) ( !(*((volatile uint32 *)REG) & (1<<BIT)) )

#endif
