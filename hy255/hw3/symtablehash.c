#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
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
	unsigned int now;
};

SymTable_T rehash(SymTable_T table);
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
	tmp->siz = HASHSIZ;
	tmp->now = 0;
	tmp->arr = malloc(tmp->siz * sizeof(token *));

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
	return oSymTable->now;
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


	if (tmp == NULL || SymTable_contains(oSymTable, pcKey))
		return 0;

	tmp->key = malloc((strlen(pcKey) + 1) * sizeof(char));

	if (strcpy(tmp->key, pcKey) == NULL)
		return 0;

	tmp->value = (void *) pvValue;
	tmp->next = NULL;

	oSymTable->now++;
	if (oSymTable->now >= oSymTable->siz && oSymTable->siz < 65521) {
		oSymTable = rehash(oSymTable);
		h = tokhash(pcKey, oSymTable->siz);
		printf("1\n");
	}

	/* Append new struct at the end of the table if this isn't the first binding */
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
			oSymTable->now--;

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

	for (i = 0; string[i] != '\0'; i++)
		hash = ((hash << 5) + hash) + string[i];

	return hash % size;
}

/* Rearanges hash table */
SymTable_T rehash(SymTable_T table) {
	unsigned int oldsiz, i, h;
	token *cur, *buff, *prev;

	oldsiz = table->siz;

	if (table->siz < 1021)
		table->siz = 1021;
	else if (table->siz < 2053)
		table->siz = 2053;
	else if (table->siz < 4093)
		table->siz = 4093;
	else if (table->siz < 8191)
		table->siz = 8191;
	else if (table->siz < 16381)
		table->siz = 16381;
	else if (table->siz < 32771)
		table->siz = 32771;
	else if (table->siz < 65521)
		table->siz = 65521;
	else
		return NULL;
	printf("Changed from %d buckets to %d\n", oldsiz, table->siz);

	table->arr = (token **) realloc(table->arr, table->siz * sizeof(token *));
	assert(table->arr);

	for (i = oldsiz; i < table->siz; i++) {
		table->arr[i] = malloc(sizeof(token));
		table->arr[i]->key = NULL;
		table->arr[i]->next = NULL;
	}

	for (i = 0; i < oldsiz; i++) {
		prev = NULL;
		for (cur = table->arr[i]; cur != NULL; cur = cur->next) {
			if (cur->key == NULL)
				continue;

			h = tokhash(cur->key, table->siz);
			if (h == tokhash(cur->key, oldsiz)) {
				prev = cur;
				continue;
			}

			for (buff = table->arr[h]; buff->next != NULL; buff = buff->next);

			if (buff->next != NULL)
				continue;

			if (buff->key == NULL) {
				buff->key = cur->key;
				buff->value = cur->value;
				cur->key = NULL;

				if (prev != NULL)
					prev->next = cur->next;

				if (table->arr[i] != cur)
					tokfree(cur);
			} else if (buff != cur) {
					buff->next = cur;

					if (prev != NULL)
						prev->next = cur->next;
			}
		}
	}

		printf("%d %d\t", i, oldsiz);
	return table;
}
