#include <stdio.h>
#include <stdlib.h>

int main() {
    int i = 0;
    printf("New process from exec\n");
    for (;;) {
        i += 2;
    }
    return 0;
}