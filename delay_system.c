#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "shared.h"

int main(int argc, char** argv) {
    argc -= 1; argv = argv + 1;

    float interval;

    switch (argc) {
    case 1:
        interval = strtof(argv[0], NULL);
        break;
    default:
        printf("delay_system INTERVAL\n");
        return 1;
    }

    struct timespec ts1;
    struct timespec ts2;
    struct timespec diff;

    while (1) {
        fsleep(interval);
        
        clock_gettime(CLOCK_REALTIME, &ts1);
        clock_gettime(CLOCK_REALTIME, &ts2);
        time_diff(&ts2, &ts1, &diff);
        
        printf("%ld.%09ld\n", diff.tv_sec, diff.tv_nsec);
    }

    return 0;
}
