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
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif