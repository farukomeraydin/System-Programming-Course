//dd if=/dev/zero bs=512 of=test.dat count=10000 command creates 5MB file. Then compile and run it
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

void exit_sys(const char *msg);

int main(void)
{
    int fd;
    char ch;
    ssize_t result;
    size_t count;
    clock_t t1, t2;
    double ts;

    t1 = clock();

    if ((fd = open("test.dat", O_RDONLY)) == -1)
        exit_sys("open");

    while ((result = read(fd, &ch, 1)) > 0)
        ;
    if (result == -1)
        exit_sys("read");

    close(fd);

    t2 = clock();

    ts = (double)(t2 - t1) / CLOCKS_PER_SEC;

    printf("Elapsed time: %f\n", ts);

    return 0;
}

void exit_sys(const char *msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}
