#define _GNU_SOURCE

#include <dlfcn.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <openssl/md5.h>
#include <sys/stat.h>

void log_action(const char *path, unsigned const char is_access) {
	FILE *(*_fopen)(const char*, const char*);
	char ttime[80], tdate[80];
	struct stat statinfo;
	struct tm *timeinfo;
	time_t rawtime;
	unsigned char hash[MD5_DIGEST_LENGTH];

	FILE *fp;
	char buffer[1024];
	int md5count;
	MD5_CTX mdContext;

	/* Get time */
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(ttime, 80, "%T", timeinfo);
	strftime(tdate, 80, "%F", timeinfo);

	/* Print the actual log */
	printf("UID\tfile_name\tdate\t\ttime\t\topen\taction_denied\thash\n");
	printf("%d\t%s\t%s\t%s\t%d\t%d\t\t", (unsigned int) getuid(), path, tdate,
			ttime, is_access, -1 * stat(path, &statinfo));

	/* Calculate and print hash */
	if (is_access) {
		_fopen = dlsym(RTLD_NEXT, "fopen");
		fp = _fopen(path, "rb");

		MD5_Init(&mdContext);
		while ((md5count = fread(buffer, 1, 1024, fp)))
			MD5_Update(&mdContext, buffer, md5count);
		MD5_Final(hash, &mdContext);

		for(md5count = 0; md5count < MD5_DIGEST_LENGTH; md5count++)
			printf("%02x", hash[md5count]);
	}

	printf("\n");
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
