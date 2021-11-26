#include <stdio.h>
#include <sched.h>
#include <errno.h>
#include <sys/resource.h>
#include <unistd.h>

int main() {
	int ret = 0;
	struct rlimit limit;
	char path[sizeof(char)*(4096 + 1)];
	char *rpath = getcwd(path, 4096 + 1);

	printf("PID %i\n", getpid());
	printf("PPID %i\n", getppid());
	printf("PGID %i\n", getpgid(getpid()));
	
	if (getrlimit(RLIMIT_NOFILE, &limit) == -1) {
		printf("Error %d: %s\n", errno, strerror(errno));
		ret = -1;
	} else {

		printf("Número máximo de ficheros %li\n", limit.rlim_max);
		printf("Directorio %s\n", path);
	}

	return ret;
}
