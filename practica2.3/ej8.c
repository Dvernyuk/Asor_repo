#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

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

int main(int argc, char **argv){
	int ret = 0;

	if (argc < 2) {
		printf("Error: falta el programa\n");
		ret = -1;
	} else {

		pid_t pid = fork();		
		int out, err, null;

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
				
				ret = faux("Hijo");
				
				out = open("/tmp/daemon.out",O_CREAT | O_RDWR, 00777);
				err = open("/tmp/daemon.err", O_CREAT | O_RDWR, 00777);
				null = open("/dev/null", O_CREAT | O_RDWR, 00777);
				
				if (out == -1 || err == -1 || null == -1) {
					printf("Error %d: %s\n", errno, strerror(errno));
					exit(1);
				}
				
				if (dup2(out,2) == -1 || dup2(err,1) == -1 || dup2(null,0) == -1) {
					printf("Error %d: %s\n", errno, strerror(errno));
					exit(1);
				}
				
				if (execvp(argv[1], argv + 1) == -1) {
					printf("Error %d: %s\n", errno, strerror(errno));
					exit(1);
				}
			break;
			default:
				ret = faux("Padre");
		}
	}

	return ret;
}
