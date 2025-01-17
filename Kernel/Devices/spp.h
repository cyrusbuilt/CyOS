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