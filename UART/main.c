/***************************************************************/
/* Author      : Sugumaran A                                   */
/* File Name   : main.c                                        */
/* Description : UART on STM32 main .c file                    */
/* Date        : 25-08-2021   				                   */
/***************************************************************/


#include <stm32f401cc.h>

extern volatile U32 val;
volatile U32 val=0xffffffff;


void clock_config(void);
void gpio_config(void);


void uart_tx(U8);
void uart_config(void);


int main(void)
{
	U32 loop=0;

	//LED Blink
	clock_config();
	gpio_config();
	uart_config();

    /* Loop forever */
	for(;;){
		uart_tx('a');
		for(loop=0 ; loop<100000;){
			loop++;
		}
		for(loop=0 ; loop<100000;){
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

	//USART1EN: USART1 clock enable
	RCC->APB2ENR |= 0x00000010;


}

void gpio_config(void){

	//PORTA
	//PORTA enable bit
	BIT_SET(RCC->AHB1ENR, GPIOAEN);

	//USART1_TX, PA9     USART1_RX, PA10
	//PA9 & PA10 set to alternate funtion
	GPIOA->MODER |= 0x00280000;

	//GPIO port pull-up/pull-down register PA9 &PA10
	GPIOA->PUPDR |= 0x00140000;

	//GPIO alternate function high register
	//PA8 & PA9 set to AF07 for USART output
	GPIOA->AFRH |= 0x00000770;

	return;
}


void uart_tx(U8 data){
	//TXE: Transmit data register is empty or not
	//while(!(BIT_TEST( UART->SR, TXE_POS)));

	//Data
	UART->DR = data;

	//Tx enable  PIN = A9
	UART->CR1 |= 0x00000008;

	//Tx is completed or not
	while(!(BIT_TEST( UART->SR, TC_POS)));
}



void uart_config(void){

	//USART enable
	UART->CR1 = 0x00002000;

	//Baud rate 9600  USARTDIV 260.42 => Mantissa 260 , fraction 7 [7/16 = 0.4375] ""
	UART->BRR = (260 << 4) | 7;

}


