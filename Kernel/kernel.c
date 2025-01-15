#include <stdio.h>
#include "kernel.h"
#include "opcodes.h"
#include "Common/io.h"

/**
 * Kernel bootstrap routine.
 */
void kernel_main(void) {
    printf("\n\n");

    // Just something to verify we can boot and run.
    PANIC("%s: hello world!", VERSION);
}

/**
 * Kernel entry point.
 */
int main(void) {
    // TODO initialize subsystems

    // Should never return.
    kernel_main();
    return 0;
}
