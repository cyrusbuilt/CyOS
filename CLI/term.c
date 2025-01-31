#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <Kernel/Devices/term.h>

uint8_t screenwidth = 80;
uint8_t screenheight = 24;

void cli_screen(int argc, char* argv[]) {
    uint8_t tmpWidth = 0;
    uint8_t tmpHeight = 0;
    if (argc >= 2) {
        tmpWidth = strtoul(argv[1], NULL, 10);
    }

    if (argc >= 3) {
        tmpHeight = strtoul(argv[2], NULL, 10);
    }

    if (tmpWidth >= 40) {
        screenwidth = tmpWidth;
    }

    if (tmpHeight >= 24) {
        screenheight = tmpHeight;
    }

    printf("usage: screen <width> <height>\n");
    printf("current screen size is %dx%d\n", screenwidth, screenheight);
}

void cli_cls(int argc, char* argv[]) {
    printf("\e_B$");
}

void cli_esc(int argc, char* argv[]) {
    if (argc < 2) {
        printf("usage: %s <sequence>...\n", argv[0]);
    }

    for (uint8_t i = 1; i < argc; i++) {
        printf("\e%s", argv[i]);
    }
}

void cli_ascii(int argc, char* argv[]) {
    if (argc < 2) {
        printf("usage: %s <hex code>...\n", argv[0]);
    }

    for (uint8_t i = 1; i < argc; i++) {
        char c = strtoul(argv[i], NULL, 16);
        printf("%c", c);
    }
}

void cli_cursor_toggle(int argc, char* argv[]) {
    if (argc < 2) {
        printf("usage: %s <on | off>...\n", argv[0]);
        return;
    }

    if (strstr(argv[1], "on") != NULL) {
        term_cursor_on();
    } else if (strstr(argv[1], "off") != NULL) {
        term_cursor_off();
    }

    printf("usage: %s <on | off>...\n", argv[0]);
    return;
}