#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <stdbool.h>
#include <stdint.h>

void gfx_clear_screen(void);
void gfx_set_brush_color(uint8_t r, uint8_t g, uint8_t b);
void gfx_set_pen_color(uint8_t r, uint8_t g, uint8_t b);
void gfx_set_pen_width(uint8_t width);
void gfx_set_pixel(int x, int y);
void gfx_draw_line(int x0, int y0, int x1, int y1);
void gfx_draw_rect(int x0, int y0, int x1, int y1);
void gfx_fill_rect(int x0, int y0, int x1, int y1);
void gfx_draw_ellipse(int x, int y, int w, int h);
void gfx_fill_ellipse(int x, int y, int w, int h);
void gfx_draw_polygon(int x0, int y0, int x1, int y1);
void gfx_draw_polygon_ex(int x0, int y0, int x1, int y1, int xn, int yn);
void gfx_fill_polygon(int x0, int y0, int x1, int y1);
void gfx_fill_polygon_ex(int x0, int y0, int x1, int y1, int xn, int yn);
void gfx_alloc_sprites(uint8_t count);
void gfx_scroll_screen(int dx, int dy);
void gfx_set_sprite(uint8_t index, bool visible, int frame, int x, int y);

// TODO Need a method for adding a bitmap to an allocated sprite

#endif