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

#include <font.h>
#include <ssd1315_service.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void SSD1315_DrawChar(SSD1315_Object_t* pObj, uint8_t x, uint8_t y, char c)
{
  if(c < 'A' || c > 'Z')
    return; // solo mayúsculas

  const uint8_t* bitmap = font_8x11_AZ[c - 'A'];
  for(uint8_t row = 0; row < 11; row++)
  {
    for(uint8_t col = 0; col < 8; col++)
    {
      if(bitmap[row] & (1 << (7 - col)))
      {
        SSD1315_SetPixel(pObj, x + col, y + row, SSD1315_COLOR_WHITE);
      }
      else
      {
        SSD1315_SetPixel(pObj, x + col, y + row, SSD1315_COLOR_BLACK); // opcional
      }
    }
  }
}

#ifdef __cplusplus
}
#endif