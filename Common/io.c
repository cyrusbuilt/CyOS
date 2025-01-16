#include <stdlib.h>
#include "io.h"
#include "Kernel/opcodes.h"

#define LF 0x0a
#define CR 0x0d
#define SER_BUF_EMPTY_BIT 0x04

// SDCC exporting fudge to handle the double export of library functions
#ifdef __SDCC
static void fudge_export(void)
{
__asm
        PUBLIC fputc_cons_native
        PUBLIC _fputc_cons_native
        defc fputc_cons_native = _fputc_cons_native
        defc fgetc_cons = _fgetc_cons
__endasm;
}
#endif

void k_outp(unsigned int port, unsigned int val) {
    outp(port, val);
}

unsigned int k_inp(unsigned int port) {
    return inp(port);
}

int fputc_cons_native(char c) {
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