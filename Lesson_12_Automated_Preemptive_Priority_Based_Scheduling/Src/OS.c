/*
 * OS.c
 *
 *  Created on: Feb 28, 2026
 *      Author: Zidane Dsouza
 */

#include "OS.h"

OS_THREAD_T * volatile OS_curr;
OS_THREAD_T * volatile OS_next;

#define LOG2(X)    (32 -  __CLZ(X))

/* The array holds the list of threads to run
 * assuming the RTOS allows 32 threads and the +1 is the
 * idle thread
 */
OS_THREAD_T *OS_ThreadArray[32 + 1];


/* Bitmask of threads that are
 * ready to run
 */
uint32_t OS_u32ReadySet;

/* Bitmask of threads that are
 * in the delayed state
 */
uint32_t OS_u32DelayedSet;

OS_THREAD_T OS_IdleThread;

void OS_vRun(void)
{
	/*callback to configure and start interrupts*/
	OS_vOnStartup();

	__disable_irq();
	OS_vSched();
	__enable_irq();

	/* The code following this should never be executed*/
	//Q_ERROR();
}

void OS_vInit(void *PrivStackMmry, uint32_t u32stackSize)
{
	/* Sets the priority of the PendSV so that it does not preempt the
	 * the systick interrupt
	 */
	*(uint32_t volatile *)0xE000ED20 |= (0xFF << 16);

	/*Start the idle thread*/
	OS_vThreadStart(&OS_IdleThread
			,0u
			,&OS_IdleTask
			,PrivStackMmry
			,u32stackSize);
}

void OS_vSched(void)
{
	/* Check if the idle thread needs to run */
	if(OS_u32ReadySet == 0u)
	{
		OS_next = OS_ThreadArray[0];
	}
	/* Schedule the threads in the ready state */
	else
	{
		OS_next = OS_ThreadArray[LOG2(OS_u32ReadySet)];
		/*LOG2 produces numbers from zero to 32 please insert a check or assert
		 * to check that os_next is not equal to zero
		 */
	}

	if(OS_next != OS_curr)
	{
		/*Trigger the PENDSV interrupt*/
		*(uint32_t volatile *)0xE000ED04 = (1 << 28);
	}
}

void OS_vThreadStart(OS_THREAD_T *me, uint8_t u8ThreadPrio ,OS_THREAD_HANDLER_T ThreadHandler,\
		void *PrivStackMmry, uint32_t u32stackSize)
{
	uint32_t *sp;
	uint32_t *pu32StackLimit;
	/* in ARM the stack grows from HIGH to LOW
	 * memory addresses*/
	/*Round DOWN to highest 8-byte aligned address within allocated bounds*/
	sp = (uint32_t *)((((uint32_t)PrivStackMmry + u32stackSize)/8)*8);

    /* But first check if the thread is in range
     * And also make sure that only one thread is assigned a unique priority
     * u8ThreadPrio < MAX_THREADS_D && OS_ThreadArray[u8ThreadPrio] == (OS_THREAD_T *)0)
     * USE AN ASSERT function to go into fault mode if this
     * condition fails.
     * NOTE: For now since there are just two tasks I am safe
     * but this will need to be revisited once the assert
     * functions are implemented.
     * */

	*(--sp) = (1 << 24); /*PSR*/
	*(--sp) = (uint32_t)ThreadHandler; /*PC*/
	*(--sp) = 0x0000000EU; /*LR*/
	*(--sp) = 0x0000000CU; /*R12*/
	*(--sp) = 0x00000003U; /*R3*/
	*(--sp) = 0x00000002U; /*R2*/
	*(--sp) = 0x00000001U; /*R1*/
	*(--sp) = 0x00000000U; /*R0*/
	/* additionally,fake registers R4-R11 */
	/*For context switching from one task to another task*/
	*(--sp) = 0x0000000BU; /*R11*/
	*(--sp) = 0x0000000AU; /*R10*/
	*(--sp) = 0x00000009U; /*R9*/
	*(--sp) = 0x00000008U; /*R8*/
	*(--sp) = 0x00000007U; /*R7*/
	*(--sp) = 0x00000006U; /*R6*/
	*(--sp) = 0x00000005U; /*R5*/
	*(--sp) = 0x00000004U; /*R4*/

	/*Save the top of the stack in the threads attribute*/
	me->pvThreadSP = sp;
	/* Rounding up the bottom of the stack to the 8-byte boundary */
	pu32StackLimit = (uint32_t *)(PrivStackMmry);

	/* pre-fill the unused part of the stack with 0xDEADBEEF. This helps
	 * determine the worst case stack use
	 */
      for(sp = sp - 1U; sp >= pu32StackLimit; --sp)
      {
    	  *sp = 0xDEADBEEFU;
      }

      /* Everytime the thread is started the thread array and thread number
       * is tracked */
      OS_ThreadArray[u8ThreadPrio]= me;
      /* Store the user specific thread priority in the thread control block */
      me->prio = u8ThreadPrio;
      /* Set the started thread (except the idle thread)
       * to ready-to-run state by setting the bit mask */
      if(u8ThreadPrio > 0u)
      {
    	  OS_u32ReadySet |= (1u << (u8ThreadPrio - 1u));
      }
      /* The increment is not rquired in the case of priorities since the
       * threads are stored in the array based on priorities and not
       * consecutively.
       */
      /* Increment the number of threads started counter */
      //++u8ThreadPrio;
}

