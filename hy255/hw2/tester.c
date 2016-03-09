#include <stdio.h>
#include <string.h>
#include "mystring.h"

int main() {
	char a[20] = "hello";
	char b[20] = "yorld";

	printf("\nStrings: a = %s b = %s\n", a, b);
	printf("\tms_length: a = %lu b = %lu\n", ms_length(a), ms_length(b));

	printf("\nStrings: a = %s b = %s\n", a, b);
	printf("\tms_copy(a, b) = %s\n", ms_copy(a, b));

	ms_copy(a, "hello");
	ms_copy(b, "yolo");

	printf("\nStrings: a = %s b = %s\n", a, b);
	printf("\tms_ncopy(a, b, 2) = %s\n", ms_ncopy(a, b, 2));

	ms_copy(a, "hello");
	ms_copy(b, "yolo");

	printf("\nStrings: a = %s b = %s\n", a, b);
	printf("\tms_concat(a, b) = %s\n", ms_concat(a, b));

	ms_copy(a, "hello");
	ms_copy(b, "yolo");

	printf("\nStrings: a = %s b = %s\n", a, b);
	printf("\tms_nconcat(a, b, 2) = %s\n", ms_nconcat(a, b, 2));

	ms_copy(a, "hello");
	ms_copy(b, "yolo");

	printf("\nStrings: a = %s b = %s\n", a, b);
	printf("\tms_compare(a, b) = %d\n", ms_compare(a, b));

	ms_copy(a, "hello");
	ms_copy(b, "yolo");

	printf("\nStrings: a = %s b = %s\n", a, b);
	printf("\tms_ncompare(a, b, 2) = %d\n", ms_ncompare(a, b, 2));

	ms_copy(a, "hello");
	ms_copy(b, "yolo");

	printf("\nStrings: a = %s b = %s\n", a, b);
	printf("\tms_search(a, \"ll\") = %s\n", ms_search(a, "ll"));

	return 0;
}
