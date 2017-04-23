#define _GNU_SOURCE

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <openssl/md5.h>
#include <sys/stat.h>

void log_action(const char *path, unsigned const char is_access) {
	FILE *(*_fopen)(const char*, const char*);
	FILE *lp;
	char ttime[80], tdate[80], abspath[1024], logbuff[1024];
	struct stat statinfo;
	struct tm *timeinfo;
	time_t rawtime;

	FILE *fp;
	char buffer[1024];
	unsigned char hash[MD5_DIGEST_LENGTH];
	int md5count;
	MD5_CTX mdContext;

	_fopen = dlsym(RTLD_NEXT, "fopen");

	/* Get absolute path */
	realpath(path, abspath);

	/* Get time */
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(ttime, 80, "%T", timeinfo);
	strftime(tdate, 80, "%F", timeinfo);

	/* Print the actual log */
	sprintf(logbuff, "UID\tfile_name");

	for (unsigned long i = 0; i < (strlen(abspath)/8); i++)
		sprintf(logbuff + strlen(logbuff), "\t");

	sprintf(logbuff + strlen(logbuff), "date\t\ttime\t\topen\taction_denied\thash\n");
	sprintf(logbuff + strlen(logbuff), "%d\t%s\t%s\t%s\t%d\t%d\t\t", (unsigned int) getuid(), abspath, tdate,
			ttime, is_access, -1 * stat(abspath, &statinfo));

	/* Calculate and print hash */
	fp = _fopen(abspath, "rb");

	if (fp) {
		MD5_Init(&mdContext);
		while ((md5count = fread(buffer, 1, 1024, fp)))
			MD5_Update(&mdContext, buffer, md5count);
		MD5_Final(hash, &mdContext);

		for(md5count = 0; md5count < MD5_DIGEST_LENGTH; md5count++)
			sprintf(logbuff + strlen(logbuff), "%02x", hash[md5count]);
	} else
		sprintf(logbuff + strlen(logbuff), "(none)");

	fclose(fp);

	sprintf(logbuff + strlen(logbuff), "\n");

	/* Open log for writing */
	lp = _fopen("log.txt", "a");
	if (!lp) {
		sprintf(logbuff + strlen(logbuff), "Could not open log.txt\n");
		return;
	}
	fputs(logbuff, lp);
	fclose(lp);
}

void plog_action(int ptr, unsigned const char is_access) {
	char path[1024], proclink[1024];
	ssize_t size;

	sprintf(proclink, "/proc/self/fd/%d", ptr);
	size = readlink(proclink, path, 1024);
	path[size] = '\0';

	log_action(path, is_access);
}

void flog_action(FILE *ptr, unsigned const char is_access) {
	plog_action(fileno(ptr), is_access);
}

int open(const char *path, int oflag, ...) {
	int (*_func)(const char *, int, ...);

	log_action(path, 1);

	_func = dlsym(RTLD_NEXT, "open");
	return  (*_func)(path, oflag);
}

FILE *fopen(const char *path, const char *mode) {
	FILE *(*_func)(const char *, const char *);

	log_action(path, 1);

	_func = dlsym(RTLD_NEXT, "fopen");
	return (*_func)(path, mode);
}

ssize_t write(int fildes, const void *buf, size_t nbyte) {
	ssize_t (*_func)(int, const void *, size_t);

	plog_action(fildes, 0);

	_func = dlsym(RTLD_NEXT, "write");
	return (*_func)(fildes, buf, nbyte);
}

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) {
	size_t (*_func)(const void *, size_t, size_t, FILE *);
	size_t result;

	_func = dlsym(RTLD_NEXT, "fwrite");
	result = (*_func)(ptr, size, nmemb, stream);
	fflush(stream);

	flog_action(stream, 0);

	return result;
}
