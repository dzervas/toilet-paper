#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "symtable.h"

struct SymTable_T {
	char *key;
	void *value;
	SymTable_T next;
};

/*
 Dead simple malloc.
 Returns pointer to new SymTable struct
 */
SymTable_T SymTable_new() {
	SymTable_T tmp;

	tmp = malloc(sizeof(struct SymTable_T));
	tmp->key = NULL;
	tmp->next = NULL;
	return tmp;
}

/*
 Frees allocated SymTable struct.
 If oSymTable is NULL, function does nothing
 */
void SymTable_free(SymTable_T oSymTable) {
	if (oSymTable == NULL)
		return;

	free(oSymTable->key);
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

	for (tmp = oSymTable; tmp != NULL; tmp = tmp->next) {
		if (tmp->key != NULL)
			count++;
	}

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

	if (tmp == NULL || SymTable_contains(oSymTable, pcKey))
		return 0;

	tmp->key = malloc((strlen(pcKey) + 1) * sizeof(char));

	if (strcpy(tmp->key, pcKey) == NULL)
		return 0;

	tmp->value = (void *) pvValue;
	tmp->next = NULL;

	/* Append new struct at the end of the table if this isn't the first binding*/
	if (oSymTable != tmp) {
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

	for (cur = oSymTable; cur != NULL; cur = cur->next) {
		if (cur->key == NULL)
			continue;

		if (strcmp(cur->key, pcKey) == 0) {
			if (cur == oSymTable) {
				free(cur->key);
				cur->key = NULL;
				return 1;
			} else
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
		if (cur->key == NULL)
			continue;

		if (strcmp(cur->key, pcKey) == 0)
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
		if (cur->key == NULL)
			continue;

		if (strcmp(cur->key, pcKey) == 0)
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
	assert(pfApply);

	for (cur = oSymTable; cur != NULL; cur = cur->next)
		(*pfApply)((const char *) cur->key, cur->value, (void *) pvExtra);
}
