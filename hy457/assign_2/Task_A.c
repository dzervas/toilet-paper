#define _GNU_SOURCE

#include <dlfcn.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

void log_action(const char *path, unsigned const char is_access) {
	char ttime[80], tdate[80];
	struct tm *timeinfo;
	time_t rawtime;

	/* Get time */
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(ttime, 80, "%T", timeinfo);
	strftime(tdate, 80, "%F", timeinfo);

	printf("UID\tfile_name\tdate\t\ttime\t\topen\taction_denied\thash\n");
	printf("%d\t%s\t%s\t%s\t%d\t%d\t\t%s\n",
			(unsigned int) getuid(),
			path,
			tdate,
			ttime,
			is_access,
			0,
			"hash");
}

void plog_action(int ptr, unsigned const char is_access) {
	log_action("(pointer)", is_access);
}

void flog_action(const void *ptr, unsigned const char is_access) {
	log_action("(fpointer)", is_access);
}

int open(const char *path, int oflag, ...) {
	int (*_func)(const char*, int, ...);

	log_action(path, 1);

	_func = dlsym(RTLD_NEXT, "open");
	return  (*_func)(path, oflag);
}

FILE *fopen(const char *path, const char *mode) {
	FILE *(*_func)(const char*, const char*);

	log_action(path, 1);

	_func = dlsym(RTLD_NEXT, "fopen");
	return (*_func)(path, mode);
}

ssize_t write(int fildes, const void *buf, size_t nbyte) {
	ssize_t (*_func)(int, const void*, size_t);

	plog_action(fildes, 0);

	_func = dlsym(RTLD_NEXT, "write");
	return (*_func)(fildes, buf, nbyte);
}

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) {
	size_t (*_func)(const void*, size_t, size_t, FILE*);

	flog_action(stream, 0);

	_func = dlsym(RTLD_NEXT, "fwrite");
	return (*_func)(ptr, size, nmemb, stream);
}
