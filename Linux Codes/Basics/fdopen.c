#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void exit_sys(const char *msg);

int main(int argc, char *argv[])
{
	int fd;
	ssize_t result;
	FILE *f;
	char buf[10 + 1];
	int ch;

	if ((fd = open("test.txt", O_RDONLY)) == -1)
		exit_sys("open");

	if ((result = read(fd, buf, 10)) == -1)
		exit_sys("read");

	buf[result] = '\0';
	printf("read bytes: %s\n", buf);

	if ((f = fdopen(fd, "r")) == NULL) {
		fprintf(stderr, "cannot open file!..\n");
		exit(EXIT_FAILURE);
	}

	while ((ch = fgetc(f)) != EOF)
		putchar(ch);

	if (ferror(f)) {
		fprintf(stderr, "cannot read file!..\n");
		exit(EXIT_FAILURE);
	}

	fclose(f);

	return 0;
}

void exit_sys(const char *msg)
{
	perror(msg);

	exit(EXIT_FAILURE);
}
