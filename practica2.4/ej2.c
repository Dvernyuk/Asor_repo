#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv) {
	int ret = 0;
	int fd_p_h[2];
	int fd_h_p[2];
	int i;
	char buf[255] = "";
	ssize_t bytes;
	
	pipe(fd_p_h);
	pipe(fd_h_p);
	pid_t pid = fork();
	
	switch(pid) {
		case -1:
			printf("Error %d: %s\n", errno, strerror(errno));
			ret = -1;
		break;
		case 0:
			close(fd_p_h[1]);
			close(fd_h_p[0]);
			ret= -1;
			for(i = 0; i < 10; i++) {
				bytes = read(fd_p_h[0], buf, 255);
				buf[bytes] = '\0';
				printf("Hijo ha recibido -> %s\n", buf);
				sleep(1);

				if(i == 9)
					write(fd_h_p[1], "q", 1);
				else
					write(fd_h_p[1], "l", 1);
			}
		break;
		default:
			close(fd_p_h[0]);
			close(fd_h_p[1]);

			while(strcmp(buf,"q") != 0){
				write(fd_p_h[1], argv[1], sizeof(argv[1]));
				bytes = read(fd_h_p[0], buf, 1);
				buf[bytes] = '\0';
			}
			wait(NULL);
			printf("Los dos procesos estan muertos\n");
		break;
	}

	return ret;
}
