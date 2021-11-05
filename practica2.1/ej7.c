#include <stdio.h>
#include <unistd.h>

int main() {
  printf("Número máximo de enlaces: %li\n", pathconf("/",_PC_LINK_MAX));
  printf("Tamaño máximo de una ruta: %li\n", pathconf("/",_PC_PATH_MAX));
  printf("tamaño máximo de un nombre de fichero: %li\n", pathconf("/",_PC_NAME_MAX));
	
  return 1;
}
