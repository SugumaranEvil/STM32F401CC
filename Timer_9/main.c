/***************************************************************/
/* Author      : Sugumaran A                                   */
/* File Name   : main.c                                        */
/* Description : TIMER9 on STM32 main .c file                  */
/* Date        : 24-08-2021   				                   */
/***************************************************************/


#include <stm32f401cc.h>
#include <stm32f401cc_timer.h>


extern volatile U32 val;
volatile U32 val=0xffffffff;

void clock_config(void);
void gpio_config(void);
void generaltimer_config(void);


int main(void)
{
	U32 loop=0;

	//LED Blink
	clock_config();
	gpio_config();
	generaltimer_config();

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
	//PPRE2 APB2 prescalar not divided
	RCC->CFGR &= 0xffff1f0f;


	//TIMER9 clock enable
	RCC->APB2ENR |= 0x00010000;

	//GPIOC RESET
	BIT_SET(RCC->AHB1RSTR, GPIOCRST);

	//GPIOC RESET
	BIT_CLR(RCC->AHB1RSTR, GPIOCRST);

}

void gpio_config(void){

	//PORTA PA2
	//IO port A clock enable
	BIT_SET(RCC->AHB1ENR, GPIOAEN);

	//GPIO port mode register PA2 output
	GPIOA->MODER |= 0x00000020;

	//GPIO port output type register
	GPIOA->OTYPER = 0x00000000;

	//GPIO port output speed register
	GPIOA->OSPEEDR = 0x00000000;

	//GPIO port pull-up/pull-down register
	GPIOA->PUPDR = 0x00000000;

	//GPIO alternate function low register
	GPIOA->AFRL = 0x00000300;

	return;
}

void generaltimer_config(void)
{
//timerconfig
	//TIMER9
	//TIM9 control register
	//CR1 => CKD 00 ,  ARPE: 1 , OPM:0 , URS:1 , UDIS = 0,
	TIMER9->CR1 = 0x00000084;

	//TIM9 slave mode control register
	//SMCR => MSM: 00 , TS:111 , SMS: 000(Internal clock)
	TIMER9->SMCR = 0x00000070;

	//TIM9 Interrupt enable register
	//DIER => TIE: 1 , CC2IE: 0 , CC1IE: 1 , UIE: 1
	TIMER9->DIER = 0x00000043;

	//TIM9 event generation register
	//EGR => TG 1 , CC1G 1 ,  UG 1
	TIMER9->EGR = 0x00000043;

	//TIM9 capture/compare mode register 1
	//CCMR1 => OC1M 011 , OC1PE 1 , OC1FE  0 , CC1S  00
	TIMER9->CCMR1 = 0X00000038;

	//TIM9 capture/compare enable register
	//CCER => CC1NP: 0 , CC1P: 0 , CC1E: 1
	TIMER9->CCER = 0X00000001;

	//TIM9 prescaler
	//PSC=> 1000
	TIMER9->PSC = 0x3e8;

	//TIM9 auto-reload register
	//ARR=> 80000
	TIMER9->ARR = 0x1F40;

	//TIM9 capture/compare register 1
	//CCR1 preloadregister 80000
	TIMER9->CCR1 = 0x1F40;

	//counter enable
	TIMER9->CR1 |= 0x00000001;

}

