/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Zidane D'souza
 * @brief          : Bit SET/RESET register BSRR
 ******************************************************************************
 */
#include <stdint.h>
#include "bsp.h"

void delay(unsigned int DelayLimit);

int main(void)
{
	SysTick_Config(SYSTICK_TICKS);
	/*enabling the peripheral clock to the AHB bus TO BLINK the LED*/
	RCC_AHBENR |= (1<<18);
	/*Set the mode of pin PB13 (User LED LD2) to output*/
	GPIO_B_MODER |= (1<<26);
	/*Toggle the LED*/
	while(1)
	{

		/*delay*/
		/* delay(1000000); This is a brain dead :|'polling function */
		/* What is polling polling is the process of constantly checking
		 * for a condition to be met so till then nothing else is done
		 * except wait for the condition to be met which is quiet expensive
		 * if you want to achieve multiple things simultaneously.
		 */

	}

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
