#include <ssd1315.h>
#include <stm32l0xx_hal.h>

#ifdef __cplusplus
extern "C" {
#endif

// I2C TIMING is calculated in case of the I2C Clock source is the SYSCLK = 32 MHz
#define I2C_TIMING  268501508U // 100 kHz with analog Filter ON, Rise Time 1000ns, Fall Time 1000ns
#define I2C_ADDRESS 0x3C
#define I2Cx        I2C1

void           SystemClock_Config(void);
static int32_t SSD1315_Initialize(void);
static int32_t SSD1315_DeInitialize(void);
static int32_t SSD1315_WriteCommand(uint16_t Addr, uint8_t* pData, uint16_t Length);
static int32_t SSD1315_ReadData(uint16_t Addr, uint8_t* pData, uint16_t Length);
static int32_t SSD1315_GetTick(void);

uint8_t aTxBuffer[] = { 1u };
uint8_t aRxBuffer[2];
uint8_t centerX = SSD1315_LCD_PIXEL_WIDTH / 2;
uint8_t centerY = SSD1315_LCD_PIXEL_HEIGHT / 2;
uint8_t radius  = 15;

SSD1315_IO_t SSD1315_IO = {
  .Init     = SSD1315_Initialize,
  .DeInit   = SSD1315_DeInitialize,
  .WriteReg = SSD1315_WriteCommand,
  .ReadReg  = SSD1315_ReadData,
  .GetTick  = SSD1315_GetTick,
};

SSD1315_Object_t  SSD1315_Obj;
I2C_HandleTypeDef t_iicHandle;
void              DrawCircle(uint8_t x0, uint8_t y0, uint8_t radius);

int main()
{
  HAL_Init();

  // Configure the system clock to 2 MHz
  SystemClock_Config();

  t_iicHandle.Instance              = I2Cx;
  t_iicHandle.Init.Timing           = I2C_TIMING;
  t_iicHandle.Init.OwnAddress1      = I2C_ADDRESS;
  t_iicHandle.Init.AddressingMode   = I2C_ADDRESSINGMODE_7BIT;
  t_iicHandle.Init.DualAddressMode  = I2C_DUALADDRESS_DISABLE;
  t_iicHandle.Init.OwnAddress2      = 0xFF;
  t_iicHandle.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  t_iicHandle.Init.GeneralCallMode  = I2C_GENERALCALL_DISABLE;
  t_iicHandle.Init.NoStretchMode    = I2C_NOSTRETCH_DISABLE;

  HAL_I2C_Init(&t_iicHandle);

  // Enable the Analog I2C Filter
  HAL_I2CEx_ConfigAnalogFilter(&t_iicHandle, I2C_ANALOGFILTER_ENABLE);

  // HAL_I2C_Master_Transmit(&t_iicHandle, (uint16_t)I2C_ADDRESS<<1, (uint8_t*)aTxBuffer, 1, 10000);
  // HAL_I2C_Master_Receive(&t_iicHandle, u_command, (uint8_t *)aRxBuffer, 1, 10000);

  if(SSD1315_RegisterBusIO(&SSD1315_Obj, &SSD1315_IO) != SSD1315_OK)
  {
    while(1); // Error
  }

  DrawCircle(centerX, centerY, radius);

  SSD1315_Refresh(&SSD1315_Obj);

  // Infinite loop
  while(1)
  {
  }
}

// Algoritmo de Bresenham para dibujar un círculo
void DrawCircle(uint8_t x0, uint8_t y0, uint8_t radius)
{
  int x   = radius;
  int y   = 0;
  int err = 0;

  while(x >= y)
  {
    // Dibuja los 8 octantes
    SSD1315_SetPixel(&SSD1315_Obj, x0 + x, y0 + y, SSD1315_COLOR_WHITE);
    SSD1315_SetPixel(&SSD1315_Obj, x0 + y, y0 + x, SSD1315_COLOR_WHITE);
    SSD1315_SetPixel(&SSD1315_Obj, x0 - y, y0 + x, SSD1315_COLOR_WHITE);
    SSD1315_SetPixel(&SSD1315_Obj, x0 - x, y0 + y, SSD1315_COLOR_WHITE);
    SSD1315_SetPixel(&SSD1315_Obj, x0 - x, y0 - y, SSD1315_COLOR_WHITE);
    SSD1315_SetPixel(&SSD1315_Obj, x0 - y, y0 - x, SSD1315_COLOR_WHITE);
    SSD1315_SetPixel(&SSD1315_Obj, x0 + y, y0 - x, SSD1315_COLOR_WHITE);
    SSD1315_SetPixel(&SSD1315_Obj, x0 + x, y0 - y, SSD1315_COLOR_WHITE);

    y++;
    err += 1 + 2 * y;
    if(2 * (err - x) + 1 > 0)
    {
      x--;
      err += 1 - 2 * x;
    }
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

static int32_t SSD1315_Initialize(void)
{
  // Inicializar pantalla
  if(SSD1315_Init(&SSD1315_Obj, SSD1315_FORMAT_DEFAULT, SSD1315_ORIENTATION_LANDSCAPE) != SSD1315_OK)
  {
    while(1);
  }

  // Encendido de la pantalla
  if(SSD1315_DisplayOn(&SSD1315_Obj) != SSD1315_OK)
  {
    // Manejo de error
    while(1);
  }

  return 0;
}

static int32_t SSD1315_DeInitialize(void)
{
  return 0;
}

static int32_t SSD1315_WriteCommand(uint16_t Addr, uint8_t* pData, uint16_t Length)
{
  if(HAL_I2C_Master_Transmit(&t_iicHandle, (uint16_t)I2C_ADDRESS << 1, pData, Length, 1000000) == HAL_OK)
  {
    return 0;
  }
  return -1;
}

static int32_t SSD1315_ReadData(uint16_t Addr, uint8_t* pData, uint16_t Length)
{
  return -1; // No aplicable para SSD1315 en la mayoría de los casos
}

static int32_t SSD1315_GetTick(void)
{
  return HAL_GetTick();
}

#ifdef __cplusplus
}
#endif
