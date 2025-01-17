#include <Kernel/Devices/spp.h>
#include <Kernel/opcodes.h>
#include <Common/io.h>

struct spp_status_t spp_status;

void spp_init(bool enableAutoFeed) {
    STORE_OPC_PORT = OP_SPP_WR_INIT;
    EXEC_PORT = (char)(enableAutoFeed);
}

void spp_write(uint8_t data) {
    STORE_OPC_PORT = OP_SPP_WR_WRITE;
    EXEC_PORT = data;
}

struct spp_status_t *spp_read(void) {
    STORE_OPC_PORT = OP_SPP_RD_READ;
    uint8_t stat = EXEC_PORT;
    struct spp_status_t *status = &spp_status;
    status->ack = (stat & 0x01);
    status->busy = (stat & 0x02);
    status->paperOut = (stat & 0x03);
    status->select = (stat & 0x04);
    status->error = (stat & 0x05);
    return status;
}
