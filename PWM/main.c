/***************************************************************/
/* Author      : Sugumaran A                                   */
/* File Name   : main.c                                        */
/* Description : PWM on STM32 main .c file                     */
/* Date        : 24-08-2021   				                   */
/***************************************************************/


#include <stm32f401cc.h>
#include <stm32f401cc_timer.h>

#define LOAD_VAL 800

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


	//TIMER10 clock enable
	RCC->APB2ENR |= 0x00020000;


	//GPIOC RESET
	BIT_SET(RCC->AHB1RSTR, GPIOCRST);

	//GPIOC RESET
	BIT_CLR(RCC->AHB1RSTR, GPIOCRST);

}

void gpio_config(void){

	//PORTB
	BIT_SET(RCC->AHB1ENR, GPIOBEN);

	//PB8 set to alternate funtion
	GPIOB->MODER = 0x00020000;

	//port pull-up/pull-down register
	GPIOB->PUPDR = 0x00050000;

	//Alternate function selection for port AF3 to select portb8 give pwm output
	GPIOB->AFRH = 0x00000003;

	return;
}

void generaltimer_config(void)
{

//timerconfig
	//TIMER10
	//PWM using timer10
	//CCR1 => CKD 00 ,  ARPE: 1 , OPM:0 , URS:1 , UDIS = 0,
	TIMER10->CR1 = 0x00000084;

	//CCMR1 => OC1M: 110 , OC1PE: 1 , OC1FE: 0 , CC1S:00
	TIMER10->CCMR1 = 0x00000068;

	//CCER => CC1NP: 0 , CC1P: 0 , CC1E: 1
	TIMER10->CCER = 0x00000001;

	//PSC=> 1000
	TIMER10->PSC = 1000;

	//ARR=> 800 (20ms)
	TIMER10->ARR = LOAD_VAL;

	//CCR1 preloadregister
	TIMER10->CCR1 = 0;

	//counter enable
	TIMER10->CR1 |= 0x00000001;

	while(1){
		TIMER10->CCR1 = 0;
		while(TIMER10->CCR1 <= LOAD_VAL){
			for(int temp=0 ; temp<10000 ; temp++){}
					TIMER10->CCR1 += 1;
				}

		while(TIMER10->CCR1 > 0){
			for(int temp=0 ; temp<10000 ; temp++){}
							TIMER10->CCR1 -= 1;
						}
	}
}

