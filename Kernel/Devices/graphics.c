#include <stdio.h>
#include <Kernel/Devices/graphics.h>

void gfx_clear_screen(void) {
    printf("\e_GCLEAR$");
}

void gfx_set_brush_color(uint8_t r, uint8_t g, uint8_t b) {
    printf("\e_GBRUSH%d;%d;%d$", r, g, b);
}

void gfx_set_pen_color(uint8_t r, uint8_t g, uint8_t b) {
    printf("\e_GPEN%d;%d;%d$", r, g, b);
}

void gfx_set_pen_width(uint8_t width) {
    printf("\e_GPENW%d$", width);
}

void gfx_set_pixel(int x, int y) {
    printf("\e_GPIXEL%d;%d$", x, y);
}

void gfx_draw_line(int x0, int y0, int x1, int y1) {
    printf("\e_GLINE%d;%d;%d;%d$", x0, y0, x1, y1);
}

void gfx_draw_rect(int x0, int y0, int x1, int y1) {
    printf("\e_GRECT%d;%d;%d;%d$", x0, y0, x1, y1);
}

void gfx_fill_rect(int x0, int y0, int x1, int y1) {
    printf("\e_GFILLRECT%d;%d;%d;%d$", x0, y0, x1, y1);
}

void gfx_draw_ellipse(int x, int y, int w, int h) {
    printf("\e_GELLIPSE%d;%d;%d;%d$", x, y, w, h);
}

void gfx_fill_ellipse(int x, int y, int w, int h) {
    printf("\e_GFILLELLIPSE%d;%d;%d;%d$", x, y, w, h);
}

void gfx_draw_polygon(int x0, int y0, int x1, int y1) {
    printf("\e_GPATH%d;%d;%d;%d$", x0, y0, x1, y1);
}

void gfx_draw_polygon_ex(int x0, int y0, int x1, int y1, int xn, int yn) {
    printf("\e_GPATH%d;%d;%d;%d;%d;%d$", x0, y0, x1, y1, xn, yn);
}

void gfx_fill_polygon(int x0, int y0, int x1, int y1) {
    printf("\e_GFILLPATH%d;%d;%d;%d$", x0, y0, x1, y1);
}

void gfx_fill_polygon_ex(int x0, int y0, int x1, int y1, int xn, int yn) {
    printf("\e_GFILLPATH%d;%d;%d;%d;%d;%d$", x0, y0, x1, y1, xn, yn);
}

void gfx_alloc_sprites(uint8_t count) {
    printf("\e_GSPRITECOUNT%d$", count);
}

void gfx_scroll_screen(int dx, int dy) {
    printf("\e_GSCROLL%d;%d$", dx, dy);
}

void gfx_set_sprite(uint8_t index, bool visible, int frame, int x, int y) {
    printf("\e_GSPRITESET%d;%S;%d;%d;%d$", index, visible ? "V" : "H", frame, x, y);
}
