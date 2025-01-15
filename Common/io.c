#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <z80.h>
#include "Common/io.h"
#include "Kernel/opcodes.h"

#define LF 0x0a
#define CR 0x0d
#define SER_BUF_EMPTY_BIT 0x04

void k_outp(uint16_t port, uint8_t val) {
    z80_outp(port, val);
}

uint8_t k_inp(uint16_t port) {
    return z80_inp(port);
}

int fputc_cons_native(char c) __naked {
    if (c == LF) {
        STORE_OPC_PORT = OP_IO_WR_SER_TX;
        EXEC_PORT = (char)(CR);
    }

    STORE_OPC_PORT = OP_IO_WR_SER_TX;
    EXEC_PORT = c;
    return c;
}

int fgetc_cons(void) __naked {
    static char sysFlags;
    do {
        STORE_OPC_PORT = OP_IO_RD_SYSFLG;
        sysFlags = EXEC_PORT;
    } while (!(sysFlags & SER_BUF_EMPTY_BIT));
    return SER_RX_PORT;
}