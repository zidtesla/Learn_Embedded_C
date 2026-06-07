/* This module contains board specific related functions and initializations */
#include "bsp.h"
/* This function resets the MCU whenever there is a fault in the system */
void assert_failed(const char *File, int line)
{
	/* TBD: Damage control */
	NVIC_SystemReset();
}

void SysTick_Handler(void)
{
	/*Set PB13*/
	GPIO_B_ODR ^= (1<<13);
}
