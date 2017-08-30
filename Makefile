CC=gcc
CFLAGS=-c -std=c11 -Wall -O2 -D _GNU_SOURCE
LDFLAGS=

VPATH = src/

all: delay_system gpio_station gpio_polling nmea_pulse pps_pulse

clean:
	rm -f *.o
	rm -f delay_system gpio_station gpio_polling nmea_pulse pps_pulse

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

gpio_station: gpio_station.o gpio.o shared.o
	$(CC) $(LDFLAGS) $^ -o $@

gpio_polling: gpio_polling.o gpio.o shared.o
	$(CC) $(LDFLAGS) $^ -o $@

delay_system: delay_system.o shared.o
	$(CC) $(LDFLAGS) $^ -o $@

nmea_pulse: nmea_pulse.o shared.o
	$(CC) $(LDFLAGS) $^ -o $@

pps_pulse: pps_pulse.o shared.o
	$(CC) $(LDFLAGS) $^ -o $@
