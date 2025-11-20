#ifndef __USART_H_
#define __USART_H_

#include <stdint.h>
#include "stm32f302x8.h"

#define SYSCLK_D       16000000
#define PERIPH_CLK_D   SYSCLK_D
#define UART_BAUD_RATE_D 115200

extern void USART_vInit(void);
extern void USART_vWrite(uint16_t ch);

#endif
