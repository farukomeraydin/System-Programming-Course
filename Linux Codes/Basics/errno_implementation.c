#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

int main (void){

    int result;
    if ((result = open("test.dat", 0, O_RDONLY)) == -1){
        fprintf(stderr, "open failed: %d\n", errno);
        exit(EXIT_FAILURE);
    }

    printf("success...\n");

    return 0;
}
