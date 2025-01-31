#include <stdio.h>
#include <Kernel/Devices/term.h>

void term_cursor_on(void) {
    printf("\e_E1$");
}

void term_cursor_off(void) {
    printf("\e_E0$");
}

void term_set_cursor_pos(int x, int y) {
    printf("\e_F%d;%d$", x, y);
}

void term_delay(int ms) {
    printf("\e_Y%d$", ms);
}
