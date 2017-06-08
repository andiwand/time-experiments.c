CC=gcc
CFLAGS=-c -std=c11 -Wall -O2 -D _GNU_SOURCE
LDFLAGS=

all: adjtimex delay_system gpio_station gpio_polling nmea_pulse pps_pulse

clean:
	rm -f *.o
	rm -f adjtimex delay_system gpio_station gpio_polling nmea_pulse pps_pulse

.c.o:
	$(CC) $(CFLAGS) $< -o $@

adjtimex: adjtimex.o
	$(CC) $(LDFLAGS) $^ -o $@

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

