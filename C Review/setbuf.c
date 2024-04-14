/*
setbuf function is used for changing the address of buffer that is used for the file. 
Buffer size is not changed. If 2nd parameter is entered as NULL, the file will be in no buffered mode.
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void disp_hex(const void* buf, size_t size, size_t lbytes)
{
	size_t i, k, remainder;
	unsigned char* cbuf = (unsigned char*)buf;

	for (i = 0; i < size; ++i) {
		if (i % lbytes == 0)
			printf("%08x ", (unsigned int)i);

		printf("%02X ", cbuf[i]);

		if (i % lbytes == lbytes - 1) {
			for (k = 0; k < lbytes; ++k)
				printf("%c", iscntrl(cbuf[i - lbytes + k]) ? '.' : cbuf[i - lbytes + k]);
			putchar('\n');
		}
	}

	remainder = size % lbytes;
	for (k = 0; k < 3 * (lbytes - remainder); ++k)
		putchar(' ');

	for (k = 0; k < remainder; ++k)
		printf("%c", iscntrl(cbuf[i - remainder + k]) ? '.' : cbuf[i - remainder + k]);
	putchar('\n');
}

int main(void)
{
	FILE* f;
	char buf[BUFSIZ];

	if ((f = fopen("test.txt", "r+")) == NULL) {
		fprintf(stderr, "cannot open file!..\n");
		exit(EXIT_FAILURE);
	}

	setbuf(f, buf);

	fgetc(f);

	disp_hex(buf, BUFSIZ, 16);

	printf("---------------------------------------------\n");

	fputc('x', f);
	disp_hex(buf, BUFSIZ, 16);

	fclose(f);

	return 0;
}
