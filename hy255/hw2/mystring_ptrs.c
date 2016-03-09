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
#include <assert.h>
#include <stddef.h>
#include "mystring.h"

/*
 Return the length of string string.
 It is a checked runtime error for string to be NULL.
*/
size_t ms_length(const char *string) {
	size_t length = 0;
	assert(string); /* Works because NULL and FALSE are identical. */

	while (*(string + length)) /* Works because end-of-string and FALSE are identical. */
		length++;

	return length;
}

/*
 Copies src string to dest string.
 Returns pointer to dest string
 It is a checked runtime error for src and n to be NULL or 0.
*/
char *ms_copy(char *dest, const char *src) {
	/* Copy the letters of the src AND the null byte */
	ms_ncopy(dest, src, ms_length(src) + 1);

	return dest;
}

/*
 Copies n first letters from src string to dest string.
 Returns pointer to dest string
 It is a checked runtime error for src and n to be NULL or 0.
*/
char *ms_ncopy(char *dest, const char *src, size_t n) {
	size_t i;
	assert(src); /* Works because NULL and FALSE are identical. */

	for (i = 0; i < n && *(src + i) != '\0'; i++)
		*(dest + i) = *(src + i);

	for (; i < n; i++)
		*(dest + i) = '\0';

	return dest;
}


/*
 Appends src string to dest string
 Returns pointer to dest string
 It is a checked runtime error for dest, src to be NULL.
*/
char *ms_concat(char *dest, const char *src) {
	/* Concatonate the letters of the src AND the null byte */
	ms_nconcat(dest, src, ms_length(src) + 1);

	return dest;
}

/*
 Appends n first letters of src string to dest string
 Returns pointer to dest string
 It is a checked runtime error for dest, src.
*/
char *ms_nconcat(char *dest, const char *src, size_t n) {
	size_t dest_len, i;

	assert(dest); /* Works because NULL and FALSE are identical. */
	assert(src);

	dest_len = ms_length(dest);

	for (i = 0 ; i < n && *(src + i) != '\0' ; i++)
		*(dest + dest_len + i) = *(src + i);
	*(dest + dest_len + i) = '\0';

	return dest;
}


/*
 Compares s1 with s2
 Returns 1 if s1 is greater, 0 if equal and -1 if less than s2
 It is a checked runtime error for s1, s2.
*/
int ms_compare(const char *s1, const char *s2) {
	return ms_ncompare(s1, s2, ms_length(s1));
}

/*
 Compares first n characters of s1 with s2
 Returns 1 if s1 is greater, 0 if equal and -1 if less than s2
 It is a checked runtime error for s1, s2.
*/
int ms_ncompare(const char *s1, const char *s2, size_t n) {
	size_t i;

	assert(s1);
	assert(s2);

	for (i = 0 ; i < n; i++) {
		if (*(s2 + i) == '\0')
			return  1;
		if (*(s1 + i) < *(s2 + i))
			return -1;
		if (*(s1 + i) > *(s2 + i))
			return  1;
	}

	if (*(s2 + i) != '\0')
		return -1;

	return 0;
}

/*
 Searches needle in haystack
 Returns a pointer to the first occurance of needle
 It is a checked runtime error for haystack, needle
*/
char *ms_search(const char *haystack, const char *needle) {
	size_t i, needle_lng;

	assert(haystack);
	assert(needle);

	needle_lng = ms_length(needle);

	for (i = 0; *(haystack + i) != '\0' && ms_length(haystack + i) > needle_lng; i++) {
		if (ms_ncompare(haystack + i, needle, needle_lng) == 0)
			return (char *) haystack + i;
	}

	return NULL;
}
