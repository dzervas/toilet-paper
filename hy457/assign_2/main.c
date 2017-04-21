#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
	FILE *fd;
	int pd;

	printf("test.txt file is used for all tests\n\n");

	printf("Calling fopen()...\n");
	fd = fopen("test.txt", "w");
	if (!fd) {
		printf("fopen() returned NULL\n");
		return 1;
	}
	printf("Success!\n");

	printf("Calling fwrite()...\n");
	if (fwrite("Hello World\n", 1, 12, fd) != 12) {
		printf("fwrite() returned NULL\n");
		return 1;
	}
	printf("Success!\n");

	fclose(fd);

	printf("Calling open()...\n");
	pd = open("test.txt", O_WRONLY);
	if (pd == -1) {
		printf("open() returned -1\n");
		return 1;
	}
	printf("Success!\n");

	printf("Calling write()...\n");
	if (write(pd, "Hello World\n", 12) != 12) {
		printf("write() returned NULL\n");
		return 1;
	}
	printf("Success!\n");

	close(pd);

	return 0;
}
