#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(){
    char c;
    while (!feof(stdout)) {
        c = getchar();
        fprintf(stderr, "%c", c);
    }
    return 0;
}
