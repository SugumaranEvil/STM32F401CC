/***************************************************************/
/* Author      : Sugumaran A                                   */
/* File Name   : stm32f402cc_timer.h                           */
/* Description : PWM on STM32                                  */
/* Date        : 25-08-2021             				       */
/***************************************************************/


#ifndef STM32F401CC_TIMER_H
#define STM32F401CC_TIMER_H

#include <stm32types.h>

#define TIMER10_BASE	0x40014400
#define TIMER11_BASE	0x40014800

typedef struct general_timer_s{
	_REG U32 CR1;		//0x00
	_REG U32 resvd0;	//0x04
	_REG U32 SMCR;		//0x08
	_REG U32 DIER;		//0x0C
	_REG U32 SR;		//0x10
	_REG U32 EGR;		//0x14
	_REG U32 CCMR1;		//0x18
	_REG U32 resvd1;	//0x1C
	_REG U32 CCER;		//0x20
	_REG U32 CNT;		//0x24
	_REG U32 PSC;		//0x28
	_REG U32 ARR;		//0x2C
	_REG U32 resvd2;	//0x30
	_REG U32 CCR1;		//0x34
	_REG U32 resvd3[6];		//0x38 to 0x4C
	_REG U32 OR;		//0x50
}general_timer_t;

extern _REG general_timer_t *TIMER10;
extern _REG general_timer_t *TIMER11;

_REG general_timer_t *TIMER10 = (_REG general_timer_t *)TIMER10_BASE;
_REG general_timer_t *TIMER11 = (_REG general_timer_t *)TIMER11_BASE;

#endif //STM32F401CC_TIMER_H
