#ifndef _KERNEL_H
#define _KERNEL_H

#include <stdlib.h>
#include "Common/types.h"

#define VERSION "0.1"

#define PANIC(fmt, ...)                                                      \
    do {                                                                     \
        printf("PANIC: %s:%d: " fmt "\n", __FILE__, __LINE__, __VA_ARGS__);  \
        while (1) {}                                                         \
    } while (0)
#endif
