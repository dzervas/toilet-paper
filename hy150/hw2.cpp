#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
	char letter, *buffer, *regexes[argc - 2];
	ifstream file;
	/* Counts the STRING length, not the array length */
	unsigned int buffsiz = 0;

	/* Deal with command line arguments */
	/* If argv[0] is not set, something is REALLY wrong with the system (Windows?) */
	if (argc < 3) {
		cout << "Usage: " << argv[0] << " <file> <format...>" << endl;
		return 1;
	}

	file.open(argv[1], ifstream::in);

	for (int x = 2; x < argc; x++)
		regexes[x - 2] = argv[x];

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
			realloc(buffer, (++buffsiz + 1) * sizeof(char));
			buffer[buffsiz - 1] = letter;
			buffer[buffsiz] = '\0';
		} else if (buffer[0] != '\0') {
			cout << "Buffer: " << buffer << endl;
			buffer[0] = '\0';
			buffsiz = 0;
			cout << "Buffer emptied!" << endl;
		}
	}

	file.close();

	return 0;
} 
