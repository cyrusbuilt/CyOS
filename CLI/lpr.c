#include <stdio.h>
#include <stdlib.h>
#include <Kernel/Devices/spp.h>

void cli_lprint(int argc, char *argv[]) {
    if (argc < 2) {
        printf("usage: %s <string>\n", argv[0]);
        return;
    }

    struct spp_status_t status;
    status = spp_read();
    if (status.error) {
        printf("ERROR: printer error\n");
        return;
    }

    if (status.paperOut) {
        printf("ERROR: printer out of paper\n");
        return;
    }

    if (status.busy) {
        printf("ERROR: printer busy. Try again later.\n");
        return;
    }

    char *line = argv[1];
    for (int i = 0; line[i] != '\0'; i++) {
        spp_write(line[i]);
        msleep(100);
    }
}