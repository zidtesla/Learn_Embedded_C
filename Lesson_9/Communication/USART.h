#ifndef __USART_H_
#define __USART_H_

#include <stdint.h>
#include "stm32f302x8.h"

#define SYSCLK_D       16000000
#define PERIPH_CLK_D   SYSCLK_D
#define UART_BAUD_RATE_D 115200

extern void USART_vInit(void);
static uint32_t USART_u32ConfigDiv(uint32_t u32PeriphClk, uint32_t u32BaudRate);
static void USART_vSetBaudRate(USART_TypeDef *USARTx, uint32_t u32BaudRate);
extern void USART_vWrite(int ch);

#endif
