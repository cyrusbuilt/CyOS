#include <stdio.h>
#include <Kernel/Devices/spp.h>
#include <Kernel/opcodes.h>
#include <Common/io.h>

void spp_init(bool enableAutoFeed) {
    printf("spp_init(): Initializing parallel port ...");
    STORE_OPC_PORT = OP_SPP_WR_INIT;
    EXEC_PORT = (char)(enableAutoFeed);
    printf("OK\n");
}

void spp_write(uint8_t data) {
    STORE_OPC_PORT = OP_SPP_WR_WRITE;
    EXEC_PORT = data;
}

struct spp_status_t spp_read(void) {
    STORE_OPC_PORT = OP_SPP_RD_READ;
    uint8_t stat = EXEC_PORT;
    struct spp_status_t status;
    status.ack = (stat >> 0) & 1;
    status.busy = (stat >> 1) & 1;
    status.paperOut = (stat >> 2) & 1;
    status.select = (stat >> 3) & 1;
    status.error = (stat >> 4) & 1;
    return status;
}
