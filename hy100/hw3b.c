#include <stdio.h>

int main(int argc, char *argv[]) {

}

unsigned char unique(unsigned char *array) {
	unsigned char buffer[9], i;

	for (i = 0; i < 9; i++) {
		if (buffer[array[i]] != 0)
			printf("Error here!");

		buffer[array[i]]++;
	}
}
