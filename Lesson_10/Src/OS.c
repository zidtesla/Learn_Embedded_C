/*
 * OS.c
 *
 *  Created on: Feb 28, 2026
 *      Author: Zidane Dsouza
 */

#include "OS.h"

OS_THREAD_T * volatile OS_curr;
OS_THREAD_T * volatile OS_next;

void OS_vInit(void)
{
	*(uint32_t volatile *)0xE000ED20 |= (0xFF << 16);
}

void OS_vSched(void)
{
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
