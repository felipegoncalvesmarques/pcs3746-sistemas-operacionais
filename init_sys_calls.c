#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pid = fork();
    int i = 0; 
    if (pid) {
        printf("Parent process, exiting!\n");
        if (fork()) {
            while(1);
        } else {
            exit(0);
        }
	} else {
        printf("Child process, exec\n");
        int error = execl("./exec_process.c", "exec_process", "", (char*) NULL);
	}
}

