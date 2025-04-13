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

#ifdef __cplusplus
extern "C" {
#endif

void SSD1315_DrawChar(SSD1315_Object_t* pObj, uint8_t x, uint8_t y, char c);

#ifdef __cplusplus
}
#endif

#endif // SSD1315_SERVICE_H