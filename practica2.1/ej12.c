#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  time_t t = time(NULL);

  printf("%li segundos\n", t);

  return 1;
}
