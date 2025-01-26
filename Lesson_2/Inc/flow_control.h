/*
 *  flow_control.h
 *
 *  Created on: Jun 18, 2024
 *  Author: Zidane D'souza
 */

#ifndef _FLOW_CONTROL_H_
#define _FLOW_CONTROL_H_

/******************************************************************
 *                       PRIVATE FUNCTIONS
 ******************************************************************/
/*This particular functions shows the normal and hard way to increment a counter*/
extern void flow_control_Counter_Inc_Manual(void);
/* Description: This particular functions shows the easy way to increment a counter*/
extern void flow_control_Counter_Inc_Loop(void);
/*This particular functions shows an optimized way to increment the counter*/
extern void flow_control_Counter_Inc_Loop_Optimized(void);
#endif
