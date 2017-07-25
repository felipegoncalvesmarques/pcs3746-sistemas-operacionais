#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int i = 0;
    while(1) {
        if(fork()) {
            i += 3;
        } else {
            i += 4;
        }
    }
    return 0;
}