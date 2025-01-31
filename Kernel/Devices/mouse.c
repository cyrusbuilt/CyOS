#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <Common/io.h>
#include <Kernel/Devices/mouse.h>
#include <Util/stringutil.h>

void mouse_enable(void) {
    printf("\e_H1$");
}

void mouse_disable(void) {
    printf("\e_H0$");
}

struct mouse_pos_t get_mouse_pos(void) {
    struct mouse_pos_t pos;
    char buf[15];
    printf("\e_M$");
    while (fgets(buf, sizeof(buf), stdin) == NULL) { ;; }

    if (string_starts_with(buf, "$")) {
        char *result[4];
        for (int i = 0; i < 4; i++) {
            result[i] = strtok(i == 0 ? buf : NULL, ";");
        }

        pos.x = atoi(result[0]);
        pos.y = atoi(result[1]);
        pos.wheel = atoi(result[2]);

        uint8_t buttons = atoi(result[3]);
        pos.leftButton = (buttons >> 0) & 1;
        pos.middleButton = (buttons >> 1) & 1;
        pos.rightButton = (buttons >> 2) & 1;
        return pos;
    }

    pos.x = 0;
    pos.y = 0;
    pos.wheel = 0;
    pos.leftButton = false;
    pos.middleButton = false;
    pos.rightButton = false;
    return pos;
}