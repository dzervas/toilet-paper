#include <fstream>
#include <iostream>
#include <regex>

using namespace std;

int main(int argc, char *argv[]) {
	char letter, *buffer, *regexes[argc - 2], add;
	ifstream file;
	/* Counts the STRING length, not the array length */
	unsigned int buffsiz = 0, i, j;

	argc--;
	argv++;

	/* Deal with command line arguments */
	/* If argv[0] is not set, something is REALLY wrong with the system (Windows?) */
	if (argc < 2) {
		cout << "Usage: hw2 <file> <format...>" << endl;
		return 1;
	}

	file.open(argv[0], ifstream::in);

	argc--;
	argv++;

	for (i = 0; i < argc; i++) {
		add = 0;
		for (j = 0; j < (sizeof(argv[i]) / sizeof(char)); j++) {
			if (argv[i][j] == '?' || argv[i][j] == '*')
				add++;
		}

		regexes[i] = (char *) malloc(sizeof(char) *
				(add + (sizeof(argv[i]) / sizeof(char))));

		for (j = 0; j < (sizeof(regexes[i]) / sizeof(char)); j++) {
			if (argv[i][j] == '?' || argv[i][j] == '*') {
				regexes[i][j] = '.';
				regexes[i][j + 1] = argv[i][j];
				j++;
			} else
				regexes[i][j] = argv[i][j];
		}

		cout << regexes[i];
	}

	buffer = (char *) malloc(sizeof(char));
	buffer[0] = '\0';

	while (!file.eof()) {
		letter = file.get();

		if (!file.good()) {
			if (file.eof())
				break;

			cout << "Some weird I/O errors took place." <<
				" *whispers* The end is coming... Run away!" << endl;
			return 1;
		}

		if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z') ||
				(letter >= '0' && letter <= '9') || letter == '_' ||
				letter == '*' || letter == '?') {
			buffer = (char *) realloc(buffer, (++buffsiz + 1) * sizeof(char));
			buffer[buffsiz - 1] = letter;
			buffer[buffsiz] = '\0';
		} else if (buffer[0] != '\0') {
			for (i = 0; i < argc; i++) {
				if (regex_search(buffer, regex(regexes[i])))
					printf("%s\n", buffer);
			}

			buffer[0] = '\0';
			buffsiz = 0;
		}
	}

	file.close();

	return 0;
}
