#include <stdio.h>
#include <stdlib.h>
#include "symtable.h"

void print(const char *a, void *b, void *c) {
	printf("%d\n", *((int*) b));
}

int main() {
	SymTable_T a;
	char *data1;
	int *data2;
	unsigned int i;
	data1 = (char *) malloc(sizeof(char) * 6);
	data2 = (int *) malloc(sizeof(int));
	data1[0] = 'w';
	data1[1] = 'o';
	data1[2] = 'r';
	data1[3] = 'l';
	data1[4] = 'd';
	data1[5] = '\0';
	*data2 = 1234;

	a = SymTable_new();
	printf("Length: %u\n", SymTable_getLength(a));
	printf("Put %s in hello->data1: %d\n", data1, SymTable_put(a, "hello", data1));
	printf("Length: %u\n", SymTable_getLength(a));
	printf("Put %d in world->data2: %d\n", *data2, SymTable_put(a, "world", data2));
	printf("Length: %u\n", SymTable_getLength(a));
	printf("Data in 'hello': %s\n", (char *) SymTable_get(a, "hello"));
	printf("Data in 'world': %d\n", *((int *) SymTable_get(a, "world")));
	printf("Contains 'bla': %d\n", SymTable_contains(a, "bla"));
	printf("Contains 'hello': %d\n", SymTable_contains(a, "hello"));
	printf("Contains 'world': %d\n", SymTable_contains(a, "world"));
	printf("Remove 'bla': %d\n", SymTable_remove(a, "bla"));
	printf("Remove 'hello': %d\n", SymTable_remove(a, "hello"));
	printf("Contains 'bla': %d\n", SymTable_contains(a, "bla"));
	printf("Contains 'hello': %d\n", SymTable_contains(a, "hello"));
	printf("Contains 'world': %d\n", SymTable_contains(a, "world"));
	printf("Length: %u\n", SymTable_getLength(a));
	printf("Data in 'world': %d\n", *((int *) SymTable_get(a, "world")));
	printf("Put %s in hello->data1: %d\n", data1, SymTable_put(a, "hello", data1));
	printf("Length: %u\n", SymTable_getLength(a));
	data1 = realloc(data1, 11000 * sizeof(char));
	printf("Putting 100k bindings into sym table...\n");
	for (i = 0; i < 10000; i++) {
		data1[i/92] = 33 + (i % 92);
		data1[(i/92) + 1] = '\0';
		SymTable_put(a, data1, data2);
	}
	printf("Done.");
	printf("Length: %u\n", SymTable_getLength(a));
	SymTable_map(a, &print, NULL);
	SymTable_free(a);

	return 0;
}
