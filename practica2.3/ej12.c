#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

volatile int nInt = 0;
volatile int nTstp = 0;

void faux(int signal){
  if (signal == SIGINT)
		nInt++;
  if (signal == SIGTSTP)
		nTstp++;
}

int main(){
  struct sigaction sig;

  sigaction(SIGINT, NULL, &sig);
  sig.sa_handler = faux;
  sigaction(SIGINT, &sig, NULL);
  sigaction(SIGTSTP, NULL, &sig);
  sig.sa_handler = faux;
  sigaction(SIGTSTP, &sig, NULL);

  sigset_t set;
	sigemptyset(&set);

	while (nInt + nTstp < 10)
		sigsuspend(&set);

	printf("SIGINT %i\n", nInt);
	printf("SIGTSTP %i\n", nTstp);

  return 0;
}
