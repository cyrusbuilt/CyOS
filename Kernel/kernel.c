#include <stdio.h>
#include "kernel.h"
#include "opcodes.h"

__sfr __at 0x00 EXEC_PORT;
__sfr __at 0x01 STORE_OPC_PORT;
__sfr __at 0x01 SER_RX_PORT;

#define LF 0x0a
#define CR 0x0d
#define SER_BUF_EMPTY_BIT 0x04

void out(uint_fast8_t port, uint_fast8_t val) {
    STORE_OPC_PORT = port;
    EXEC_PORT = (char)(val);
}

void uint_fast8_t in(uint_fast8_t port) {
    return SER_RX_PORT;
}

int putchar(int c) {
    if (c == LF) {
        out(OP_IO_WR_SER_TX, CR);
    }

    out(OP_IO_WR_SER_TX, c);
    return c;
}

int getchar(void) {
    static char sysFlags;
    do {
        STORE_OPC_PORT = OP_IO_RD_SYSFLG;
        sysFlags = EXEC_PORT;
    } while (!(sysFlags & SER_BUF_EMPTY_BIT));
    return SER_RX_PORT;
}

/**
 * Kernel bootstrap routine.
 */
void kernel_main(void) {
    printf("\n\n");

    // Just something to verify we can boot and run.
    PANIC("hello world!");
}

/**
 * Kernel entry point.
 */
void main() {
    // TODO 

    // Should never return.
    kernel_main();
}
