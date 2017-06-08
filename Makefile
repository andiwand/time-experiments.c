CC=gcc
CFLAGS=-c -std=c11 -Wall -O2 -D _GNU_SOURCE
LDFLAGS=

all: adjtimex delay_system gpio_station gpio_polling

clean:
	rm -f *.o
	rm -f adjtimex delay_system gpio_station gpio_polling

.c.o:
	$(CC) $(CFLAGS) $< -o $@

adjtimex: adjtimex.o
	$(CC) $(LDFLAGS) $^ -o $@

gpio_station: gpio_station.o gpio.o shared.o
	$(CC) $(LDFLAGS) $^ -o $@

gpio_polling: gpio_polling.o gpio.o shared.o
	$(CC) $(LDFLAGS) $^ -o $@

delay_system: delay_system.o gpio.o shared.o
	$(CC) $(LDFLAGS) $^ -o $@
