#include <stdio.h>
#include <time.h>
#include <sys/time.h>

int main() {
  time_t t = time(NULL);
  struct tm *date = localtime(&t);

  int year = date->tm_year;

  printf("Es el año %i\n", 1900 + year);

  return 1;
}
