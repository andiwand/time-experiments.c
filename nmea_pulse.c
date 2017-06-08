#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "shared.h"

int main(int argc, char** argv) {
    FILE* fd;
    int r;
    char c;
    struct timespec ts;
    
    if (argc != 2) {
        fprintf(stderr, "usage: %s <ttydev>\n", argv[0]);
        return 1;
    }
    
    defaults();
    
    fd = fopen(argv[1], "r");
    if (fd == NULL) {
        printf("cannot open %s\n", argv[1]);
        return 1;
    }
    
    while (1) {
        r = fread(&c, sizeof(char), 1, fd);
        if (r <= 0) continue;
        if (c == '\r') {
            clock_gettime(CLOCK_REALTIME, &ts);
            printf("%ld.%09ld\n", ts.tv_sec, ts.tv_nsec);
        }
    }

    fclose(fd);
    
    return 0;
}
