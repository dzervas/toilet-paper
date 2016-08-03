/*
Dimitris Zervas <dzervas@dzervas.gr> [A.M. 3502]
Date 07/03/2015

Licensed under the beer-ware license.
"THE BEER-WARE LICENSE" (Revision 42):
dzervas <dzervas@dzervas.gr> wrote this code (unless said otherwise in the file).
As long as you retain this notice and I am mensioned somewhere in the credits (if any),
you can do whatever you want with this stuff. If we meet some day, and you think this stuff is worth it,
you can buy me a beer in return.
*/
/* Header was (almost) copied from string.h man page, to be sure that the 2 libs are compatible */

/* strlen */
size_t ms_length(const char *);

/* strcpy */
char *ms_copy(char *, const char *);

/* strcpy */
char *ms_ncopy(char *, const char *, size_t);

/* strcat */
char *ms_concat(char *, const char *);

/* strncat */
char *ms_nconcat(char *, const char *, size_t);

/* strcmp */
int ms_compare(const char *, const char *);

/* strncmp */
int ms_ncompare(const char *, const char *, size_t);

/* strstr */
char *ms_search(const char *, const char *);
