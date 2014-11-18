#include <stdio.h>

int main(int argc, char *argv[]) {
	unsigned char i, buffer[];

	for (i = 0; i < 9; i++) {
		if (sscanf("%d %d %d %d %d %d %d %d %d", buffer[i], buffer[i]+1, buffer[i]+2,
					buffer[i]+3, buffer[i]+4, buffer[i]+5, buffer[i]+6,
					buffer[i]+7, buffer[i]+8) != 8)
			return 1;
	}

	for (i = 0; i < 9; i++) {
		// Line check
		if (!unique(buffer[i]))
			printf("Error in line: %d", i);
		// Row check
		// Block check
	}
}

unsigned char unique(unsigned char *array) {
	unsigned char buff[9], i;

	for (i = 0; i < 9; i++)
		buff[i] = 0;

	for (i = 0; i < 9; i++) {
		if (buff[array[i]] != 0)
			return 0;

		buff[array[i]]++;
	}

	return 1;
}
