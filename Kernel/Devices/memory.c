#include <Kernel/opcodes.h>
#include <Kernel/Devices/memory.h>
#include <Common/io.h>

void mem_set_bank(enum mem_bank_t bank) {
    STORE_OPC_PORT = OP_IO_WR_SETBNK;
    EXEC_PORT = (char)(bank);
}
