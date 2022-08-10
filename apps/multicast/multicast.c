#include "multicast.h"
#include "sys/rtimer.h"

static struct rtimer rt;
static struct pt pthread; //Protothread
static volatile rtimer_clock_t t_start = 0;
static int visit=0; 

/*---------------------------------------------------------------------------*/
PROCESS(printStatsProcess, "Print the Statistics of the MultiCast Process");
PROCESS_THREAD(printStatsProcess, ev, data){
  PROCESS_BEGIN();
  while(1){
    PROCESS_YIELD_UNTIL(ev == PROCESS_EVENT_POLL);
    printf("In rtimer call number %d\n", visit);
  }
  PROCESS_END();
}

/*---------------------------------------------------------------------------*/

char multicast_scheduler(struct rtimer *t, void *ptr) {
  PT_BEGIN(&pthread);
  t_start = RTIMER_NOW();

  //Do something here
  visit++;
  process_poll(&printStatsProcess);

  //Reschedule the scheduler again again
  rtimer_set(t, t_start + MULTICAST_PERIOD, 1, (rtimer_callback_t)multicast_scheduler, ptr);
  PT_END(&pthread);
}

/*---------------------------------------------------------------------------*/
AUTOSTART_PROCESSES(&scheduleMultiCastProcess);
PROCESS_THREAD(scheduleMultiCastProcess, ev, data)
{
  PROCESS_BEGIN();
  process_start(&printStatsProcess, NULL);
  rtimer_set(&rt, RTIMER_NOW() + MULTICAST_PERIOD, 1, (rtimer_callback_t)multicast_scheduler, NULL);
  printf("MultiCast Process Started\n");
  PROCESS_END();
}