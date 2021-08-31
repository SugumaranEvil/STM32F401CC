/***************************************************************/
/* Author      : Sugumaran A                                   */
/* File Name   : stm32f401cc.h                                 */
/* Description : Direct Memory Access on STM32 header file     */
/* Date        : 29-08-2021                                    */
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


#define TXE_POS	8
#define TC_POS	7

#define DMAT		7
#define DMA2EN		22
#define GPIOAEN		0
#define GPIOBEN		1
#define GPIOCEN		2
#define GPIOCRST	2
#define TC			6

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

_REG RCC_t* RCC = (_REG RCC_t*) (RCC_BASE);

#define GPIOC_BASE 0x40020800
#define GPIOB_BASE 0x40020400
#define GPIOA_BASE 0x40020000

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
extern _REG GPIO_t *GPIOA;

_REG GPIO_t *GPIOC = (_REG GPIO_t *) (GPIOC_BASE);
_REG GPIO_t *GPIOB = (_REG GPIO_t *) (GPIOB_BASE);
_REG GPIO_t *GPIOA = (_REG GPIO_t *) (GPIOA_BASE);


#define SYS_TIMER_BASE 0xE000E010

typedef volatile struct SYS_TIMER_s{
	_REG U32 STCSR;
	_REG U32 STRVR;
	_REG U32 STCVR;
	const U32 STCR;
}SYS_TIMER_t;

extern _REG SYS_TIMER_t *SYS_TIMER;


#define UART_STR "UART receiving data from transmitter!!!!!!!"
#define UART_BASE 0x40011000

typedef volatile struct UART_s{
	_REG U32 SR; 	//0x00
	_REG U32 DR;	//0x04
	_REG U32 BRR;	//0x08
	_REG U32 CR1;	//0x0c
	_REG U32 CR2;	//0x10
	_REG U32 CR3;	//0x14
	_REG U32 GTPR;	//0x18
}UART_t;

extern _REG UART_t *UART;

_REG UART_t *UART = (_REG UART_t *)(UART_BASE);


extern char DMA_UART_Tx_BUFFER[50];

#define DMA1_BASE 0x40026000
#define DMA2_BASE 0x40026400

typedef volatile struct DMA_s{
	_REG U32 LISR;		//0x0000
	_REG U32 HISR;		//0x0004
	_REG U32 LIFCR;		//0x0008
	_REG U32 HIFCR;		//0x000C
	_REG U32 S0CR;		//0x0010
	_REG U32 S0NDTR;	//0x0014
	_REG U32 S0PAR;		//0x0018
	_REG U32 S0M0AR;	//0x001C
	_REG U32 S0M1AR;	//0x0020
	_REG U32 S0FCR;		//0x0024
	_REG U32 S1CR;		//0x0028
	_REG U32 S1NDTR;	//0x002C
	_REG U32 S1PAR;		//0x0030
	_REG U32 S1M0AR;	//0x0034
	_REG U32 S1M1AR;	//0x0038
	_REG U32 S1FCR;		//0x003C
	_REG U32 S2CR;		//0x0040
	_REG U32 S2NDTR;	//0x0044
	_REG U32 S2PAR;		//0x0048
	_REG U32 S2M0AR;	//0x004C
	_REG U32 S2M1AR;	//0x0050
	_REG U32 S2FCR;		//0x0054
	_REG U32 S3CR;		//0x0058
	_REG U32 S3NDTR;	//0x005C
	_REG U32 S3PAR;		//0x0060
	_REG U32 S3M0AR;	//0x0064
	_REG U32 S3M1AR;	//0x0068
	_REG U32 S3FCR;		//0x006C
	_REG U32 S4CR;		//0x0070
	_REG U32 S4NDTR;	//0x0074
	_REG U32 S4PAR;		//0x0078
	_REG U32 S4M0AR;	//0x007C
	_REG U32 S4M1AR;	//0x0080
	_REG U32 S4FCR;		//0x0084
	_REG U32 S5CR;		//0x0088
	_REG U32 S5NDTR;	//0x008C
	_REG U32 S5PAR;		//0x0090
	_REG U32 S5M0AR;	//0x0094
	_REG U32 S5M1AR;	//0x0098
	_REG U32 S5FCR;		//0x009C
	_REG U32 S6CR;		//0x00A0
	_REG U32 S6NDTR;	//0x00A4
	_REG U32 S6PAR;		//0x00A8
	_REG U32 S6M0AR;	//0x00AC
	_REG U32 S6M1AR;	//0x00B0
	_REG U32 S6FCR;		//0x00B4
	_REG U32 S7CR;		//0x00B8
	_REG U32 S7NDTR;	//0x00BC
	_REG U32 S7PAR;		//0x00C0
	_REG U32 S7M0AR;	//0x00C4
	_REG U32 S7M1AR;	//0x00C8
	_REG U32 S7FCR;		//0x00CC
}DMA_t;

extern _REG DMA_t *DMA1;
extern _REG DMA_t *DMA2;

_REG DMA_t *DMA1 =  (_REG DMA_t *)(DMA1_BASE);
_REG DMA_t *DMA2 =  (_REG DMA_t *)(DMA2_BASE);






#endif
