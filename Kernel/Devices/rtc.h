#ifndef RTC_H
#define RTC_H

#include <stdint.h>

#define CENTURY_PREFIX 20

struct rtc_time {
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t day;
    uint8_t month;
    uint8_t year;
    uint8_t tempC;
};

struct rtc_time rtc_get_time(void);

#endif