#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sched.h>

int main() {
  int incr = -20;  

  if(nice(incr) == -1)
    printf("Error(1) %d: %s\n", errno, strerror(errno));

  incr = 12;
  struct sched_param* a;
  a->sched_priority = 12;

  if(sched_setscheduler(0, SCHED_FIFO, a) == -1)
    printf("Error(2) %d: %s\n", errno, strerror(errno));

  return 0;
}
