/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Zidane D'souza
 * @brief          : Bit SET/RESET register BSRR
 ******************************************************************************
 */
#include "OS.h"
#include <stdbool.h>
#include "bsp.h"
#include "USART.h"

uint32_t IdleStack[40];
uint32_t USART_CommStack[40];
OS_THREAD_T USART_CommThread;
uint32_t LED_BlinkStack[40];
OS_THREAD_T LED_BlinkThread;


void delay(unsigned int DelayLimit);

int __io_putchar(int ch)
{
	USART_vWrite(ch);
	return ch;
}

void USARTCommTask1(void)
{
	while(1)
	{
         printf("Hello World \n\r");
		/*delay*/
		/* delay(1000000); This is a brain dead :|'polling function */
		/* What is polling polling is the process of constantly checking
		 * for a condition to be met so till then nothing else is done
		 * except wait for the condition to be met which is quiet expensive
		 * if you want to achieve multiple things simultaneously.
		 */

	}
}

void LEDBlinkTask2(void)
{

	while(1)
	{
		/*Set PB13*/
		GPIO_B_BSRR = (1<<13);
		/*delay*/
		delay(1000000);
		/*Toggle PB13 */
		GPIO_B_BSRR = (1<<29);
		/*delay*/
		delay(1000000);
	}
}

int main(void)
{
	OS_vInit(IdleStack, sizeof(IdleStack));
	USART_vInit();
	bsp_init();

	OS_vThreadStart(&USART_CommThread
			,&USARTCommTask1
			,USART_CommStack
			,sizeof(USART_CommStack));

	OS_vThreadStart(&LED_BlinkThread
			,&LEDBlinkTask2
			,LED_BlinkStack
			,sizeof(LED_BlinkStack));

	/*Transfer control to RTOS and ask it to run the threads*/
	/* Configure and enable interrupts after the threads are
	 * initialized this is important to be here else incase of an exception
	 * before the initialization of the threads you may or
	 * may not have all the threads initialized.
	 */
	OS_vRun();

    return 0 ;
}

void delay(unsigned int DelayLimit)
{
	unsigned int volatile i;

	for(i = 0; i < DelayLimit ; i++)
	{
		/*wait*/
	}
}
