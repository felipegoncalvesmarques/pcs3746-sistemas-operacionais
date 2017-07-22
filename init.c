#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pid = fork();
    int i = 0; 
    if (pid) {
        while (1) {
            i += 3;
        }
	} else {
        while (1) {
            i += 2;
        }
	}
}

