#ifndef _KERNEL_H
#define _KERNEL_H

#include <stdio.h>
#include "Common/types.h"

void out(uint_fast8_t port, uint_fast8_t val);
void uint_fast8_t in(uint_fast8_t port);
int putchar(int c);
int getchar(void);
#endif