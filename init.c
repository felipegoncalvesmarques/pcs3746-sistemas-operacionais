#include <stdio.h>
#include <sched.h>
#include <errno.h>
#include "inic.h"

void childProcess(void);
void parentProcess(void);

int main() {

	struct sched_param param = { .sched_priority = 1 };

	pid_t pid = getpid();

	printf("Default scheduler: %d (SCHED_NORMAL) from process pid: %d \n", sched_getscheduler(pid), pid);
	sched_setscheduler(pid, SCHED_RR, &param);
	printf("New scheduler: %d (SCHED_RR) from process pid: %d \n", sched_getscheduler(pid), pid);
	pid_t processo;

	for (int i = 0; i < 1; i++){
		processo = fork();
		if (processo == 0) {
			break;
		}
	}

	if (processo == 0){
		printf("filho\n");
		int error = execl("./conta", "conta", "", (char*) NULL);
		if (error == -1) {
			printf("An error occured! %s\n", strerror(errno);
		} 
	} else {
		processo = fork();
		if (processo == 0) {
			int error2 = execl("./inOut", "inOut", "", (char*) NULL);
			if (error2 == 1) {
				printf("An error occured %s\n", strerror(errno));
			}
		} else {
			wait(processo);
		}
	}
}
