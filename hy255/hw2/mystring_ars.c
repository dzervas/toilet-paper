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
#include <stddef.h>

/*
 Return the length of string string.
 It is a checked runtime error for string to be NULL.
*/
size_t ms_length(const char string[]) {
	size_t length = 0;
	assert(string); /* Works because NULL and FALSE are identical. */

	while (string[length]) /* Works because end-of-string and FALSE are identical. */
		length++;

	return length;
}

/*
 Copies src string to dest string.
 Returns pointer to dest string
 It is a checked runtime error for src and n to be NULL or 0.
*/
char *ms_copy(char dest[], const char src[]) {
	size_t i;
	assert(src); /* Works because NULL and FALSE are identical. */

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];

	return dest;
}

/*
 Copies n first letters from src string to dest string.
 Returns pointer to dest string
 It is a checked runtime error for src and n to be NULL or 0.
*/
char *ms_ncopy(char dest[], const char src[], size_t n) {
	size_t i;
	assert(src); /* Works because NULL and FALSE are identical. */
	assert(n);

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];

	for (; i < n; i++)
		dest[i] = '\0';

	return dest;
}


/*
 Appends src string to dest string
 Returns pointer to dest string
 It is a checked runtime error for dest, src to be NULL.
*/
char *ms_concat(char dest[], const char src[]) {
	size_t dest_len, i;

	assert(dest); /* Works because NULL and FALSE are identical. */
	assert(src);

	dest_len = my_length(dest);

	for (i = 0 ; src[i] != '\0' ; i++)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';

	return dest;
}

/*
 Appends n first letters of src string to dest string
 Returns pointer to dest string
 It is a checked runtime error for dest, src and n to be NULL or 0.
*/
char *ms_nconcat(char dest[], const char src[], size_t n) {
	size_t dest_len, i;

	assert(dest); /* Works because NULL and FALSE are identical. */
	assert(src);
	assert(n);

	dest_len = my_length(dest);

	for (i = 0 ; i < n && src[i] != '\0' ; i++)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';

	return dest;
}


char *ms_compare(const char s1[], const char s2[]) {
	size_t s1_len, s2_len, i, cmp;

	assert(s1);
	assert(s2);
	assert(n);

	s1_len = my_length(s1);
	s2_len = my_length(s2);
	cmp = -1 * my_length(s2);

	for (i = 0 ; i < s1_len && i < s2_len; i++) {
		if (s1[i] == s2[i])
			cmp++;
	}

	if (cmp == 0 && s1_len > s2_len)
		cmp += (s1_len - s2_len);

	return cmp;
}

char *ms_ncompare(const char s1[], const char s2[], size_t n) {
	size_t s1_len, s2_len, i, cmp;

	assert(s1);
	assert(s2);
	assert(n);

	s1_len = my_length(s1);
	s2_len = my_length(s2);
	cmp = -1 * my_length(s2);

	for (i = 0 ; i < n && i < s1_len && i < s2_len; i++) {
		if (s1[i] == s2[i])
			cmp++;
	}

	if (cmp == 0 && s1_len > s2_len)
		cmp += (s1_len - s2_len);

	return cmp;
}

char *ms_search(const char haystack[], const char needle[]) {
	size_t i, cmp;

	assert(haystack);
	assert(needle);

	for (i = 0; needle[i] != '\0'; i++) {
		cmp = strcmp(needle + i, haystack);
		if (cmp >= 0)
	}

	if (cmp >= 0)
}