/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Zidane D'souza
 * @brief          : How do Computers count
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
#include "flow_control.h"
#include <stdint.h>

int main(void)
{
	/******The hard way******/
	flow_control_Counter_Inc_Manual();
	/******The easy way******/
	flow_control_Counter_Inc_Loop();
	/*But wait the loop has an overhead because of the branch instructions which stalls
	 * the pipeline for a few cycles. Check this function out.
	 */
	flow_control_Counter_Inc_Loop_Optimized();
    return 0 ;
}
