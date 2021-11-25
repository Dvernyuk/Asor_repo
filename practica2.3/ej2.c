#include <stdio.h>
#include <sched.h>

int main() {
	int pid = 0;
	int sched = sched_getscheduler(pid);
	int max = sched_get_priority_max(sched);
	int min = sched_get_priority_min(sched);
	struct sched_param sp;

	printf("Planificación ");
	switch (sched) {
		case SCHED_OTHER:
			printf("Other\n");
		break;
		case SCHED_FIFO:
			printf("FIFO\n");
		break;
		case SCHED_RR:
			printf("Round-Robin\n");
		break;
		default:
			printf("Error\n");
	}

	sched_getparam(pid, &sp);
	printf("Prioridad %i\n", sp.sched_priority);
	printf("Prioridad max %i\n", max);
	printf("Prioridad min %i\n", min);

	return 0;
}
