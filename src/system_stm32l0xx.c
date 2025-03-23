/**********************************************************************************************************************
 * \file system_stm32l0xx.c
 *
 * \author  STMicroelectronics
 *
 * \date Oct-03-2024
 *
 * \version 1.0 \n \n
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Copyright (c) 2016 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *********************************************************************************************************************/

#include "stm32l0xx.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(HSE_VALUE)
#define HSE_VALUE ((uint32_t)8000000U) /*!< Value of the External oscillator in Hz */
#endif                                 /* HSE_VALUE */

#if !defined(MSI_VALUE)
#define MSI_VALUE ((uint32_t)2097152U) /*!< Value of the Internal oscillator in Hz*/
#endif                                 /* MSI_VALUE */

#if !defined(HSI_VALUE)
#define HSI_VALUE ((uint32_t)16000000U) /*!< Value of the Internal oscillator in Hz*/
#endif                                  /* HSI_VALUE */

uint32_t      SystemCoreClock   = 2097152U; /* 32.768 kHz * 2^6 */
const uint8_t AHBPrescTable[16] = { 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 1U, 2U, 3U, 4U, 6U, 7U, 8U, 9U };
const uint8_t APBPrescTable[8]  = { 0U, 0U, 0U, 0U, 1U, 2U, 3U, 4U };
const uint8_t PLLMulTable[9]    = { 3U, 4U, 6U, 8U, 12U, 16U, 24U, 32U, 48U };

void SystemInit(void)
{
}

void SystemCoreClockUpdate(void)
{
}

#ifdef __cplusplus
}
#endif
