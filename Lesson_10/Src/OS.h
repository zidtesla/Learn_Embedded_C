/*
 * OS.h
 *
 *  Created on: Mar 1, 2026
 *      Author: Zidane Dsouza
 */

#ifndef OS_H_
#define OS_H_

#include <stdint.h>

typedef struct
{
	void *pvThreadSP;
}OS_THREAD_T;

typedef  void (*OS_THREAD_HANDLER_T)();

void OS_vThreadStart(OS_THREAD_T *me, OS_THREAD_HANDLER_T ThreadHandler,\
		void *PrivStackMmry, uint32_t u32stackSize);


#endif /* OS_H_ */
