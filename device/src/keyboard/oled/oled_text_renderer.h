#ifndef __OLED_TEXT_RENDERER_H__
#define __OLED_TEXT_RENDERER_H__

// Includes:

#include <inttypes.h>
#include "lvgl/lvgl.h"
#include "framebuffer.h"

// Macros:

// Variables:

// Typedefs:

typedef struct widget_t widget_t;

// Functions:

void Framebuffer_DrawText(widget_t* canvas, framebuffer_t* buffer, uint16_t x, uint16_t y, const lv_font_t* font, const char* text);

#endif
