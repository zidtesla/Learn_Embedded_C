/*
 * startup_stm32f302r8tx.c
 *
 *  Created on: Oct 13, 2025
 *      Author: Zidane
 */
#include <stdint.h>
#include <assert.h>
#include <system_stm32f3xx.h>
#include "stm32f302x8.h"
#include "core_cm4.h"

extern int main(void);
extern void __libc_init_array(void);
extern
// Forward declarations of handlers
void Reset_Handler(void);
void Default_Handler(void);
void NMI_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void)      __attribute__((weak, alias("Default_Handler")));

// Peripheral IRQ prototypes
void WWDG_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));
void PVD_IRQHandler(void)             __attribute__((weak, alias("Default_Handler")));
void TAMP_STAMP_IRQHandler(void)      __attribute__((weak, alias("Default_Handler")));
void RTC_WKUP_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void FLASH_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));
void RCC_IRQHandler(void)             __attribute__((weak, alias("Default_Handler")));
void EXTI0_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));
void EXTI1_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));
void EXTI2_TSC_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void EXTI3_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));
void EXTI4_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));
void DMA1_CH1_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void DMA1_CH2_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void DMA1_CH3_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void DMA1_CH4_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void DMA1_CH5_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void DMA1_CH6_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void DMA1_CH7_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void ADC1_2_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
void USB_HP_CAN_TX_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void USB_LP_CAN_RX0_IRQHandler(void)  __attribute__((weak, alias("Default_Handler")));
void CAN_RX1_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
void CAN_SCE_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
void EXTI9_5_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
void TIM1_BRK_TIM15_IRQHandler(void)  __attribute__((weak, alias("Default_Handler")));
void TIM1_UP_TIM16_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void TIM1_TRG_COM_TIM17_IRQHandler(void)__attribute__((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
void TIM2_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));
void TIM3_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));
void TIM4_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));
void I2C1_EV_EXTI23_IRQHandler(void)  __attribute__((weak, alias("Default_Handler")));
void I2C1_ER_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
void I2C2_EV_EXTI24_IRQHandler(void)  __attribute__((weak, alias("Default_Handler")));
void I2C2_ER_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
void SPI1_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));
void SPI2_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));
void USART1_EXTI25_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void USART2_EXTI26_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void USART3_EXTI28_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void EXTI15_10_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
void RTCAlarm_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void USB_WKUP_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void TIM8_BRK_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void TIM8_UP_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
void TIM8_TRG_COM_IRQHandler(void)    __attribute__((weak, alias("Default_Handler")));
void TIM8_CC_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
void ADC3_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));
void FMC_IRQHandler(void)             __attribute__((weak, alias("Default_Handler")));
void SPI3_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));
void UART4_EXTI34_IRQHandler(void)    __attribute__((weak, alias("Default_Handler")));
void UART5_EXTI35_IRQHandler(void)    __attribute__((weak, alias("Default_Handler")));
void TIM6_DACUNDER_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
void TIM7_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));
void DMA2_CH1_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void DMA2_CH2_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void DMA2_CH3_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void DMA2_CH4_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void DMA2_CH5_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
void ADC4_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));
void USB_HP_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
void USB_LP_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
void USB_WKUP_EXTI_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));

// Symbols defined in linker script
extern uint32_t _estack;   // Top of RAM
extern uint32_t _sidata;   // Start of .data in Flash
extern uint32_t _sdata;    // Start of .data in RAM
extern uint32_t _edata;    // End of .data in RAM
extern uint32_t _sbss;     // Start of .bss
extern uint32_t _ebss;     // End of .bss

