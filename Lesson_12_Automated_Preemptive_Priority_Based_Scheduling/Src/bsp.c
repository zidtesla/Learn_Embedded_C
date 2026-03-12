/* This module contains board specific related functions and initializations */
#include "bsp.h"
#include "OS.h"

/* This function resets the MCU whenever there is a fault in the system */
void assert_failed(const char *File, int line)
{
	/* TBD: Damage control */
	NVIC_SystemReset();
}

void SysTick_Handler(void)
{
	OS_vTick();
	__disable_irq();
	OS_vSched();
	__enable_irq();
}

void bsp_init(void)
{
	/*enabling the peripheral clock to the AHB bus TO BLINK the LED*/
	RCC_AHBENR |= (1<<18);
	/*Set the mode of pin PB13 (User LED LD2) to output*/
	GPIO_B_MODER |= (1<<26);
}

/*These two functions have been defined here since they are
 * dependent on the hardware for their functioning
 */
void OS_vOnStartup(void)
{
	SysTick_Config(SYSTICK_TICKS);

	/*Set the systick interrupt priority (highest)*/
	NVIC_SetPriority(SysTick_IRQn,0u);

	__enable_irq();
}

void OS_vOnIdle(void)
{

}
