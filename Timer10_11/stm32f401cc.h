/***************************************************************/
/* Author      : Sugumaran A                                   */
/* File Name   : stm32f401cc.h                                 */
/* Description : TIMER10 & 11 on STM32                         */
/* Date        : 20-08-2021   				                   */
/***************************************************************/


#ifndef STM32F401CC_H
#define STM32F401CC_H

#include <stm32types.h>

#define RCC_BASE 		 0x40023800
#define RCC_CR			 0x00
#define RCC_PLLCFGR		 0x04
#define RCC_CFGR	 	 0x08
#define RCC_CIR			 0x0C
#define RCC_AHB1RSTR	 0x10
#define RCC_AHB2RSTR	 0x14
#define RCC_APB1RSTR	 0x20
#define RCC_APB2RSTR	 0x24
#define RCC_AHB1ENR 	 0x30
#define RCC_AHB2ENR 	 0x34
#define RCC_APB1ENR		 0x40
#define RCC_APB2ENR		 0x44
#define RCC_AHB1LPENR	 0x50
#define RCC_AHB2LPENR	 0x54
#define RCC_APB1LPENR	 0x60
#define RCC_APB2LPENR	 0x64
#define RCC_BDCR		 0x70
#define RCC_CSR			 0x74
#define RCC_SSCGR		 0x80
#define RCC_PLLI2SCFGR	 0x84
#define RCC_DCKCFGR		 0x8C


#define PLLON	24
#define HSEBYP	18
#define HSEON	16
#define HSERDY	17


#define PLLSRC	22
#define PLLM	0
#define PLLN	6
#define PLLP	16
#define PLLON	24
#define PLLRDY	25


#define SW_HSI	0
#define SW_HSE	1
#define SW_PLL	2
#define SW_INVALID 3



#define GPIOCEN		2
#define GPIOCRST	2


#define GPIOBEN		1

#define SWS_MASK 	0x0c
#define SWS_HSI		0x00
#define SWS_HSE		0x04
#define SWS_PLL		0x08
#define SWS_INVALID 0x0c


typedef volatile struct RCC_s {
	_REG U32 CR;			//0x00
	_REG U32 PLLCFGR;		//0x04
	_REG U32 CFGR;			//0x08
	_REG U32 CIR;			//0x0C
	_REG U32 AHB1RSTR;		//0x10
	_REG U32 AHB2RSTR;		//0x14
	U32 reserved1;			//0x18
	U32 reserved2;			//0x1C
	_REG U32 APB1RSTR;		//0x20
	_REG U32 APB2RSTR;		//0x24
	U32 reserved3;			//0x28
	U32 reserved4;			//0x2C
	_REG U32 AHB1ENR;		//0x30
	_REG U32 AHB2ENR;		//0x34
	U32 reserved5;			//0x38
	U32 reserved6;			//0x3C
	_REG U32 APB1ENR;		//0x40
	_REG U32 APB2ENR;		//0x44
	U32 reserved7;			//0x48
	U32 reserved8;			//0x4C
	_REG U32 AHB1LPENR;		//0x50
	_REG U32 AHB2LPENR;		//0x54
	U32 reserved9;			//0x58
	U32 reserved10;			//0x5C
	_REG U32 APB1LPENR;		//0x60
	_REG U32 APB2LPENR;		//0x64
	U32 reserved11;			//0x68
	U32 reserved12;			//0x6C
	_REG U32 BDCR;			//0x70
	_REG U32 CSR;			//0x74
	U32 reserved13;			//0x78
	U32 reserved14;			//0x7C
	_REG U32 SSCGR;			//0x80
	_REG U32 PLLI2SCFGR;	//0x84
}RCC_t;

extern _REG RCC_t *RCC;


#define GPIOC_BASE 0x40020800
#define GPIOB_BASE 0x40020400

typedef volatile struct GPIO_s{
	_REG U32 MODER;
	_REG U32 OTYPER;
	_REG U32 OSPEEDR;
	_REG U32 PUPDR;
	_REG U32 IDR;
	_REG U32 ODR;
	_REG U32 BSRR;
	_REG U32 LCKR;
	_REG U32 AFRL;
	_REG U32 AFRH;

}GPIO_t;

extern _REG GPIO_t *GPIOC;
extern _REG GPIO_t *GPIOB;


#define SYS_TIMER_BASE 0xE000E010

typedef volatile struct SYS_TIMER_s{
	_REG U32 STCSR;
	_REG U32 STRVR;
	_REG U32 STCVR;
	const U32 STCR;
}SYS_TIMER_t;

extern _REG SYS_TIMER_t *SYS_TIMER;

_REG GPIO_t *GPIOC = (_REG GPIO_t *) (GPIOC_BASE);
_REG GPIO_t *GPIOB = (_REG GPIO_t *) (GPIOB_BASE);

_REG RCC_t* RCC = (_REG RCC_t*) (RCC_BASE);



#endif
