#include <Kernel/opcodes.h>
#include <Kernel/Devices/bsp.h>
#include <Common/io.h>

struct sysflags_t bsp_read_flags(void) {
    STORE_OPC_PORT = OP_IO_RD_SYSFLG;
    uint8_t data = EXEC_PORT;
    struct sysflags_t bspSysFlags;
    bspSysFlags.autoExecEnabled = (data >> 0) & 1;
    bspSysFlags.rtcInstalled = (data >> 1) & 1;
    bspSysFlags.serialCharAvailable = (data >> 2) & 1;
    bspSysFlags.prevSerialCharValid = (data >> 3) & 1;
    return bspSysFlags;
}

void bsp_beep_start(uint8_t freq) {
    STORE_OPC_PORT = OP_IO_WR_BEEPSTART;
    EXEC_PORT = (char)(freq);
}

void bsp_beep_stop(void) {
    STORE_OPC_PORT = OP_IO_WR_BEEPSTOP;
}

bool bsp_user_key_pressed(void) {
    STORE_OPC_PORT = OP_IO_RD_USRKEY;
    return EXEC_PORT;
}

void bsp_user_led_write(enum user_led_t state) {
    STORE_OPC_PORT = OP_IO_WR_USR_LED;
    EXEC_PORT = (char)(state);
}

uint8_t bsp_serial_tx_buffer_free(void) {
    STORE_OPC_PORT = OP_IO_RD_ATXBUFF;
    return EXEC_PORT;
}

void bsp_nop(void) {
    STORE_OPC_PORT = OP_IO_NOP;
}

struct isb_t bsp_get_interrupt(void) {
    STORE_OPC_PORT = OP_IO_RD_SYSIRQ;
    uint8_t data = EXEC_PORT;
    struct isb_t isb;
    isb.serialRxIntEn = (bool)(data & 1);
    isb.sysTickIntEn = (bool)(data & (1 << 1)) >> 1;
    return isb;
}

void bsp_enable_interrupt(struct isb_t isb) {
    STORE_OPC_PORT = OP_IO_WR_SETIRQ;
    EXEC_PORT = isb.serialRxIntEn | (isb.sysTickIntEn << 1);
}

void bsp_set_tick(uint8_t millis) {
    STORE_OPC_PORT = OP_IO_WR_SETTICK;
    EXEC_PORT = (char)(millis);
}
