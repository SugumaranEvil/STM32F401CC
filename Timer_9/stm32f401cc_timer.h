/***************************************************************/
/* Author      : Sugumaran A                                   */
/* File Name   : stm32f401cc_timer.h                           */
/* Description : TIMER9 on STM32                               */
/* Date        : 24-08-2021   				                   */
/***************************************************************/


#ifndef STM32F401CC_TIMER_H
#define STM32F401CC_TIMER_H

#include <stm32types.h>

//Timer 9
#define TIMER9_BASE	0x40014000

typedef struct general_timer_s{
	_REG U32 CR1;		//0x00
	_REG U32 resvd1;	//0x04
	_REG U32 SMCR;		//0x08
	_REG U32 DIER;		//0x0C
	_REG U32 SR;		//0x10
	_REG U32 EGR;		//0x14
	_REG U32 CCMR1;		//0x18
	_REG U32 resvd2;	//0x1C
	_REG U32 CCER;		//0x20
	_REG U32 CNT;		//0x24
	_REG U32 PSC;		//0x28
	_REG U32 ARR;		//0x2C
	_REG U32 resvd3;	//0x30
	_REG U32 CCR1;		//0x34
	_REG U32 CCR2;		//0x38
	_REG U32 resvd[5];	//0x3C to 0x4C
}general_timer_t;

extern _REG general_timer_t * TIMER9;

_REG general_timer_t *TIMER9 = (_REG general_timer_t *)TIMER9_BASE;

#endif //STM32F401CC_TIMER_H
