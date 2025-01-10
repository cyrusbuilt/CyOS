#ifndef _KERNEL_H
#define _KERNEL_H

#include <stdio.h>
#include "Common/types.h"
#include "Common/common.h"

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

// TODO Maybe move these to devio.h in common so it can be used by drivers, etc.
// and keep only the kernel-specific stuff here.
extern void out(uint_fast8_t port, uint_fast8_t val);
extern void uint_fast8_t in(uint_fast8_t port);
extern int putchar(int c);
extern int getchar(void);

#define PANIC(fmt, ...)                                                        \
    do {                                                                       \
        printf("PANIC: %s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__);  \
        while (1) {}                                                           \
    } while (0)
#endif
