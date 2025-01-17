#ifndef _BSP_H_
#define _BSP_H_

#include <stdint.h>
#include <stdbool.h>

struct sysflags_t {
    bool autoExecEnabled;
    bool rtcInstalled;
    bool serialCharAvailable;
    bool prevSerialCharValid;
};

extern struct sysflags_t bspSysflags;

void bsp_read_flags(void);
void bsp_beep_start(uint8_t freq);
void bsp_beep_stop(void);
bool bsp_user_key_pressed(void);
#endif