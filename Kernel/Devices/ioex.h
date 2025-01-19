/**
* IOEX: I/O Expansion driver. Provides drivers functions for interfacing
* with the IOEX functions exposed in firmware.
*/
#ifndef _IOEX_H_
#define _IOEX_H_

#include <stdbool.h>
#include <stdint.h>

enum ioex_port_t {
    ioex_port_a,
    ioex_port_b
};

enum ioex_mode_t {
    ioex_mode_input,
    ioex_mode_output
};

void ioex_write(enum ioex_port_t port, uint8_t data);
void ioex_set_mode(enum ioex_port_t port, enum ioex_mode_t mode);
void ioex_set_pullup(enum ioex_port_t port, bool pullup);
uint8_t ioex_read(enum ioex_port_t port);
#endif