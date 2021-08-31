/***************************************************************/
/* Author      : Sugumaran A                                   */
/* File Name   : main.c                                        */
/* Description : Direct Memory Access on STM32                 */
/* Date        : 29-08-2021                                    */
/***************************************************************/


#include <stm32f401cc.h>

extern volatile U32 val;
volatile U32 val=0xffffffff;
char DMA_UART_Tx_BUFFER[50]={0};
char *str="Transmitter transmitting.........\n";


void clock_config(void);
void gpio_config(void);
void dma2_config(void);

int strlen(char *);
int strcpy(const char *, char *);

void uart_config(void);


int main(void)
{
	volatile U32 loop;
	clock_config();
	gpio_config();
	uart_config();
	dma2_config();

    /* Loop forever */
	for(;;);
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

	//TIMER10 clock enable
	//RCC->APB2ENR |= 0x00020000;


	//GPIOC RESET
	BIT_SET(RCC->AHB1RSTR, GPIOCRST);

	//GPIOC RESET
	BIT_CLR(RCC->AHB1RSTR, GPIOCRST);
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


void uart_config(void){

	//USART enable, TX enable PIN = A9
	UART->CR1 = 0x00002008;

	//Baud rate 9600  USARTDIV 260.42 => Mantissa 260 , fraction 7 [7/16 = 0.4375] ""
	UART->BRR = (260 << 4) | 7;

}


int strlen(char *str){
	int length=0;

	 while(*(str++)!='\0')
	 {
	    length = length+1;
	 }
	 return length;
}


int strcpy(const char *src, char *des){

	int length=0;
	 while(*src != '\0')
	 {
	    *des++ = *src++;
	    length++;
	 }
	 return length;
}


void dma2_config(void){

   /* DMA - Direct Memory Address , here memory to peripheral we are using string memory to print in uart by using DMA.*/
    
	//DMA enable transmitter
	BIT_SET(UART->CR3, DMAT);

	//DMA2 clock enable
	BIT_SET(RCC->AHB1ENR, DMA2EN);

	//ch 4 stream 7 for USART Tx1
	//DMA stream x configuration register
	//S2CR => CHSEL 100 MBURST: 00 PBURST 00 ct 0 DBM: 0 PL 00 PINCOS:0 MSIZE 00 PSIZE 00 MINC: 1 PINC: 0
	DMA2->S7CR = 0x08030440;

	//DMA stream x number of data register
	DMA2->S7NDTR = strcpy(str,DMA_UART_Tx_BUFFER);

	//DMA stream x peripheral address register
	DMA2->S7PAR =(U32 )&UART->DR;

	//DMA stream x memory 1 address register
	DMA2->S7M0AR = (U32 )DMA_UART_Tx_BUFFER;

	//DMA stream x FIFO control register
	DMA2->S7FCR |= 0x00000000;

	//Transmission complete clearing bit
	BIT_CLR(UART->SR,TC);

	//DMA stream enablebit EN =1
	//Stream enable / flag stream ready when read low
	DMA2->S7CR |= 0x00000001;
}


