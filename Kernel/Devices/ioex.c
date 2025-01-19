#include <Kernel/opcodes.h>
#include <Kernel/Devices/ioex.h>
#include <Common/io.h>

void ioex_write(enum ioex_port_t port, uint8_t data) {
    if (port == ioex_port_a) {
        STORE_OPC_PORT = OP_IO_WR_GPIOA;
    } else {
        STORE_OPC_PORT = OP_IO_WR_GPIOB;
    }

    EXEC_PORT = (char)(data);
}

void ioex_set_mode(enum ioex_port_t port, enum ioex_mode_t mode) {
    if (port == ioex_port_a) {
        STORE_OPC_PORT = OP_IO_WR_IODIRA;
    } else {
        STORE_OPC_PORT = OP_IO_WR_IODIRB;
    }

    char mode_val = 0;
    if (mode == ioex_mode_output)  {
        mode_val = 1;
    }

    EXEC_PORT = mode_val;
}

void ioex_set_pullup(enum ioex_port_t port, bool pullup) {
    if (port == ioex_port_a) {
        STORE_OPC_PORT = OP_IO_WR_GPPUA;
    } else {
        STORE_OPC_PORT = OP_IO_WR_GPPUB;
    }

    EXEC_PORT = (char)(pullup);
}

uint8_t ioex_read(enum ioex_port_t port) {
    if (port == ioex_port_a) {
        STORE_OPC_PORT = OP_IO_RD_GPIOA;
    } else {
        STORE_OPC_PORT = OP_IO_RD_GPIOB;
    }

    return EXEC_PORT;
}
