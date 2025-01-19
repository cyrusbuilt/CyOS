#include <Kernel/opcodes.h>
#include <Kernel/Devices/diskio.h>
#include <Common/io.h>

enum disk_error_t diskio_get_last_error(void) {
    STORE_OPC_PORT = OP_IO_RD_ERRDSK;
    char error = EXEC_PORT;
    return (enum disk_error_t)(error);
}

enum disk_error_t diskio_select_disk(uint8_t disk_num) {
    STORE_OPC_PORT = OP_IO_WR_SELDSK;
    EXEC_PORT = (char)(disk_num);
    return diskio_get_last_error();
}

enum disk_error_t diskio_select_track(uint16_t track_num) {
    uint8_t disk_num_lsb = (uint8_t)(track_num & 0xff);
    STORE_OPC_PORT = OP_IO_WR_SELTRK;
    EXEC_PORT = (char)(disk_num_lsb);

    uint8_t disk_num_msb = (uint8_t)(track_num >> 8);
    STORE_OPC_PORT = OP_IO_WR_SELTRK;
    EXEC_PORT = (char)(disk_num_msb);

    return diskio_get_last_error();
}

enum disk_error_t diskio_select_sector(uint8_t sector_num) {
    STORE_OPC_PORT = OP_IO_WR_SELSCT;
    EXEC_PORT = (char)(sector_num);
    return diskio_get_last_error();
}

enum disk_error_t diskio_write_sector(uint16_t data) {
    uint8_t data_lsb = (uint8_t)(data & 0xff);
    STORE_OPC_PORT = OP_IO_WR_WRTSCT;
    EXEC_PORT = (char)(data_lsb);

    uint8_t data_msb = (uint8_t)(data >> 8);
    STORE_OPC_PORT = OP_IO_WR_WRTSCT;
    EXEC_PORT = (char)(data_msb);

    return diskio_get_last_error();
}

enum disk_error_t diskio_read_sector(uint16_t *sect_buf) {
    STORE_OPC_PORT = OP_IO_RD_RDSECT;
    uint8_t data_lsb = EXEC_PORT;

    STORE_OPC_PORT = OP_IO_RD_RDSECT;
    uint8_t data_msb = EXEC_PORT;

    *sect_buf = ((uint16_t)data_msb << 8) | data_lsb;
    return diskio_get_last_error();
}

enum disk_error_t diskio_mount(void) {
    STORE_OPC_PORT = OP_IO_RD_SDMNT;
    char error = EXEC_PORT;
    return (enum disk_error_t)(error);
}
