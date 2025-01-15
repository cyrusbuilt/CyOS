#ifndef _IO_H
#define _IO_H

#include <sys/compiler.h>
#include <stdint.h>

void k_outp(uint16_t port, uint8_t val);
uint8_t k_inp(uint8_t port);

__sfr __at 0x00 EXEC_PORT;
__sfr __at 0x01 STORE_OPC_PORT;
__sfr __at 0x01 SER_RX_PORT;

#endif