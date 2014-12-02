#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

typedef struct entry entry;
struct entry {
	char *First;
	char *Last;
	int Tel;
};

int sort(entry* table, unsigned int entries);
int search(char* first, char* last, entry* table, unsigned int entries);

int main(int argc, char *argv[]) {
	char command, *buffer, *first, *last;
	int tmp;
	unsigned int entries = 0, i;
	entry *contacts;
	FILE *database;

	argc--;
	if (argc < 1)
		printf("Usage: ./hw3 <database>");
	argv++;

	contacts = (entry *) malloc(sizeof(entry));
	database = fopen(argv[0], "r");
	buffer = (char *) calloc(BUFSIZ, sizeof(char));
	contacts[0].First = (char *) calloc(BUFSIZ, sizeof(char));
	contacts[0].Last = (char *) calloc(BUFSIZ, sizeof(char));

	while (fgets(buffer, BUFSIZ, database) != NULL) {
		sscanf(buffer, " %s %s %d",
				contacts[entries].First,
				contacts[entries].Last,
				&contacts[entries].Tel);
		entries++;

		contacts = (entry *) realloc(contacts, (entries + 1) * sizeof(entry));
		contacts[entries].First = (char *) calloc(BUFSIZ, sizeof(char));
		contacts[entries].Last = (char *) calloc(BUFSIZ, sizeof(char));
	}
	printf("%d Entries\n", entries);

	fclose(database);

	first = (char *) calloc(1, sizeof(char));
	last = (char *) calloc(1, sizeof(char));

	printf("> ");
	while (scanf(" %c", &command) > -1) {
		switch (command) {
			case 'd':
				scanf("%s %s", first, last);
				tmp = search(first, last, contacts, entries);
				if (tmp != -1) {
					contacts = (entry *) realloc(contacts, entries * sizeof(entry));
					entries--;
					printf("Deleted %s %s\n",
							contacts[tmp].First,
							contacts[tmp].Last);
					contacts[tmp].First = (char *) calloc(1, sizeof(char));
					sort(contacts, entries);
				} else
					printf("Contact not found!\n");

				first = (char *) calloc(1, sizeof(char));
				last = (char *) calloc(1, sizeof(char));
				break;
			case 'f':
				scanf("%s", first);
				if ((tmp = search(first, NULL, contacts, entries)) != -1)
					printf("%s %s: %d\n",
							contacts[tmp].First,
							contacts[tmp].Last,
							contacts[tmp].Tel);
				break;
			case 'h':
				printf("Usage: <command> <args...>\n");
				printf("Commands:\n");
				printf("d <First name> <Last name>\t\tDelete contact\n");
				printf("f <Name>\t\t\t\tSearch contact with first or last name <name>\n");
				printf("h\t\t\t\t\tImagination is the key\n");
				printf("i <First name> <Last name> <Telephone>\tInsert or replace contact\n");
				printf("p\t\t\t\t\tPrint the address book\n");
				printf("q\t\t\t\t\tQuit\n");
				break;
			case 'i':
				scanf("%s %s %d",
						contacts[entries].First,
						contacts[entries].Last,
						&contacts[entries].Tel);

				sort(contacts, entries);
				entries++;

				contacts = (entry *) realloc(contacts, (entries + 1) * sizeof(entry));
				contacts[entries].First = (char *) calloc(BUFSIZ, sizeof(char));
				contacts[entries].Last = (char *) calloc(BUFSIZ, sizeof(char));
				break;
			case 'p':
				printf("%d Entries\n", entries);
				for (i = 0; i < entries; i++)
					printf("%s %s: %d\n",
							contacts[i].First,
							contacts[i].Last,
							contacts[i].Tel);
				break;
			case 'q':
				database = fopen(argv[0], "w");
				for (i = 0; i < entries; i++)
					fprintf(database, "%s %s %d\n",
							contacts[i].First,
							contacts[i].Last,
							contacts[i].Tel);
				fclose(database);
				return 0;
				break;
			default:
				printf("Wrong command, press h for help\n");
				break;
		}

		printf("> ");
	}

	database = fopen(argv[0], "w");
	for (i = 0; i < entries; i++)
		fprintf(database, "%s %s %d\n",
				contacts[i].First,
				contacts[i].Last,
				contacts[i].Tel);
	fclose(database);

	return 0;
}

int sort(entry* table, unsigned int entries) {
	/* Only the last entry is unsorted */
	int place = -1, state, lstate, pstate = -1, plstate = -1, counter;
	unsigned int i;
	entry *tmp;

	/* Find the place to insert the entry */
	for (i = 0; i < entries; i++) {
		state = strcmp(table[i].First, table[entries].First);
		lstate = strcmp(table[i].Last, table[entries].Last);
		printf("%d %d%s\n", state, lstate, table[entries].First);

		if ((pstate < 0 && state > 0) ||
				(plstate < 0 && lstate > 0) ||
				(state == 0 && lstate == 0)) {
			place = i;
			break;
		}

		pstate = state;
		plstate = lstate;
	}

	if (place < 0) {
		printf("Something went wrong while sorting!");
		exit(1);
	}

	if (state == 0 && lstate == 0) {
		/* TODO: Here for bonus of multiple telephones */
		printf("Hello %d\n", place);
		table[place].Tel = table[entries - 1].Tel;
		table = (entry *) realloc(table, entries * sizeof(entry));
		entries--;
		return 2;
	}

	/* Place can't be negative here */
	tmp = (entry *) calloc(entries + 1, sizeof(entry));
	counter = 0;

	for (i = 0; i < entries; i++) {
		if ((int) i > place || table[i + counter].First == NULL)
			counter++;
		tmp[i] = table[i + counter];
	}

	table = tmp;

	return 0;
}

int search(char* first, char* last, entry* table, unsigned int entries) {
	unsigned int i;

	for (i = 0; i < entries; i++) {
		if (last == NULL) {
			if (strcmp(table[i].First, first) == 0 ||
					strcmp(table[i].Last, first) == 0)
				return i;
		} else {
			if (strcmp(table[i].First, first) == 0 &&
					strcmp(table[i].Last, last) == 0)
				return i;
		}
	}

	return -1;
}
