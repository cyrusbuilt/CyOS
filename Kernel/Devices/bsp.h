/**
* BSP: Driver for the Board Support Processor (ViCREM). Provides driver functions
* for interfacing with core firmware features.
*/
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

enum user_led_t {
    user_led_off = 0,
    user_led_on = 1
};

struct isb_t {
    bool serialRxIntEn;
    bool sysTickIntEn;
};

struct sysflags_t bsp_read_flags(void);
void bsp_beep_start(uint8_t freq);
void bsp_beep_stop(void);
bool bsp_user_key_pressed(void);
void bsp_user_led_write(enum user_led_t state);
uint8_t bsp_serial_tx_buffer_free(void);
void bsp_nop(void);
struct isb_t bsp_get_interrupt(void);
void bsp_enable_interrupt(struct isb_t isb);
void bsp_set_tick(uint8_t millis);
#endif