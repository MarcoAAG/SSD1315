/**********************************************************************************************************************
 * \file stm32l0xx_it.c
 *
 * \author  STMicroelectronics
 *
 * \date Sep-25-2024
 *
 * \version 1.0 \n \n
 *
 * Copyright (c) 2016 STMicroelectronics.
 * All rights reserved.
 *********************************************************************************************************************/

#include "stm32l0xx_it.h"
#include "stm32l0xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *            Cortex-M0+ Processor Exceptions Handlers
 ******************************************************************************/

void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while(1)
  {
  }
}

void SVC_Handler(void)
{
}

void PendSV_Handler(void)
{
}

void SysTick_Handler(void)
{
  HAL_IncTick();
}

#ifdef __cplusplus
}
#endif
