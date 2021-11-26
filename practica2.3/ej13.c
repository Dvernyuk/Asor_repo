#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>

volatile bool stop = false;

void faux(int senial){
	if (senial == SIGUSR1)
		stop = true;
}

int main(int argc, char **argv) {
	int ret = 0;
	int i, seg;
	sigset_t set;
	struct sigaction sig;

	if (argc != 2) {
		printf("Error: faltan los segundos\n");
		ret = -1;
	} else {

		sigemptyset(&set);
		sigaddset(&set, SIGUSR1);
		sigprocmask(SIG_UNBLOCK, &set, NULL);

		sigaction(SIGUSR1, NULL, &sig);
		sig.sa_handler = faux;
		sigaction(SIGUSR1, &sig, NULL);

		seg = atoi(argv[1]);

		i = 0;
		while (i < seg && !stop) {
			sleep(1);
			i++;
		}

		if (!stop)
			unlink(argv[0]);
	}

	return ret;
}
