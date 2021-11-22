#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sched.h>

int main() {
  int incr = -20;

  if(nice(incr) == -1)
    printf("Error %d: %s\n", errno, strerror(errno));

  incr = 12;

  if(sched_setscheduler(0, SCHED_FIFO, incr) == -1)
    printf("Error %d: %s\n", errno, strerror(errno));

  return 0;
}
