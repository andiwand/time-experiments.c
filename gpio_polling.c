#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include "gpio.h"
#include "shared.h"

int main(int argc, char** argv) {
    argc -= 1; argv = argv + 1;

    int flags = EDGE_RISING | EDGE_FALLING;
    int pin;

    switch (argc) {
    case 2:
        flags = strtol(argv[1], NULL, 10);
    case 1:
        pin = strtol(argv[0], NULL, 10);
        break;
    default:
        printf("gpio_polling PIN [FLAGS]\n");
        return 1;
    }

    gpio_t gpio;
    defaults(&gpio);

    INP_GPIO(gpio, pin);

    int last = GET_GPIO(gpio, pin);
    int now;
    struct timespec ts;
    while (1) {
        clock_gettime(CLOCK_REALTIME, &ts);
        now = GET_GPIO(gpio, pin);
        if (last != now) {
            if ((now & (flags & EDGE_RISING)) | ((!now) & (flags & EDGE_FALLING))) {
                printf("%ld.%09ld %d\n", ts.tv_sec, ts.tv_nsec, now != 0);
            }
        }
        last = now;
    }

    return 0;
}
