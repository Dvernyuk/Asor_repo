#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>

int main() {
  uid_t uid = getuid();
  struct passwd *pass= getpwuid(uid);
  char *name = pass->pw_name;
  char *dir = pass->pw_dir;
  char *gecos = pass->pw_gecos;

  printf("UID Real: %d\n", getuid());
  printf("UID efectivo: %d\n", geteuid());
  printf("Nombre de usuario: %s\n", name);
  printf("Directorio: %s\n", dir);
  printf("Descripción: %s\n", gecos);

  return 1;
}
