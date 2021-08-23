/***************************************************************/
/* Author      : Sugumaran A                                   */
/* File Name   : STM32TYPES.H                                  */
/* Description : Header file                                   */
/* Date        : 22-08-2021   						           */
/***************************************************************/

#ifndef STM32TYPES_H
#define STM32TYPES_H

#define _REG volatile
#define TRUE 1
#define FALSE 0

#define BIT_SET(reg, pos)	(reg = (reg | (0x00000001 << pos)))
#define BIT_CLR(reg, pos)	(reg = (reg & (~(0x00000001 << pos))))
#define BIT_TEST(reg, pos)	(reg &  (0x00000001 << pos))

typedef unsigned int U32;


#endif //STM32TYPES_H
