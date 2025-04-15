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

#ifdef __cplusplus
extern "C" {
#endif

void SSD1315_DrawChar_Generic(SSD1315_Object_t* pObj, uint8_t x, uint8_t y, char c, const Font_t* font)
{
  uint16_t char_index = (c - 32) * font->char_height;  // Suponemos que el primer carácter es ' '
  const uint16_t* bitmap = (const uint16_t*)font->data + char_index;

  for (uint8_t row = 0; row < font->char_height; row++)
  {
    uint16_t row_data = bitmap[row];

    for (uint8_t col = 0; col < font->char_width; col++)
    {
      if (row_data & (1 << (15 - col)))  // MSB first
      {
        SSD1315_SetPixel(pObj, x + col, y + row, SSD1315_COLOR_WHITE);
      }
      else
      {
        SSD1315_SetPixel(pObj, x + col, y + row, SSD1315_COLOR_BLACK);
      }
    }
  }
}

void SSD1315_DrawString_Generic(SSD1315_Object_t* pObj, uint8_t x, uint8_t y, const char* str, const Font_t* font)
{
  uint8_t offset_x = 0;

  while (*str) {
    SSD1315_DrawChar_Generic(pObj, x + offset_x, y, *str, font);
    offset_x += font->char_width + 2; // Mueve el puntero x para el siguiente carácter
    str++;
  }
}


#ifdef __cplusplus
}
#endif