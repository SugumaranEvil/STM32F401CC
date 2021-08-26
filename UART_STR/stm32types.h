/***************************************************************/
/* Author      : Sugumaran A                                   */
/* File Name   : stm32types.h                                  */
/* Description : UART on STM32 stm32types.h file               */
/* Date        : 26-08-2021   				                   */
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
typedef signed int S32;
typedef unsigned short int U16;
typedef signed short int S16;
typedef unsigned char U8;
typedef signed char S8;


//__inline U32 _BIT_SET(U32 value, U8 lsb, U8 width ){
//	register U32 reg1 = value;
//	asm();
//}


#define CLR_BITS(value,lsb,width) 	({\
	asm volatile("BFC %0, #"#lsb", #"#width: "=r" (value));\
	})

#define SET_BIT(value,lsb) 	({\
	asm volatile("BFC %0, #"#lsb", #1": "=r" (value));\
	})


#endif //STM32TYPES_H
