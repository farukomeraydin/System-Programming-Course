#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main (void){

    int result;
    if ((result = open("test.dat", 0, O_RDONLY)) == -1){
        perror("open failed");
        exit(EXIT_FAILURE);
    }

    printf("success...\n");

    return 0;
}
