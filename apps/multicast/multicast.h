#include "contiki.h"
#include <stdio.h>

#define MULTICAST_PERIOD (RTIMER_SECOND) 

PROCESS(scheduleMultiCastProcess , "Multicast Scheduler Process");