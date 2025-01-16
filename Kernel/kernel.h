#ifndef _KERNEL_H
#define _KERNEL_H

#include <stdlib.h>
#include "Common/types.h"

#define VERSION "0.1"
#define PROCS_MAX 8
#define PROC_UNUSED   0
#define PROC_RUNNABLE 1
#define PROC_EXITED   2

struct process {
    int pid; // -1 if it's an idle process
    int state; // PROC_UNUSED, PROC_RUNNABLE, PROC_EXITED
    vaddr_t sp; // kernel stack pointer
    uint32_t *page_table; // points to first level page table
    uint8_t stack[8192]; // kernel stack
};

#define PANIC(fmt, ...)                                                      \
    do {                                                                     \
        printf("PANIC: %s:%d: " fmt "\n", __FILE__, __LINE__, __VA_ARGS__);  \
        while (1) {}                                                         \
    } while (0)
#endif
