#include <Kernel/opcodes.h>
#include <Kernel/Devices/rtc.h>
#include <Common/io.h>

struct rtc_time rtc_get_time(void) {
    struct rtc_time rtc;

    uint8_t i;
    for (i = 0; i < 8; i++) {
        STORE_OPC_PORT = OP_IO_RD_DATTME;
        switch (i) {
            case 0:
                rtc.seconds = EXEC_PORT;
                break;
            case 1:
                rtc.minutes = EXEC_PORT;
                break;
            case 2:
                rtc.hours = EXEC_PORT;
                break;
            case 3:
                rtc.day = EXEC_PORT;
                break;
            case 4:
                rtc.day = EXEC_PORT;
                break;
            case 5:
                rtc.month = EXEC_PORT;
                break;
            case 6:
                rtc.year = EXEC_PORT;
                break;
            case 7:
                rtc.tempC = EXEC_PORT;
                break;
        }
    }

    return rtc;
}