/* Puts the Thread in the blocked state */
void OS_Delay(uint32_t u32ticks)
{
	uint32_t u32Bit = 0u;
	__disable_irq();

	u32Bit = (1u << (OS_curr->prio - 1u));
	/* NOTE: To increase the safety and safeguard the delay function
	 * from being called by the IDLE thread add an ASSERTION
	 * that the current thread is not in the idle thread
	 */
	/* Needs to be revisited when the assert file is added to
	 * the include path */
	OS_curr->timeout = u32ticks;

	/* Indicate the task as blocked by updating the ready and delayed set */
	OS_u32ReadySet &= ~u32Bit;
    OS_u32DelayedSet |= u32Bit;
    /* Call the scheduler to switch context to another
     * thread in the array that is in the ready state. The context switch
     * will happen only after the interrupts are enabled.
     */
	OS_vSched();
	__enable_irq();
}

/* Removes the Thread out of the blocked state
 * Description: Iterates through the thread array at every systick interrupt
 * and check the timeout corresponding to the respective thread if it is not
 * zero decrement the timeout, else set the corresponding thread to the running state*/
void OS_vTick(void)
{
	uint32_t u32WorkingSet = OS_u32DelayedSet;
	uint32_t u32bit = 0U;
	OS_THREAD_T *sTemp = (OS_THREAD_T *)0;

	while(u32WorkingSet != 0u)
	{
		sTemp = OS_ThreadArray[LOG2(u32WorkingSet)];

		u32bit = (1u << (sTemp->prio -  1u));

        /* Continue executing if sTemp points to something, else halt
         * Use ASSERT here once created*/

		/* Decrement the timeout for the corresponding thread */
		--(sTemp->timeout);

		/* Check in advance that the timeout value for this thread is zero and
		 * remove it from the delayed set and update the readyset bit-mask
		 */
		if(sTemp->timeout == 0u)
		{
			OS_u32ReadySet |= u32bit;
			OS_u32DelayedSet &= ~u32bit;
		}

		/* Update the working set */
		u32WorkingSet &= ~u32bit;
	}
}

void OS_IdleTask(void)
{
    while(1)
    {
       OS_vOnIdle();
    }
}


__attribute__((naked)) void PendSV_Handler(void)
{
//	void *sp;
//
//	__disable_irq();
//	if(OS_curr != (OS_THREAD_T *)0)
//	{
//		/*PUSH R4-R11 onto the stack*/
//		/*Save the SP register contents in the SP data member*/
//		OS_curr->pvThreadSP = sp;
//	}
//	/*Store the private sp data member of the thread to be scheduled to the SP register*/
//	sp = OS_next->pvThreadSP;
//	OS_curr = OS_next;
//	/*POP R4-R11*/
//	__enable_irq();
	__asm volatile(
			"cpsid i                \n"
			"ldr r3, =OS_curr       \n"
			"ldr r3, [r3]           \n"
			"cmp r3, #0             \n"
			"beq PendSV_Restore     \n"

			"push {r4-r11}          \n"
			"ldr r3, =OS_curr       \n"
			"ldr r3, [r3]           \n"
			"str sp, [r3]           \n"

			"PendSV_Restore:        \n"
			"ldr r3, =OS_next       \n"
			"ldr r3, [r3]           \n"
			"ldr r3, [r3]           \n"
			"mov sp, r3             \n"

			"ldr r3, =OS_next       \n"
			"ldr r3, [r3]           \n"
			"ldr r2, =OS_curr       \n"
			"str r3, [r2]           \n"

			"pop {r4-r11}           \n"
			"cpsie i                \n"
			"bx lr                  \n"
	   );


}
