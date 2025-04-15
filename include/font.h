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

typedef struct {
    const void* data;         // font
    uint8_t char_width;       
    uint8_t char_height;       
  } Font_t;

// extern const uint16_t FONT7x10[];
// extern const uint16_t FONT11x18[];
extern const uint16_t FONT16x26[];



#ifdef __cplusplus
}
#endif

#endif // FONT_H