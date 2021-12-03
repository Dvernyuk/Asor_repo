#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>


int main(int argc, char **argv){
	int ret = 0;
	int fd;
	
	remove("tuberia");
	if(mkfifo("tuberia", 0777) == -1){
		printf("Error %d: %s\n", errno, strerror(errno));
		ret = -1;
	} else {
		fd = open("tuberia", O_WRONLY, O_CREAT);
		write(fd, argv[1], strlen(argv[1]));
		close(fd);
	}

	return ret;
}
