#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {

  int fd = open("txt/ej5.txt", O_CREAT, 00645);
  printf("%i\n", fd);
  close(fd);

  return 0;
}
