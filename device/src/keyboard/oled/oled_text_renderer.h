#ifndef __OLED_TEXT_RENDERER_H__
#define __OLED_TEXT_RENDERER_H__

// Includes:

#include <inttypes.h>
#include "lvgl/lvgl.h"

// Macros:

// Variables:

// Functions:

void Oled_DrawText(uint16_t x, uint16_t y, const lv_font_t* font, const char* text);
void Oled_LogConstant(const char* text);
void Oled_Log(const char *fmt, ...);

#endif
