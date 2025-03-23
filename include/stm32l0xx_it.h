/**********************************************************************************************************************
 * \file stm32l0xx_it.h
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

#ifndef __STM32L0xx_IT_H
#define __STM32L0xx_IT_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *
 * \brief This function is used to
 *
 * \param [in] None
 * \param [out] None
 *
 * \return  None
 *
 ******************************************************************************/
void NMI_Handler(void);

/*******************************************************************************
 *
 * \brief This function is used to
 *
 * \param [in] None
 * \param [out] None
 *
 * \return  None
 *
 ******************************************************************************/
void HardFault_Handler(void);

/*******************************************************************************
 *
 * \brief This function is used to
 *
 * \param [in] None
 * \param [out] None
 *
 * \return  None
 *
 ******************************************************************************/
void SVC_Handler(void);

/*******************************************************************************
 *
 * \brief This function is used to
 *
 * \param [in] None
 * \param [out] None
 *
 * \return  None
 *
 ******************************************************************************/
void PendSV_Handler(void);

/*******************************************************************************
 *
 * \brief This function is used to
 *
 * \param [in] None
 * \param [out] None
 *
 * \return  None
 *
 ******************************************************************************/
void SysTick_Handler(void);

#ifdef __cplusplus
}
#endif

#endif // __STM32L0xx_IT_H
