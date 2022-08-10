#include "contiki.h"
#include "multicast.h"

PROCESS(multiCastMain,"A Sample Process that uses MultiCast");
AUTOSTART_PROCESSES(&multiCastMain);

PROCESS_THREAD(multiCastMain,ev,data){
    PROCESS_BEGIN();

    process_start(&scheduleMultiCastProcess,NULL);

    PROCESS_END();
}