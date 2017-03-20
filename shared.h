#ifndef SHARED_H_
#define SHARED_H_

#include <time.h>
#include "gpio.h"

char* trim(const char* str);
char* get_cpuinfo(const char* param);
int rpi_version();
void fsleep(float time);
void defaults(gpio_t* gpio);

unsigned long time_long_ns(struct timespec *ts);
unsigned long time_long_us(struct timespec *ts);
void time_add_ns(struct timespec *ts, unsigned long nanos);
void time_add_us(struct timespec *ts, unsigned long micros);
void time_diff(struct timespec *a, struct timespec *b, struct timespec *c);
int time_cmp(struct timespec *a, struct timespec *b);

#endif // SHARED_H_

