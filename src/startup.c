/**********************************************************************************************************************
 * \file startup.c
 *
 * \author  Marco Aguilar
 *
 * \date Sep-25-2024
 *
 * \version 1.0 \n \n
 *
 *********************************************************************************************************************/

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern uint32_t _estack;
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

int main(void);

void Default_Handler(void)
{
  while(1);
}

void Reset_Handler(void)
{
  uint32_t* psrc = &_sidata;
  uint32_t* pdst = &_sdata;

  while(pdst < &_edata)
  {
    *pdst = *psrc;
    ++psrc;
    ++pdst;
  }

  pdst = &_sbss;
  while(pdst < &_ebss)
  {
    *pdst = 0;
    ++pdst;
  }

  main();

  while(1);
}

/*******************************************************************************
 *            Interrupt table prototype
 ******************************************************************************/
void Reset_Handler(void);
void Default_Handler(void);
void NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void) __attribute__((weak, alias("Default_Handler")));
void WWDG_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void PVD_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void RTC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void FLASH_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void RCC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI0_1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI2_3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXTI4_15_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel2_3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA1_Channel4_7_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void ADC_COMP_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void LPTIM1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void USART4_USART5_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM6_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM7_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM21_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void I2C3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIM22_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void I2C1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void I2C2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SPI1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SPI2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void USART1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void USART2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void AES_RNG_LPUART1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));

/*******************************************************************************
 *            Vector Table definition
 ******************************************************************************/
uint32_t vector_table[] __attribute__((section(".isr_vector"))) = {
  (uint32_t)&_estack,           // Initial Stack Pointer
  (uint32_t)&Reset_Handler,     // Reset Handler
  (uint32_t)&NMI_Handler,       // NMI Handler
  (uint32_t)&HardFault_Handler, // Hard Fault Handler
  (uint32_t)0,                  // Reserved
  (uint32_t)0,                  // Reserved
  (uint32_t)0,                  // Reserved
  (uint32_t)0,                  // Reserved
  (uint32_t)0,                  // Reserved
  (uint32_t)0,                  // Reserved
  (uint32_t)0,                  // Reserved
  (uint32_t)&SVC_Handler,       // SVCall Handler
  (uint32_t)0,                  // Reserved
  (uint32_t)0,                  // Reserved
  (uint32_t)&PendSV_Handler,    // PendSV Handler
  (uint32_t)&SysTick_Handler,   // SysTick Handler
  // External Interrupts
  (uint32_t)&WWDG_IRQHandler,            // Window Watchdog
  (uint32_t)&PVD_IRQHandler,             // PVD through EXTI Line detect
  (uint32_t)&RTC_IRQHandler,             // RTC through EXTI Line
  (uint32_t)&FLASH_IRQHandler,           // FLASH
  (uint32_t)&RCC_IRQHandler,             // RCC
  (uint32_t)&EXTI0_1_IRQHandler,         // EXTI Line 0 and 1
  (uint32_t)&EXTI2_3_IRQHandler,         // EXTI Line 2 and 3
  (uint32_t)&EXTI4_15_IRQHandler,        // EXTI Line 4 to 15
  (uint32_t)0,                           // Reserved
  (uint32_t)&DMA1_Channel1_IRQHandler,   // DMA1 Channel 1
  (uint32_t)&DMA1_Channel2_3_IRQHandler, // DMA1 Channel 2 and Channel 3
  (uint32_t)&DMA1_Channel4_7_IRQHandler, // DMA1 Channel 4, Channel 5, Channel 6 and Channel 7
  (uint32_t)&ADC_COMP_IRQHandler,        // ADC1, COMP1
  (uint32_t)&LPTIM1_IRQHandler,          // LPTIM1
  (uint32_t)&USART4_USART5_IRQHandler,   // USART4/USART5
  (uint32_t)&TIM2_IRQHandler,            // TIM2
  (uint32_t)&TIM3_IRQHandler,            // TIM3
  (uint32_t)&TIM6_IRQHandler,            // TIM6
  (uint32_t)&TIM7_IRQHandler,            // TIM7
  (uint32_t)0,                           // Reserved
  (uint32_t)&TIM21_IRQHandler,           // TIM21
  (uint32_t)&I2C3_IRQHandler,            // I2C3
  (uint32_t)&TIM22_IRQHandler,           // TIM22
  (uint32_t)&I2C1_IRQHandler,            // I2C1
  (uint32_t)&I2C2_IRQHandler,            // I2C2
  (uint32_t)&SPI1_IRQHandler,            // SPI1
  (uint32_t)&SPI2_IRQHandler,            // SPI2
  (uint32_t)&USART1_IRQHandler,          // USART1
  (uint32_t)&USART2_IRQHandler,          // USART2
  (uint32_t)&AES_RNG_LPUART1_IRQHandler, // AES_RNG_LPUART1
};

#ifdef __cplusplus
}
#endif
