#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char **argv) {
	int ret = 0;	

	if (argc < 2) {
		printf("Error: falta el programa\n");
		ret = -1;
	} else {

		if (execvp(argv[1], argv + 1) == -1) {
			printf("Error %d: %s\n", errno, strerror(errno));
			ret = -1;
		}

		printf("El comando terminó de ejecutarse\n");
	}

	return ret;
}
