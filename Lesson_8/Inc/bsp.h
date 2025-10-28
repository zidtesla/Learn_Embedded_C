#ifndef __BSP_H_
#define __BSP_H_

#include "stm32f302x8.h"

#define SYSTICK_TICKS     ((uint32_t)4000000)
#define RCC_START_ADDR    0x40021000
#define RCC_AHBENR_OFFSET 0x14
#define RCC_AHBENR        (*((unsigned int volatile *)(RCC_START_ADDR + RCC_AHBENR_OFFSET)))
#define GPIO_B_START_ADDR 0x48000400
#define GPIO_B_MODER_OFST 0x00
#define GPIO_B_ODR_OFST   0x14
#define GPIO_B_PUPDR_OFST 0x0C
#define GPIO_B_BSRR_OFST  0x18
#define GPIO_B_MODER      (*((unsigned int volatile *)(GPIO_B_START_ADDR + GPIO_B_MODER_OFST)))
#define GPIO_B_ODR        (*((unsigned int volatile *)(GPIO_B_START_ADDR + GPIO_B_ODR_OFST)))
#define GPIO_B_PUPDR      (*((unsigned int volatile *)(GPIO_B_START_ADDR + GPIO_B_PUPDR_OFST)))
#define GPIO_B_BSRR       (*((unsigned int volatile *)(GPIO_B_START_ADDR + GPIO_B_BSRR_OFST)))

/* Function prototype */

/* This function resets the MCU whenever there is a fault in the system */
void assert_failed(const char *, int);
#endif
