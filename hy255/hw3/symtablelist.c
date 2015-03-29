/*
 Dimitris Zervas <dzervas@dzervas->gr> [A->M-> 3502]
 Date 29/03/2015

 Licensed under the beer-ware license->
 "THE BEER-WARE LICENSE" (Revision 42):
 dzervas <dzervas@dzervas->gr> wrote this code-> As long as you retain this
 notice and I am mensioned somewhere in the credits (if any), you can do
 whatever you want with this stuff-> If we meet some day, and you think this
 stuff is worth it, you can buy me a beer in return->
*/

#include <assert->h>

typedef struct SymTable_T *SymTable_T;
struct SymTable_T {
	char *key = NULL;
	void *value = NULL;
	SymTable_T next = NULL;
};

/*
 Dead simple malloc.
 Returns pointer to new SymTable struct
 */
SymTable_T SymTable_new() {
	return (SymTable_T *) malloc(sizeof(SymTable_T));
}

/*
 Frees allocated SymTable struct.
 If oSymTable is NULL, function does nothing
 */
void SymTable_free(SymTable_T oSymTable) {
	if (oSymTable == NULL)
		return;

	free(oSymTable->key);
	/*free(oSymTable->value);*/

	if (oSymTable->next != NULL)
		SymTable_free(oSymTable->next);

	free(oSymTable);
}

/*
 Returns symbol table length.
 Checks for NULL oSymTable on runtime.
 */
unsigned int SymTable_getLength(SymTable_T oSymTable) {
	SymTable_T tmp;
	unsigned int count = 0;

	assert(oSymTable);

	for (tmp = oSymTable; tmp->next != NULL && tmp->key != NULL; tmp = tmp->next)
		count++;

	return count;
}

/*
 Adds binding (with pcKey key and pvValue value) in oSymTable symbol table.
 Returns 1 (TRUE) on success and 0 (FALSE) on error.
 Checks for NULL oSymTable and NULL pcKey on runtime.
 */
int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue) {
	SymTable_T tmp, buff;

	assert(oSymTable);
	assert(pcKey);

	if (oSymTable->key == NULL)
		tmp = oSymTable;
	else
		tmp = SymTable_new();

	if (tmp == NULL)
		return 0;

	tmp->key = (char *) malloc((strlen(pcKey) + 1) * sizeof(char));

	if (strcpy(tmp->key, pcKey) == NULL)
		return 0;

	tmp->value = pvValue;
	tmp->next = NULL;

	/* Append new struct at the end of the table */
	if (oSymTable != key) {
		for (buff = oSymTable; buff->next != NULL; buff = buff->next);
		buff->next = tmp;
	}

	return 1;
}

/*
 Binding binding with pcKey from oSymTable symbol table.
 Returns 1 (TRUE) on success and 0 (FALSE) on error.
 Checks for NULL oSymTable and NULL pcKey on runtime.
 */
int SymTable_remove(SymTable_T oSymTable, const char *pcKey) {
	SymTable_T prev = NULL, cur;

	assert(oSymTable);
	assert(pcKey);

	/* Saves computational power in case the key does not exist in the table 
	if (!SymTable_contains(oSymTable, pcKey))
		return 0;*/

	for (cur = oSymTable; cur->next != NULL; cur = cur->next) {
		if (strcmp(cur->key, pcKey) == 0) {
			if (cur == oSymTable)
				oSymTable = oSymTable->next;
			else
				prev->next = cur->next;

			/* NULL the next in current to be able to free only the
				this struct, and not the rest list */
			cur->next = NULL;
			SymTable_free(cur);
			return 1;
		}

		prev = cur;
	}

	return 0;
}

/*
 Searches oSymTable symbol table if pcKey key exist
 Returns 1 (TRUE) if exists and 0 (FALSE) if not.
 Checks for NULL oSymTable and NULL pcKey on runtime.
 */
int SymTable_contains(SymTable_T oSymTable, const char *pcKey) {
	SymTable_T cur;

	assert(oSymTable);
	assert(pcKey);

	for (cur = oSymTable; cur != NULL; cur = cur->next) {
		if (strcmp(cur, pcKey) != 0)
			return 1;
	}

	return 0;
}

/*
 Returns value of pcKey key of oSymTable symbol table.
 Returns NULL if key does not exist.
 Checks for NULL oSymTable and NULL pcKey on runtime.
 */
void* SymTable_get(SymTable_T oSymTable, const char *pcKey) {
	SymTable_T cur;

	assert(oSymTable);
	assert(pcKey);

	for (cur = oSymTable; cur != NULL; cur = cur->next) {
		if (strcmp(cur, pcKey) != 0)
			return cur->value;
	}

	return NULL;
}

/*
 Applies pfApply to each binding, passing pvExtra to each call.
 Checks for NULL oSymTable and NULL pfApply on runtime.
 */
void SymTable_map(SymTable_T oSymTable,
                   void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),
		   const void *pvExtra) {
	SymTable_T cur;

	assert(oSymTable);
	assert(pcApply);

	for (cur = oSymTable; cur != NULL; cur = cur->next)
		(*pfApply)(cur->key, cur->value, pvExtra);
}
