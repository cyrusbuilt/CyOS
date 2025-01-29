#include <stdio.h>
#include <Kernel/Devices/rtc.h>

void print2digit(char data) {
    if (data < 10) {
        printf("0");
    }
    printf("%d", data);
}

void cli_time(int argc, char* argv[]) {
    struct rtc_time time;
    time = rtc_get_time();
    printf("%d", CENTURY_PREFIX);
    print2digit(time.year);
    printf("-");
    print2digit(time.month);
    printf("-");
    print2digit(time.day);
    printf(" ");
    print2digit(time.hours);
    printf(":");
    print2digit(time.minutes);
    printf(":");
    print2digit(time.seconds);
    printf("\n");
}