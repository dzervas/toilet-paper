#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LOG_BUFFER 102400

regmatch_t *regex_match(char *, char *);

int main(int argc, char *argv[]) {
	FILE *lp;
	char log[MAX_LOG_BUFFER];

	/* Self name is not needed */
	argc--; argv++;

	if (argc < 2) {
		printf("./Task_B <log_path> <mode> [file_path]\n");
		return 1;
	}

	lp = fopen(argv[0], "r");
	if (!lp) {
		printf("Could not open log file\n");
		return 1;
	}
	fread(log, 1, MAX_LOG_BUFFER, lp);
	fclose(lp);

	switch (argv[1][0]) {
		case '1':
			regex_match("([0-9]+)\t+.*\t+[0-9]\t+1", log);
			break;
		case '2':
			break;
		case '3':
			break;
		default:
			printf("Possible modes: 1,2,3");
			return 0;
	}

	return 0;
}

regmatch_t *regex_match(char *needle, char *haystack) {
	size_t ngroups;
	regex_t compiled;
	regmatch_t *groups;

	regcomp(&compiled, needle, REG_EXTENDED);

	ngroups = compiled.re_nsub + 1;
	groups = malloc(ngroups * sizeof(regmatch_t));

	if (regexec(&compiled, haystack, ngroups, groups, 0))
		return NULL;

	for (size_t i = 0; i < ngroups; i++) {
		printf("%d - %d: %.4s\n", groups[i].rm_so, groups[i].rm_eo, haystack + groups[i].rm_so);
	}

	return groups;
}
