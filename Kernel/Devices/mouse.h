#ifndef _MOUSE_H_
#define _MOUSE_H_

#include <stdbool.h>

struct mouse_pos_t {
    int x;
    int y;
    int wheel;
    bool leftButton;
    bool middleButton;
    bool rightButton;
};

void mouse_enable(void);
void mouse_disable(void);
struct mouse_pos_t get_mouse_pos(void);

#endif
