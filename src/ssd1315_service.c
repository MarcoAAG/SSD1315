/**********************************************************************************************************************
 * \file ssd1315_service.c
 *
 * \author  Marco Aguilar
 *
 * \date April-13-2025
 *
 * \version 1.0 \n \n
 *
 *********************************************************************************************************************/

#include <ssd1315_service.h>
#include <stdint.h>
#include <stm32l0xx_hal.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

static int32_t SSD1315_Initialize(void);
static int32_t SSD1315_DeInitialize(void);
static int32_t SSD1315_WriteCommand(uint16_t Addr, uint8_t* pData, uint16_t Length);
static int32_t SSD1315_ReadData(uint16_t Addr, uint8_t* pData, uint16_t Length);
static int32_t SSD1315_GetTick(void);

SSD1315_IO_t SSD1315_IO = {
  .Init     = SSD1315_Initialize,
  .DeInit   = SSD1315_DeInitialize,
  .WriteReg = SSD1315_WriteCommand,
  .ReadReg  = SSD1315_ReadData,
  .GetTick  = SSD1315_GetTick,
};

// I2C TIMING is calculated in case of the I2C Clock source is the SYSCLK = 32 MHz
#define I2C_TIMING  268501508U // 100 kHz with analog Filter ON, Rise Time 1000ns, Fall Time 1000ns
#define I2C_ADDRESS 0x3C
#define I2Cx        I2C1

SSD1315_Object_t  SSD1315_Obj;
I2C_HandleTypeDef t_iicHandle;

/***************************************************************************
 * PUBLIC FUNCTIONS
***************************************************************************/

void SSD1315_v_Init(void)
{
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
  if(SSD1315_RegisterBusIO(&SSD1315_Obj, &SSD1315_IO) != SSD1315_OK)
  {
    while(1); // Error
  }
}

void SSD1315_v_PrintString(void)
{
  Font_t myFont;
  myFont.p_data       = FONT32x56;
  myFont.u_charHeight = 56;
  myFont.u_charWidth  = 32;
  SSD1315_v_DrawString(&SSD1315_Obj, 14, 4, "37%", &myFont);
  SSD1315_Refresh(&SSD1315_Obj);
}

void SSD1315_v_DrawChar(SSD1315_Object_t* t_pObj, uint8_t u_posX, uint8_t u_posY, char c_char, const Font_t* t_font)
{
  const char s_VALIDCHARS[] = "%0123456789";

  // Verify if is valid char
  const char* s_CHARPOS = strchr(s_VALIDCHARS, c_char);

  // Get index based on char position
  uint32_t char_index = (s_CHARPOS - s_VALIDCHARS) * t_font->u_charHeight;

  // Get char's bitmap
  const uint32_t* p_bitmap = (const uint32_t*)t_font->p_data + char_index;

  for(uint8_t u_row = 0; u_row < t_font->u_charHeight; u_row++)
  {
    uint32_t u_rowData = p_bitmap[u_row];

    for(uint8_t u_col = 0; u_col < t_font->u_charWidth; u_col++)
    {
      if(u_rowData & (1 << (31 - u_col))) // MSB first
      {
        SSD1315_SetPixel(t_pObj, u_posX + u_col, u_posY + u_row, SSD1315_COLOR_WHITE);
      }
      else
      {
        SSD1315_SetPixel(t_pObj, u_posX + u_col, u_posY + u_row, SSD1315_COLOR_BLACK);
      }
    }
  }
}

void SSD1315_v_DrawString(SSD1315_Object_t* p_obj, uint8_t u_posX, uint8_t u_posY, const char* p_str, const Font_t* t_font)
{
  uint8_t u_offsetX  = 0;
  uint8_t u_tracking = 2; // 2 pixels of space between chars

  while(*p_str)
  {
    SSD1315_v_DrawChar(p_obj, u_posX + u_offsetX, u_posY, *p_str, t_font);
    u_offsetX += t_font->u_charWidth + u_tracking; // Go to next char
    p_str++;
  }
}

/***************************************************************************
 * STATIC FUNCTIONS
***************************************************************************/

static int32_t SSD1315_Initialize(void)
{
  uint8_t u_iicStat = 0;

  u_iicStat = SSD1315_Init(&SSD1315_Obj, SSD1315_FORMAT_DEFAULT, SSD1315_ORIENTATION_LANDSCAPE);
  if(u_iicStat == SSD1315_OK)
  {
    u_iicStat = SSD1315_DisplayOn(&SSD1315_Obj);
  }

  return u_iicStat;
}

static int32_t SSD1315_DeInitialize(void)
{
  return 0;
}

static int32_t SSD1315_WriteCommand(uint16_t Addr, uint8_t* pData, uint16_t Length)
{
  uint8_t        u_iicStat    = 0;
  const uint32_t u_timeoutIIC = 1000000;
  uint8_t        u_buffer[Length + 1];

  if(Length > 1)
  {
    u_buffer[0] = 0x40; // Data
  }
  else
  {
    u_buffer[0] = 0; // Control
  }

  memcpy(&u_buffer[1], pData, Length); // Add register before payload

  u_iicStat = HAL_I2C_Master_Transmit(&t_iicHandle, (uint16_t)I2C_ADDRESS << 1, u_buffer, Length + 1, u_timeoutIIC);

  return u_iicStat;
}

static int32_t SSD1315_ReadData(uint16_t Addr, uint8_t* pData, uint16_t Length)
{
  return -1;
}

static int32_t SSD1315_GetTick(void)
{
  return HAL_GetTick();
}

#ifdef __cplusplus
}
#endif