/***************************************************************/
/* Author      : Sugumaran A                                   */
/* File Name   : main.c                                        */
/* Description : SYS_TICK system timer how to config           */
/* Date        : 22-08-2021   						           */
/***************************************************************/

#include <stm32f401cc.h>


_REG GPIO_t *GPIOC = (_REG GPIO_t *) (GPIOC_BASE);
_REG RCC_t* RCC = (_REG RCC_t*) (RCC_BASE);
_REG SYS_TIMER_t *SYS_TIMER = (_REG SYS_TIMER_t *) (SYS_TIMER_BASE);

//Interrupt Control State Register
_REG U32 *ICSR = (_REG U32 *)0xE000ED04;

void clock_config(void);
void gpio_config(void);

void SysTimer_config(void);
void SysTick_Handler(void);
volatile U32 value=0;


void SysTimer_config(void) {
	//System timer settings
	//Enable the systick interrupt
	SYS_TIMER->STCSR = 0x02;

	//Reload value register
	SYS_TIMER->STRVR = 10000;
//	SYS_TIMER->STRVR = 0x64;

	//SysTick Current Value Register
	SYS_TIMER->STCVR = 1;

	//the counter is enabled
	SYS_TIMER->STCSR = 0x02 | 0x01;
}


int main(void)
{
	U32 loop=0;
	gpio_config();
	//LED Blink
	clock_config();
	gpio_config();
	SysTimer_config();
	
    /* Loop forever */
	for(;;){
		//LED Blink
		for(loop=0 ; loop<10000;){
			loop++;
		}
	}
}


void clock_config(void)
{
	//RCC.CR = (volatile unsigned int *) (RCC_BASE | RCC_CR);
	//HSE frequency is 25MHz
	//Desired system clock frequency is 40MHz
	//PLLON=0; PLL is OFF

	BIT_CLR(RCC->CR, PLLON);

	//HSEBYP bit has to be cleared because we are using it should not be bypass
	BIT_CLR(RCC->CR, HSEBYP);

	//HSEON set to 1
	BIT_SET(RCC->CR, HSEON);

	//Wait until HSERDY is set to 1
	while(!(BIT_TEST(RCC->CR, HSERDY)));

	//PLLSRC:set to 1 to select HSE as a PLL clock source
	BIT_SET(RCC->PLLCFGR, PLLSRC);

	//Divide HSE by 5 and multiply by 8 to get 40 MHz system clock
	//PLLM 5; 25/5 = 5MHz;
	RCC->PLLCFGR = RCC->PLLCFGR & (0xffffffe0);
	RCC->PLLCFGR = RCC->PLLCFGR | (5 << PLLM);

	//PLLN 16; 16*5 = 80MHz;
	RCC->PLLCFGR = RCC->PLLCFGR & (0xffffc01f);
	RCC->PLLCFGR = RCC->PLLCFGR | (16 << PLLN);

	//PLLP 2; 80/2 = 40MHz;
	RCC->PLLCFGR = RCC->PLLCFGR & (0xffff3fff);
	RCC->PLLCFGR = RCC->PLLCFGR | (2 << PLLP);

	//PLLON=1; PLL is ON "After configured the PLL only we need to start it"
	BIT_SET(RCC->CR, PLLON);

    //Wait until PLL locks to desired frequency
	while(!(BIT_TEST(RCC->CR, PLLRDY)));

	//Switch system clock to PLLCLK (PLL clock)
//	RCC->CFGR = RCC->CFGR | (2 << SW);
	RCC->CFGR |= SW_PLL;

	//wait until switch clock status is set to PLLCLK clock
	while(!((RCC->CFGR & SWS_MASK)==SWS_PLL));

	//CFGR AHB prescalar =>system clock not divided
	RCC->CFGR &= 0xffffff0f;

	//GPIOC RESET
	BIT_SET(RCC->AHB1RSTR, GPIOCRST);

	//GPIOC RESET
	BIT_CLR(RCC->AHB1RSTR, GPIOCRST);

	//GPIOC Clock enable
	//BIT_SET(RCC->AHB1ENR, GPIOCEN);
}

void gpio_config(void){
	U32 val;
	U32 loop1;
	//PORTC Base address = 0x4002 0800

	//Bad coding.....
	BIT_SET(RCC->AHB1ENR, GPIOCEN);

	GPIOC->MODER = 0x54000000;

	GPIOC->OTYPER = 0xE000;

	GPIOC->OSPEEDR = 0x00000000;

	GPIOC->PUPDR = 0x54000000;

/*	for (loop1 = 0; loop1 < 20; loop1++) {
		val = 1000000;
		while(val--);
		GPIOC->ODR =  0xE000; //LED ON
		val = 1000000;
		while(val--);
		GPIOC->ODR =  0x0000; //LED OFF
	}*/
}


//SysTick_Handler 
void SysTick_Handler(void){
	*ICSR &= 0x02000000;//clear systick pending flag
	//SYS_TIMER->STCSR |= 0x010000;
	// write to a variable
	if(value == 0) {
		value = 1;
		GPIOC->ODR =  0xE000; //Output data register
	} else {
		value = 0;
		GPIOC->ODR =  0xE000;
	}
	//value=0;
	//check the interrupt is working or not
}
