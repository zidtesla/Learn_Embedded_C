/* This module contains board specific related functions and initializations */
#include "stm32f302x8.h"
#include "core_cm4.h"

/* This function resets the MCU whenever there is a fault in the system */
void assert_failed(const char *File, int line)
{
	/* TBD: Damage control */
	NVIC_SystemReset();
}
