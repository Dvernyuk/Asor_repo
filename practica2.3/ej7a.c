#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv) {
	int ret = 0;	
	int i;
	int tamStr = 1;
	char *str;

	if (argc < 2) {
		printf("Error: falta el programa\n");
		ret = -1;
	} else {

		for (i = 1; i < argc; i++)
			tamStr += strlen(argv[i]) + 1;

		str = (char*)malloc(sizeof(char) * tamStr);


		for (i = 1; i < argc; i++) {
			strcat(str, argv[i]);
			strcat(str, " ");
		}

		if (system(str) == -1) {
			printf("Error %d: %s\n", errno, strerror(errno));
			ret = -1;
		}

		printf("El comando terminó de ejecutarse\n");
		free(str);
	}

	return ret;
}
