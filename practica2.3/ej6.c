#include <stdio.h>
#include <sched.h>
#include <errno.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdlib.h>

int faux(char *hilo) {
	int ret = 0;
	struct rlimit limit;
	char path[sizeof(char)*(4096 + 1)];
	char *rpath = getcwd(path, 4096 + 1);

	printf("PID (%s) %i\n", hilo, getpid());
	printf("PPID (%s) %i\n", hilo, getppid());
	printf("PGID (%s) %i\n", hilo, getpgid(getpid()));
	
	if (getrlimit(RLIMIT_NOFILE, &limit) == -1) {
		printf("Error %d: %s\n", errno, strerror(errno));
		ret = -1;
	} else {

		printf("Número máximo de ficheros (%s) %li\n", hilo, limit.rlim_max);
		printf("Directorio (%s) %s\n", hilo, path);
	}

	return ret;
}

int main() {
	pid_t pid = fork();
	int ret = 0;

	switch (pid) {
		case -1:
			printf("Error %d: %s\n", errno, strerror(errno));
			exit(1);
		break;
		case 0:
			if (setsid() == -1) {
				printf("Error %d: %s\n", errno, strerror(errno));
				exit(1);
			}
			if (chdir("/tmp") == -1) {
				printf("Error %d: %s\n", errno, strerror(errno));
				exit(1);
			}
			ret = faux("Hijo");
		break;
		default:
			ret = faux("Padre");
	}
	
	return ret;
}
