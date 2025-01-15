#ifndef _TYPES_H
#define _TYPES_H

#include <stdint.h>

#ifdef vaddr_t
#undef vaddr_t
#endif
#ifdef uint_fast8_t
#undef uint_fast8_t
#endif
typedef unsigned int uint_fast8_t;
typedef uint32_t vaddr_t;

#endif