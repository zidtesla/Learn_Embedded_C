/*
 * OS.c
 *
 *  Created on: Feb 28, 2026
 *      Author: Zidane Dsouza
 */

#include "OS.h"

OS_THREAD_T * volatile OS_curr;
OS_THREAD_T * volatile OS_next;

/* The array holds the list of threads to run
 * assuming the RTOS allows 32 threads and the +1 is the
 * idle thread
 */
OS_THREAD_T *OS_ThreadArray[32 + 1];

/* Bitmask of threads that are
 * ready to run
 */
uint32_t OS_u32ReadySet;

/* Current index of the thread */
uint8_t OS_u8CurrIndex;

/* Number of threads started so far */
uint8_t OS_u8ThreadNum;

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
			,&OS_IdleTask
			,PrivStackMmry
			,sizeof(PrivStackMmry));
}

void OS_vSched(void)
{
	/* Check if the idle thread needs to run */
	if(OS_u32ReadySet == 0u)
	{
		OS_u8CurrIndex = 0u;
	}
	/* Schedule the threads in the ready state */
	else
	{
		/* Keep checking for the thread in ready set list
		 * if its ready or not.
		 */
		do
		{
			++OS_u8CurrIndex;
			if(OS_u8CurrIndex == OS_u8ThreadNum)
			{
				OS_u8CurrIndex = 1u;
			}

		}while((OS_u32ReadySet & (1u << (OS_u8CurrIndex - 1u))) == 0u);

	}
	OS_next = OS_ThreadArray[OS_u8CurrIndex];

	if(OS_curr != OS_next)
	{
		/*Trigger the PENDSV interrupt*/
		*(uint32_t volatile *)0xE000ED04 |= (1 << 28);
	}
}

void OS_vThreadStart(OS_THREAD_T *me, OS_THREAD_HANDLER_T ThreadHandler,\
		void *PrivStackMmry, uint32_t u32stackSize)
{
	uint32_t *sp;
	uint32_t *pu32StackLimit;
	/* in ARM the stack grows from HIGH to LOW
	 * memory addresses*/
	/*The size/8 * 8 is for the 8byte alignment*/
	sp = (uint32_t *)((((uint32_t)PrivStackMmry + u32stackSize)/8)*8);

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
      /* But first check if the OS_u8ThreadNum < MAX_THREADS_D
       * USE AN ASSERT function to go into fault mode if this
       * condition fails.
       * NOTE: For now since there are just two tasks I am safe
       * but this will need to be revisited once the assert
       * functions are implemented.
       * */
      OS_ThreadArray[OS_u8ThreadNum]= me;

      /* Set the started thread (except the idle thread)
       * to ready-to-run state by setting the bit mask */
      if(OS_u8ThreadNum > 0u)
      {
    	  OS_u32ReadySet |= (1u << (OS_u8ThreadNum - 1u));
      }
      /* Increment the number of threads started counter */
      ++OS_u8ThreadNum;
}

/* Puts the Thread in the blocked state */
void OS_Delay(uint32_t u32ticks)
{
	__disable_irq();

	/* NOTE: To increase the safety and safeguard the delay function
	 * from being called by the IDLE thread add an ASSERTION
	 * that the current thread is not in the idle thread
	 */
	/* Needs to be revisited when the assert file is added to
	 * the include path */
	OS_curr->timeout = u32ticks;

	/* Indicate the task as blocked */
	OS_u32ReadySet &= ~(1u << (OS_u8CurrIndex - 1u));

    /* Call the scheduler to switch context to another
     * thread in the array that is in the ready state. The context switch
     * will happen only after the interrupts are enabled.
     */
	OS_vSched();
	__enable_irq();
}

/* Removes the Thread out of the blocked state
 * Description: Iterate through the thread array at every systick interrupt
 * and check the timeout corresponding to the respective thread if it is not
 * zero decrement the timeout, else set the corresponding thread to the running state*/
void OS_vTick(void)
{
	uint8_t u8ThreadIndex;
	for(u8ThreadIndex = 1u; u8ThreadIndex < OS_u8ThreadNum; u8ThreadIndex++)
	{
		if(OS_ThreadArray[u8ThreadIndex]->timeout != 0u)
		{
			--OS_ThreadArray[u8ThreadIndex]->timeout;
			/* Check before-hand if the timeout is zero and
			 * set the readyset bit mask to ready state
			 */
			if(OS_ThreadArray[u8ThreadIndex]->timeout == 0u)
			{
				OS_u32ReadySet |= (1u << (u8ThreadIndex - 1u));
			}
		}
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
