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

#include <ssd1315.h>
#include <stdint.h>
#include <font.h>

#ifdef __cplusplus
extern "C" {
#endif

void SSD1315_DrawChar(SSD1315_Object_t* pObj, uint8_t x, uint8_t y, char c);
void SSD1315_DrawChar_7x10(SSD1315_Object_t* pObj, uint8_t x, uint8_t y, char c);
void SSD1315_DrawChar_Generic(SSD1315_Object_t* pObj, uint8_t x, uint8_t y, char c, const Font_t* font);
void SSD1315_DrawString_Generic(SSD1315_Object_t* pObj, uint8_t x, uint8_t y, const char* str, const Font_t* font);

#ifdef __cplusplus
}
#endif

#endif // SSD1315_SERVICE_H