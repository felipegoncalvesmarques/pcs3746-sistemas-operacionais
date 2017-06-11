#include <stdio.h>
#include <stdlib.h>
#include <sched.h>


int main() {
	int total = 0;
	time_t t;

	struct sched_param param = { .sched_priority = 1 };

	pid_t pid = getpid();

	printf("Default scheduler: %d (SCHED_NORMAL) from process pid: %d \n", sched_getscheduler(pid), pid);
	sched_setscheduler(pid, SCHED_RR, &param);
	printf("New scheduler: %d (SCHED_RR) from process pid: %d \n", sched_getscheduler(pid), pid);
	
	
	srand((unsigned) time(&t));

	while (1) {
		total += rand();
	}
}
