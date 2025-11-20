#include "USART.h"
#include <stddef.h>

static void USART_vSetBaudRate(USART_TypeDef *USARTx, uint32_t u32BaudRate)
{

	if(USARTx != NULL)
	{
		USARTx->BRR = USART_u32ConfigDiv(PERIPH_CLK_D,u32BaudRate);
	}
	else
	{
	    /*Raise a communication fault*/
	}

}

static uint32_t USART_u32ConfigDiv(uint32_t u32PeriphClk, uint32_t u32BaudRate)
{
	 uint32_t u32Divisor;
     u32Divisor = (u32PeriphClk + (u32BaudRate/2))/u32BaudRate;
     return u32Divisor;
}

void USART_vWrite(uint16_t ch)
{
	/*Check if the uart data register is empty */
	while(!(USART2->ISR & USART_ISR_TXE))
	{
		/*Wait for the transmission to complete*/
	}
	/*Write to the data register*/
	USART2->TDR = (ch & 0xFF);
}

void USART_vInit(void)
{
	/*Configure GPIO for USART*/
	/* NOTE: Use the USART2 because the USART2 communication between the
	 * target STM32 and ST-LINK MCU is enabled, in order to
     * support virtual COM port for Mbed
     */

	/*GPIO port A enable*/
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    /*Set the GPIO port A pin 2 to alternate function mode*/
	GPIOA->MODER |= GPIO_MODER_MODER2_1;

	/* set PA2 to AF07 i.e. USART2*/
	GPIOA->AFR[0]|= (1 << 8);
	GPIOA->AFR[0]|= (1 << 9);
	GPIOA->AFR[0]|= (1 << 10);
	GPIOA->AFR[0]&= ~(1 << 11);

	/*Configure the USART*/
	/*Enable clock for the APB bus */
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

	/*Configure the USART2 baudrate*/
	USART_vSetBaudRate(USART2, UART_BAUD_RATE_D);

	/* Configure the USART direction */
    USART2->CR1 = USART_CR1_TE;
	/* Enable the USART module */
    USART2->CR1 |= USART_CR1_UE;
}
