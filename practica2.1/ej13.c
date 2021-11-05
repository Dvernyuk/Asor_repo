#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>

int main(){
  struct timeval t;
  int aux = gettimeofday(&t, NULL);

  if(aux == -1) {
    printf("Error %d: %s\n", errno, strerror(errno));
  } else {
    int t_start = t.tv_usec;

    int i;
    for (i = 0; i < 1000000; i++);

    aux = gettimeofday(&t, NULL);
    if(aux == -1) {
    printf("Error %d: %s\n", errno, strerror(errno));
    } else {
      int t_end = t.tv_usec;

      printf("%i ms\n", t_end - t_start);
    }
  }

  return 1;
}
