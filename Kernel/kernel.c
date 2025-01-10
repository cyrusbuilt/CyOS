#include "kernel.h"
#include "opcodes.h"

__sfr __at 0x00 EXEC_PORT;
__sfr __at 0x01 STORE_OPC_PORT;
__sfr __at 0x01 SER_RX_PORT;

void out(uint_fast8_t port, uint_fast8_t val) {

}

void uint_fast8_t in(uint_fast8_t port) {
    
}

int putchar(int c) {
    
}

/**
 * Kernel bootstrap routine.
 */
void kernel_main(void) {

}

/**
 * Kernel entry point.
 */
void main() {
    kernel_main();
}
