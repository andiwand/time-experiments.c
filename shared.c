#include "shared.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sched.h>

char* trim(const char* str) {
    while (isspace((unsigned char) *str)) str++;

    if (*str == '\0') {
        char* out = (char*) malloc(1);
        out[0] = '\0';
        return out;
    }

    const char* end = str + strlen(str) - 1;
    while((end > str) && isspace((unsigned char)* end)) end--;
    end++;

    size_t out_size = end - str;
    char* out = (char*) malloc(out_size + 1);
    memcpy(out, str, out_size);
    out[out_size] = '\0';
    return out;
}

char* get_cpuinfo(const char* param) {
    FILE* cpuinfo = fopen("/proc/cpuinfo", "rb");
    char* tmp = 0;
    size_t tmp_size = 0;
    ssize_t r;
    bool matched = false;
    char* result = NULL;
    
    while (1) {
        r = getdelim(&tmp, &tmp_size, ':', cpuinfo);
        if (r < 0) break;
        matched = strstr(tmp, param) != NULL;
        
        r = getdelim(&tmp, &tmp_size, '\n', cpuinfo);
        if (r < 0) break;
        if (matched) break;
    }
    
    if (matched) result = trim(tmp);
    free(tmp);
    fclose(cpuinfo);
    return result;
}

int rpi_version() {
    char* hardware = get_cpuinfo("Hardware");
    if (hardware == NULL) return -1;
    if (strcmp(hardware, "BCM2708") == 0) return RPI_V1;
    if (strcmp(hardware, "BCM2709") == 0) return RPI_V2;
    return -1;
}

void fsleep(float time) {
    sleep((unsigned int) time);
    time -= (unsigned int) time;
    time *= 1000000;
    usleep((unsigned int) time);
}

void defaults(gpio_t* gpio) {
    setbuf(stdout, NULL);
    
    int version = rpi_version();
    *gpio = gpio_setup(version);
    
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    if (sched_setaffinity(0, sizeof(mask), &mask)) {
        printf("sched_setaffinity failed");
    }
    if (setpriority(PRIO_PROCESS, 0, -20)) {
        printf("setpriority failed");
    }
}

unsigned long time_long_ns(struct timespec *ts) {
	unsigned long result = 0;
	result += ts->tv_sec * 1000000000;
	result += ts->tv_nsec;
	return result;
}

unsigned long time_long_us(struct timespec *ts) {
	unsigned long result = 0;
	result += ts->tv_sec * 1000000;
	result += ts->tv_nsec / 1000;
	return result;
}

void time_add_ns(struct timespec *ts, unsigned long nanos) {
	ts->tv_sec += nanos / 1000000000;
	ts->tv_nsec += nanos % 1000000000;
	ts->tv_sec += ts->tv_nsec / 1000000000;
	ts->tv_nsec %= 1000000000;
}

void time_add_us(struct timespec *ts, unsigned long micros) {
	ts->tv_sec += micros / 1000000;
	ts->tv_nsec += (micros % 1000000) * 1000;
	ts->tv_sec += ts->tv_nsec / 1000000000;
	ts->tv_nsec %= 1000000000;
}

void time_diff(struct timespec *a, struct timespec *b, struct timespec *c) {
	c->tv_sec = a->tv_sec - b->tv_sec;
	if(b->tv_nsec > a->tv_nsec) {
		c->tv_sec--;
		c->tv_nsec = 1000000000 - (b->tv_nsec - a->tv_nsec);
	} else {
		c->tv_nsec = a->tv_nsec - b->tv_nsec;
	}
}

int time_cmp(struct timespec *a, struct timespec *b) {
	if(a->tv_sec > b->tv_sec) {
		return 1;
	} else if(a->tv_sec < b->tv_sec) {
		return -1;
	} else {
		if(a->tv_nsec > b->tv_nsec) {
			return 1;
		} else if(a->tv_nsec < b->tv_nsec) {
			return -1;
		} else {
			return 0;
		}
	}
}

