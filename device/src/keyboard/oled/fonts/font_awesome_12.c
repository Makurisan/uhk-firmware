/*******************************************************************************
 * Size: 12 px
 * Bpp: 4
 * Opts: --lv-font-name FontAwesome12 --format lvgl --bpp 4 -o font_awesome_12.c --size 12 --font /opt/fontawesome/otfs/font_awesome_6_reguler.ttf --range 0xf057,0xf8dd,0xf1e6 --no-compress
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef FONTAWESOME12
#define FONTAWESOME12 1
#endif

#if FONTAWESOME12

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+F057 "" */
    0x0, 0x0, 0x13, 0x31, 0x0, 0x0, 0x0, 0x2,
    0xbf, 0xee, 0xfb, 0x20, 0x0, 0x4, 0xf9, 0x10,
    0x1, 0x8f, 0x50, 0x1, 0xf5, 0x0, 0x0, 0x0,
    0x4f, 0x20, 0x8a, 0x0, 0x30, 0x3, 0x0, 0x99,
    0xd, 0x40, 0xd, 0x98, 0xe0, 0x3, 0xe0, 0xe3,
    0x0, 0x1f, 0xf2, 0x0, 0x2f, 0xd, 0x40, 0x8,
    0xed, 0x90, 0x3, 0xe0, 0x8a, 0x0, 0xa2, 0x1a,
    0x0, 0x99, 0x1, 0xe5, 0x0, 0x0, 0x0, 0x4f,
    0x20, 0x4, 0xf9, 0x10, 0x1, 0x8f, 0x50, 0x0,
    0x2, 0xbf, 0xee, 0xfb, 0x20, 0x0, 0x0, 0x0,
    0x13, 0x31, 0x0, 0x0, 0x0,

    /* U+F1E6 "" */
    0x0, 0x50, 0x0, 0x50, 0x0, 0x1f, 0x0, 0xf,
    0x10, 0x2, 0xf0, 0x0, 0xf2, 0x1, 0x24, 0x22,
    0x24, 0x21, 0xdf, 0xff, 0xff, 0xff, 0xd4, 0xe0,
    0x0, 0x0, 0xe4, 0x3e, 0x0, 0x0, 0xe, 0x31,
    0xf2, 0x0, 0x2, 0xf1, 0x9, 0xc2, 0x2, 0xc9,
    0x0, 0x9, 0xfe, 0xf9, 0x0, 0x0, 0x1, 0xf1,
    0x0, 0x0, 0x0, 0xf, 0x0, 0x0, 0x0, 0x0,
    0x60, 0x0, 0x0,

    /* U+F8DD "" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xa,
    0x60, 0x0, 0x0, 0x0, 0x1d, 0x10, 0x4e, 0x11,
    0x0, 0x0, 0x2, 0xa, 0xa0, 0xa8, 0xc, 0x60,
    0x0, 0xe, 0x42, 0xf0, 0xe3, 0x3f, 0x0, 0x52,
    0x7, 0xb0, 0xd4, 0xf2, 0x5c, 0x1, 0xf9, 0x4,
    0xd0, 0xc5, 0xe3, 0x3f, 0x0, 0x51, 0x7, 0xb0,
    0xd4, 0xa8, 0xc, 0x60, 0x0, 0xe, 0x42, 0xf0,
    0x4e, 0x11, 0x0, 0x0, 0x2, 0xa, 0xa0, 0xa,
    0x60, 0x0, 0x0, 0x0, 0x1d, 0x10, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 192, .box_w = 13, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 85, .adv_w = 144, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 144, .adv_w = 216, .box_w = 14, .box_h = 11, .ofs_x = 0, .ofs_y = -1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x18f, 0x886
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 61527, .range_length = 2183, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 3, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 4,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t FontAwesome12 = {
#else
lv_font_t FontAwesome12 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 13,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = 0,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
    .fallback = NULL,
    .user_data = NULL
};



#endif /*#if FONTAWESOME12*/

