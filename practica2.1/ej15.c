#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <locale.h>

int main(){
  time_t t = time(NULL);
  struct tm *data = localtime(&t);
  char buff[80];

  setlocale(LC_ALL, "spanish");
  strftime(buff, 80, "%c", data);
  printf("%s\n", buff);

  return 1;
}
