#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv) {
	int ret = 0;
	int fd[2];
	pipe(fd);
	pid_t pid = fork();

	switch(pid) {
		case -1:
			printf("Error %d: %s\n", errno, strerror(errno));
			ret = -1;
		break;
		case 0:
			close(fd[0]);
			dup2(fd[1], 1);
			close(fd[1]);
			execlp(argv[1], argv[1], argv[2], 0);
		break;
		default:
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd[0]);
			execlp(argv[3], argv[3], argv[4], 0);
	}

	return ret;
}
