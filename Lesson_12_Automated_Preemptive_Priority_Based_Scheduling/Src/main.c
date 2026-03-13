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
uint32_t USART_CommStack[256];    // Increased from 40 to 256 for printf
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
        OS_Delay(20);  /* ~200 ms */
	}
}

void LEDBlinkTask2(void)
{

	while(1)
	{
		/*Set PB13*/
		GPIO_B_BSRR = (1<<13);
		/*delay 500ms*/
		OS_Delay(50);
		/*Toggle PB13 */
		GPIO_B_BSRR = (1<<29);
		/*delay 330ms*/
		OS_Delay(33);
	}
}

int main(void)
{
	OS_vInit(IdleStack, sizeof(IdleStack));
	USART_vInit();
	bsp_init();

	OS_vThreadStart(&USART_CommThread
			,2u
			,&USARTCommTask1
			,USART_CommStack
			,sizeof(USART_CommStack));

	OS_vThreadStart(&LED_BlinkThread
			,5u
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
