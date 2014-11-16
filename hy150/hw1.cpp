#include <iostream>

using namespace std;

int main() {
	bool mode = false; /* mode: 0 is space, 1 is word */
	char buffer, letter = 's';
	long int count = 0;

	while(cin.get(buffer)) {
		if ((buffer >= 'a' && buffer <= 'z') || (buffer >= 'A' && buffer <= 'Z') || (buffer >= '0' && buffer <= '9') || buffer == '_') {
			if (!mode) {
				mode = true;
				count++;
			}
		} else
			mode = false;
	}

	if (count == 1)
		letter = ' ';

	cout << "You typed " << count << " word" << letter << endl;
	return 0;
} 
