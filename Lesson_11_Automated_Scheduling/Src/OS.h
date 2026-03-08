/*
 * OS.h
 *
 *  Created on: Mar 1, 2026
 *      Author: Zidane Dsouza
 */

#ifndef OS_H_
#define OS_H_

#include <stdint.h>
#include "stm32f302x8.h"

typedef struct
{
	void *pvThreadSP;
}OS_THREAD_T;

typedef  void (*OS_THREAD_HANDLER_T)();

/* Incase all the threads are in the blocked state the Idle thread is
 * supposed to run. The Idle thread will never enter the blocked state
 * During this time its wise to put your system in a power-saving state
 */
void OS_IdleTask(void);

void OS_vRun();

void OS_vOnStartup(void);

/* Since stack-size that will be used by the idle task is unknown
 * it is best to define the size in the application
 */
void OS_vInit(void *PrivStackMmry, uint32_t u32stackSize);

void OS_vSched();

void OS_vThreadStart(OS_THREAD_T *me, OS_THREAD_HANDLER_T ThreadHandler,\
		void *PrivStackMmry, uint32_t u32stackSize);


#endif /* OS_H_ */
