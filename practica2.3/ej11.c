#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char **argv) {
	int ret = 0;
	sigset_t set;
	char *sleep_secs;
	int seg;

	if (argc != 2) {
		printf("Error: faltan los segundos\n");
		ret = -1;
	} else {

		sigemptyset(&set);
		sigaddset(&set, SIGINT);
		sigaddset(&set, SIGTSTP);
		sigprocmask(SIG_BLOCK, &set, NULL);

		sleep_secs = getenv("SLEEP_SECS");
		seg = atoi(sleep_secs);
		sleep(seg);

		sigset_t pending;
		sigpending(&pending);

		if (sigismember(&pending, SIGINT) == 1) {
			printf("Recibi SIGINT\n");
			sigdelset(&set, SIGINT);
		} else {
			printf("No recibi SIGINT\n");
		}

		if (sigismember(&pending, SIGTSTP) == 1) {
			printf("Recibi SIGTSTP\n");
			sigdelset(&set, SIGTSTP);
		} else {
			printf("No recibi SIGTSTP\n");
		}

		sigprocmask(SIG_UNBLOCK, &set, NULL);
	}

	return ret;
}
