#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/types.h>

int main() {
  struct utsname buff;

  if(uname(&buff) < -1) {
    printf("Error %d: %s\n", errno, strerror(errno));

    return -1;

  } else {
    printf("Sysname: %s\n", buff.sysname);
    printf("Nodename: %s\n", buff.nodename);
    printf("Release: %s\n", buff.release);
    printf("Version: %s\n", buff.version);
    printf("Machine: %s\n", buff.machine);
  }

  return 1;
}
