/**********************************************************************************************************************
 * \file ssd1315_service.h
 *
 * \author  Marco Aguilar
 *
 * \date April-13-2025
 *
 * \version 1.0 \n \n
 *
 *********************************************************************************************************************/

#ifndef SSD1315_SERVICE_H
#define SSD1315_SERVICE_H

#include <font.h>
#include <ssd1315.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void SSD1315_v_DrawChar(SSD1315_Object_t* t_pObj, uint8_t u_posX, uint8_t u_posY, char c_char, const Font_t* t_font);
void SSD1315_v_DrawString(SSD1315_Object_t* p_obj, uint8_t u_posX, uint8_t u_posY, const char* p_str, const Font_t* t_font);

#ifdef __cplusplus
}
#endif

#endif // SSD1315_SERVICE_H