#include <Kernel/opcodes.h>
#include <Kernel/Devices/bsp.h>
#include <Common/io.h>

struct sysflags_t bspSysflags;

void bsp_read_flags(void) {
    STORE_OPC_PORT = OP_IO_RD_SYSFLG;
    uint8_t data = EXEC_PORT;
    bspSysflags.autoExecEnabled = (data & 0x01);
    bspSysflags.rtcInstalled = (data & 0x02);
    bspSysflags.serialCharAvailable = (data & 0x03);
    bspSysflags.prevSerialCharValid = (data & 0x04);
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
