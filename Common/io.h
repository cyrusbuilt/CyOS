#ifndef _IO_H
#define _IO_H

#include <sys/compiler.h>
#include <stdio.h>
#include <stdlib.h>

__sfr __at 0x00 EXEC_PORT;
__sfr __at 0x01 STORE_OPC_PORT;
__sfr __at 0x01 SER_RX_PORT;

void k_outp(unsigned int port, unsigned int val);
unsigned int k_inp(unsigned int port);

#endif