#include <stdio.h>

int main(int argc, char *argv[]) {
	FILE *lp;

	if (argc < 2) {
		printf("./Task_B <log_path> <mode> [file_path]\n");
		return 1;
	}

	lp = fopen(argv[0], "r");
	if (!lp) {
		printf("Could not open log file\n");
		return 1;
	}

	switch (argv[1][0]) {
		case '1':
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
