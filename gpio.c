#include "gpio.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define BCM2708_PERI_BASE        0x20000000
#define BCM2709_PERI_BASE        0x3F000000

#define PAGE_SIZE  (4*1024)
#define BLOCK_SIZE (4*1024)

volatile unsigned* gpio_setup(int version) {
    int mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (mem_fd < 0) {
        printf("can't open /dev/mem\n");
        exit(-1);
    }
    
    off_t base;
    switch (version) {
    case RPI_V1:
        base = BCM2708_PERI_BASE + 0x200000;
        break;
    case RPI_V2:
        base = BCM2709_PERI_BASE + 0x200000;
        break;
    default:
        printf("invalid version");
        return NULL;
    }
    
    void* gpio_map = mmap(
        NULL,                   // Any adddress in our space will do
        BLOCK_SIZE,             // Map length
        PROT_READ | PROT_WRITE, // Enable reading & writting to mapped memory
        MAP_SHARED,             // Shared with other processes
        mem_fd,                 // File to map
        base                    // Offset to GPIO peripheral
    );
    
    close(mem_fd);
    
    if (gpio_map == MAP_FAILED) {
        printf("mmap error %p\n", gpio_map);
        return NULL;
    }
    
    return (volatile unsigned*) gpio_map;
}

