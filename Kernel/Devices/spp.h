/**
* SPP: Driver for the Standard Parallel Port add-on card (CyBorgSPP).
* Provides driver functions for interfacing with the SPP functionality
* exposed by the firmware.
* NOTE: These are ignored if the board is not present.
*/
#ifndef _SPP_H_
#define _SPP_H_

#include <stdint.h>
#include <stdbool.h>

struct spp_status_t {
    bool ack;
    bool busy;
    bool paperOut;
    bool select;
    bool error;
};

void spp_init(bool enableAutoFeed);
void spp_write(uint8_t data);
struct spp_status_t *spp_read(void);

#endif