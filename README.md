# time-experiments.c
A collection of c modules for the time experiment scripts espcially aimed for the Raspberry Pi.

## delay_system
```
usage: ./delay_system <interval> [<flags]

measures the system delay between two clock calls
```
## gpio_polling
```
usage: ./gpio_polling <pin> [<flags]

polls the specified pin for state changes and prints the local time
```
## gpio_station
```
usage: ./gpio_station <pin> [<interval]

sends digital signals to the given pin with a constant interval
```
## nmea_pulse
```
usage: ./nmea_pulse <ttydev>

prints the local time on a nmea signal
```
## pps_pulse
```
usage: ./pps_pulse <ppsdev>

prints the local time on a pps signal
```
