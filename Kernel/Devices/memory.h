/**
* Memory: Provides driver functions for interfacing with memory
* as exposed by the firmware.
*/
#ifndef _MEMORY_H_
#define _MEMORY_H_

enum mem_bank_t {
    mem_bank_0 = 0,
    mem_bank_1 = 1,
    mem_bank_2 = 2
};

void mem_set_bank(enum mem_bank_t bank);

#endif