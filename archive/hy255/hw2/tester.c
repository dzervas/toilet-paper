#include <stdio.h>
#include <string.h>
#include "mystring.h"

int main() {
	int i;
	char *tests[][2] = {
		{ "hello", "hello"},
		{ "hello", "world"},
		{ " ", "world"},
		{ "hello", "world"},
		{ "hello", "world"},
	};

	for (i = 0; i < 5; i++)
		printf("Strings: %s, %s with n: %d\n\tstrlen: %zu ms_lenght: %zu\
\tstrcpy: %s, ms_copy: %s\n\tstrncpy: %s, ms_ncopy: %s\n\tstrcat: %s, ms_concat: %s\
\tstrncat: %s, ms_nconcat: %s\n\tstrcmp: %d, ms_compare: %d\n\tstrncmp: %d, ms_ncompare: %d\
\tstrstr: %s, ms_search: %s", tests[i][0], tests[i][1], i,
strlen(tests[i][0]), ms_length(tests[i][0]),
strcpy(tests[i][0], tests[i][1]), ms_copy(tests[i][0], tests[i][1]),
strncpy(tests[i][0], tests[i][1], i), ms_ncopy(tests[i][0], tests[i][1], i),
strcat(tests[i][0], tests[i][1]), ms_concat(tests[i][0], tests[i][1]),
strncat(tests[i][0], tests[i][1], i), ms_nconcat(tests[i][0], tests[i][1], i),
strcmp(tests[i][0], tests[i][1]), ms_compare(tests[i][0], tests[i][1]),
strncmp(tests[i][0], tests[i][1], i), ms_ncompare(tests[i][0], tests[i][1], i),
strstr(tests[i][0], tests[i][1]), ms_search(tests[i][0], tests[i][1])
);

	return 0;
}
