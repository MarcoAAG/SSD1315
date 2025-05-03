/**********************************************************************************************************************
 * \file font.h
 *
 * \author  Marco Aguilar
 *
 * \date April-13-2025
 *
 * \version 1.0 \n \n
 *
 *********************************************************************************************************************/

#ifndef FONT_H
#define FONT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
  const void* p_data; // font
  uint8_t     u_charWidth;
  uint8_t     u_charHeight;
} Font_t;

extern const uint32_t FONT32x56[];

#ifdef __cplusplus
}
#endif

#endif // FONT_H