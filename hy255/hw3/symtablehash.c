#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "symtable.h"

#define HASHSIZ 509
#define ARR oSymTable->arr

typedef struct token token;
struct token {
	char *key;
	void *value;
	token *next;
};

struct SymTable_T {
	token **arr;
	unsigned int siz;
};

void tokfree(token *list);
unsigned int tokhash(const char *string, unsigned int size);

/*
 Dead simple malloc.
 Returns pointer to new SymTable struct
 */
SymTable_T SymTable_new() {
	SymTable_T tmp;
	int i;

	tmp = malloc(sizeof(struct SymTable_T));
	tmp->arr = malloc(HASHSIZ * sizeof(token *));
	tmp->siz = HASHSIZ;

	for (i = 0; i < tmp->siz; i++) {
		tmp->arr[i] = malloc(sizeof(token));
		tmp->arr[i]->key = NULL;
		tmp->arr[i]->next = NULL;
	}

	return tmp;
}

/*
 Frees allocated symbol hash table.
 If oSymTable is NULL, function does nothing
 */
void SymTable_free(SymTable_T oSymTable) {
	int i;

	for (i = 0; i < oSymTable->siz; i++)
		tokfree(ARR[i]);

	free(ARR);
	free(oSymTable);
}

/*
 Returns symbol table length.
 Checks for NULL oSymTable on runtime.
 */
unsigned int SymTable_getLength(SymTable_T oSymTable) {
	token *tmp;
	unsigned int count = 0, i;

	assert(oSymTable);

	for (i = 0; i < oSymTable->siz; i++) {
		for (tmp = ARR[i]; tmp != NULL; tmp = tmp->next) {
			if (tmp->key != NULL)
				count++;
		}
	}

	return count;
}

/*
 Adds binding (with pcKey key and pvValue value) in oSymTable symbol table.
 Returns 1 (TRUE) on success and 0 (FALSE) on error.
 Checks for NULL oSymTable and NULL pcKey on runtime.
 */
int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue) {
	token *buff, *tmp;
	unsigned int h;

	assert(oSymTable);
	assert(pcKey);

	h = tokhash(pcKey, oSymTable->siz);

	if (ARR[h]->key == NULL)
		tmp = ARR[h];
	else
		tmp = malloc(sizeof(token));


	if (tmp == NULL)
		return 0;

	tmp->key = malloc((strlen(pcKey) + 1) * sizeof(char));

	if (strcpy(tmp->key, pcKey) == NULL)
		return 0;

	tmp->value = (void *) pvValue;
	tmp->next = NULL;

	/* Append new struct at the end of the table if this isn't the first binding*/
	if (ARR[h] != tmp) {
		for (buff = ARR[h]; buff->next != NULL; buff = buff->next);
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
	token *prev = NULL, *cur;
	unsigned int h;

	assert(oSymTable);
	assert(pcKey);

	h = tokhash(pcKey, oSymTable->siz);

	for (cur = ARR[h]; cur != NULL; cur = cur->next) {
		if (cur->key == NULL)
			continue;

		if (strcmp(cur->key, pcKey) == 0) {
			if (cur == ARR[h]) {
				free(cur->key);
				cur->key = NULL;
				return 1;
			} else
				prev->next = cur->next;

			/* NULL the next in current to be able to free only the
				this struct, and not the rest list */
			cur->next = NULL;
			tokfree(cur);
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
	token *cur;
	unsigned int h;

	assert(oSymTable);
	assert(pcKey);

	h = tokhash(pcKey, oSymTable->siz);

	for (cur = ARR[h]; cur != NULL; cur = cur->next) {
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
	token *cur;
	unsigned int h;

	assert(oSymTable);
	assert(pcKey);

	h = tokhash(pcKey, oSymTable->siz);

	for (cur = ARR[h]; cur != NULL; cur = cur->next) {
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
	token *cur;
	unsigned int i;

	assert(oSymTable);
	assert(pfApply);

	for (i = 0; i < oSymTable->siz; i++) {
		for (cur = ARR[i]; cur != NULL; cur = cur->next)
			(*pfApply)((const char *) cur->key, cur->value, (void *) pvExtra);
	}
}

/*
 Frees allocated token struct.
 If token is NULL, function does nothing
 */
void tokfree(token *list) {
	if (list == NULL)
		return;

	free(list->key);
	tokfree(list->next);
	free(list);
}

/*
 Returns hash address of string
 */
unsigned int tokhash(const char *string, unsigned int size) {
	unsigned int hash = 5381, i;

	for (i = 0; string[i]!='\0'; i++){
		hash= ((hash << 5) + hash) + string[i];
	}

	return hash % size;
}