// Vector table placed at start of flash
__attribute__((section(".isr_vector")))
const void* vector_table[] =
{
    (void*)&_estack,          // Initial MSP value
    Reset_Handler,            // Reset handler
    NMI_Handler,              // NMI
    HardFault_Handler,        // HardFault
    0,                        // Reserved
    0,                        // Reserved
    0,                        // Reserved
    0,                        // Reserved
    0,                        // Reserved
    0,                        // Reserved
    0,                        // Reserved
    SVC_Handler,              // SVCall
    0,                        // Reserved for Debug
    0,                        // Reserved
    PendSV_Handler,           // PendSV (used for context switching)
    SysTick_Handler,          // SysTick
	// External Interrupts
	WWDG_IRQHandler,
	PVD_IRQHandler,
	TAMP_STAMP_IRQHandler,
	RTC_WKUP_IRQHandler,
	FLASH_IRQHandler,
	RCC_IRQHandler,
	EXTI0_IRQHandler,
	EXTI1_IRQHandler,
	EXTI2_TSC_IRQHandler,
	EXTI3_IRQHandler,
	EXTI4_IRQHandler,
	DMA1_CH1_IRQHandler,
	DMA1_CH2_IRQHandler,
	DMA1_CH3_IRQHandler,
	DMA1_CH4_IRQHandler,
	DMA1_CH5_IRQHandler,
	DMA1_CH6_IRQHandler,
	DMA1_CH7_IRQHandler,
	ADC1_2_IRQHandler,
	USB_HP_CAN_TX_IRQHandler,
	USB_LP_CAN_RX0_IRQHandler,
	CAN_RX1_IRQHandler,
	CAN_SCE_IRQHandler,
	EXTI9_5_IRQHandler,
	TIM1_BRK_TIM15_IRQHandler,
	TIM1_UP_TIM16_IRQHandler,
	TIM1_TRG_COM_TIM17_IRQHandler,
	TIM1_CC_IRQHandler,
	TIM2_IRQHandler,
	TIM3_IRQHandler,
    TIM4_IRQHandler,
	I2C1_EV_EXTI23_IRQHandler,
	I2C1_ER_IRQHandler,
	I2C2_EV_EXTI24_IRQHandler,
	I2C2_ER_IRQHandler,
	SPI1_IRQHandler,
	SPI2_IRQHandler,
	USART1_EXTI25_IRQHandler,
	USART2_EXTI26_IRQHandler,
	USART3_EXTI28_IRQHandler,
	EXTI15_10_IRQHandler,
	RTCAlarm_IRQHandler,
	USB_WKUP_IRQHandler,
	TIM8_BRK_IRQHandler,
	TIM8_UP_IRQHandler,
	TIM8_TRG_COM_IRQHandler,
	TIM8_CC_IRQHandler,
	ADC3_IRQHandler,
	FMC_IRQHandler,
	0,
	0,                          // Reserved
	SPI3_IRQHandler,
	UART4_EXTI34_IRQHandler,
	UART5_EXTI35_IRQHandler,
	TIM6_DACUNDER_IRQHandler,
	TIM7_IRQHandler,
	DMA2_CH1_IRQHandler,
	DMA2_CH2_IRQHandler,
	DMA2_CH3_IRQHandler,
	DMA2_CH4_IRQHandler,
	DMA2_CH5_IRQHandler,
	ADC4_IRQHandler,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,      // Reserved
	USB_HP_IRQHandler,
	USB_LP_IRQHandler,
	USB_WKUP_EXTI_IRQHandler
};

// Reset handler: called on MCU startup
void Reset_Handler(void)
{

    /* Initialize data/bss sections */
	uint32_t *src;
	uint32_t *dst;

	src = &_sidata;
	dst = &_sdata;

    /* Copy the .data from flash to the .data in RAM */
	while(dst < (uint32_t *)&_edata)
	{
		*dst = *src;
		dst++;
		src++;
	}

	/* Uninitialized global or static variables are initialized to zero */
	dst = &_sbss;
	while(dst < (uint32_t *)&_ebss)
	{
		*dst = 0;
		dst++;
	}

	/* Run all global constructors before main */
	__libc_init_array();

    /* Call SystemInit() */
	SystemInit();

    /* Call main() */
	main();

    while (1);
}

void Default_Handler()
{
	assert(0 && "Unexpected interrupt");
	NVIC_SystemReset();
}
