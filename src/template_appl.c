#include <stm32l0xx_hal.h>

#ifdef __cplusplus
extern "C" {
#endif

void SystemClock_Config(void);

int main()
{
  HAL_Init();

  // Configure the system clock to 2 MHz
  SystemClock_Config();

  // Infinite loop
  while(1)
  {
  }
}

/*******************************************************************************
 *
 * \brief System Clock Configuration \n
 *        The system Clock is configured as follow : \n
 *            System Clock source            = MSI      \n
 *            SYSCLK(Hz)                     = 2000000  \n
 *            HCLK(Hz)                       = 2000000  \n
 *            AHB Prescaler                  = 1        \n
 *            APB1 Prescaler                 = 1        \n
 *            APB2 Prescaler                 = 1        \n
 *            Flash Latency(WS)              = 0        \n
 *
 ******************************************************************************/
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
  RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };

  // Enable MSI Oscillator
  RCC_OscInitStruct.OscillatorType      = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState            = RCC_MSI_ON;
  RCC_OscInitStruct.MSIClockRange       = RCC_MSIRANGE_5;
  RCC_OscInitStruct.MSICalibrationValue = 0x00;
  RCC_OscInitStruct.PLL.PLLState        = RCC_PLL_NONE;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    // Initialization Error
    while(1);
  }

  /* Select MSI as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType      = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    // Initialization Error
    while(1);
  }
  // Enable Power Control clock
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
}

#ifdef __cplusplus
}
#endif
