#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main() {
	int ret = 0;	
	int fd1, fd2, fd3;
	char buffer[256];
	ssize_t bytes;
	int cambios, nPip = 0;
	fd_set rfds;

	mkfifo("tuberia1", 0644);
	mkfifo("tuberia2", 0644);

	fd1 = open("tuberia1", O_RDONLY | O_NONBLOCK);
	fd2 = open("tuberia2", O_RDONLY | O_NONBLOCK);
	
	while(cambios != -1 ) {
		bytes = 255;
		FD_ZERO(&rfds);
		FD_SET(fd1, &rfds);
		FD_SET(fd2, &rfds);

		if(fd1 < fd2) {
			cambios = select(fd2 + 1, &rfds, NULL,NULL,NULL);
		} else {
			cambios = select(fd1 + 1, &rfds, NULL,NULL,NULL);
		}

		if(cambios == -1) {
			printf("Error %d: %s\n", errno, strerror(errno));
			ret = -1;			
		} else if(cambios > 0) {
			
			if(FD_ISSET(fd1, &rfds)) {
				nPip = 1;
				fd3 = fd1;
			} else {
				nPip = 2;
				fd3 = fd2;
			}
			
			while(bytes == 255) {
				bytes = read(fd3, buffer, 255);
				buffer[bytes] = '\0';
				printf("Leida la tuberia %i; Datos: %s", nPip, buffer);
			}
			
			if(bytes != 255 && nPip == 1) {
				close(fd1);
				fd1 = open("tuberia1", O_RDONLY | O_NONBLOCK);

			} else if(bytes != 255 && nPip == 2) {
				close(fd2);
				fd2 = open("tuberia2", O_RDONLY | O_NONBLOCK);
			}
		}
	}
	
	close(fd1);
	close(fd2);
	
	return ret;
}
