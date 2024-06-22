/*
 *  flow_control.c
 *
 *  Created on: Jun 18, 2024
 *  Author: Zidane D'souza
 */
/******************************************************************
 *                       HEADER FILES
 ******************************************************************/
#include "flow_control.h"
/* Author: Zidane D'souza
 *
 * Description: This particular functions shows the normal and hard way to increment a counter
 *
 * Parameter: Void
 */
extern void flow_control_Counter_Inc_Manual(void)
{
   static int counter = 0;

   counter++;
   counter++;
   counter++;
   counter++;
   counter++;
   counter++;
   counter++;
   counter++;
   counter++;
}

/* Author: Zidane D'souza
 *
 * Description: This particular functions shows the easy way to increment a counter
 *
 * Parameter: Void
 */
extern void flow_control_Counter_Inc_Loop(void)
{
   static int counter = 0;
   while(counter < 10)
   {
	   counter++;
   }
}

/* Author: Zidane D'souza
 *
 * Description: This particular functions shows an optimized way to increment the counter
 *
 * Parameter: Void
 */
extern void flow_control_Counter_Inc_Loop_Optimized(void)
{
   static int counter = 0;
   static int iterations = 10;
   static int iterations_after_unrolling_loop = 2;
   while(counter < iterations - iterations_after_unrolling_loop )
   {
	   counter++;
	   counter++;
   }
   /*since my desired iterations are 10 and due to optimization and to improve speed we unroll
    * the loop.
    */
   counter++;
   counter++;
}
