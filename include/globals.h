#ifndef _GLOBALS_H
#define _GLOBALS_H

#include <Arduino.h>

#define FIRMWARE_VERSION "v0.0.1"

#define SECONDS_30 30000 // in milliseconds
#define MINUTES_1 60000  // in milliseconds
#define MINUTES_5 300000 // in milliseconds
#define NTP_POLLING 3600 // NTP polling interval in seconds (3600 = 1 hour)

#define DEBUG_PRINT 1

#if DEBUG_PRINT == 1
    #define debugp(x,...) Serial.print(x)
    #define debugpf(x,...) Serial.printf(x)
    #define debugpln(x,...) Serial.println(x)
#else
    #define debugp(x)
    #define debugpln(x,...)
    #define debugpf(x,...)
#endif


#endif




