#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hash_tables.h"

/* ========= Internal helpers (allowed > 5 functions for this task) ========= */

/**
 * make_shash_node - Allocate and initialize a sorted hash node
 * @key: Key string (must be non-NULL, non-empty)
 * @value: Value string (must be non-NULL)
 *
 * Return: Pointer to node on success, NULL on failure
 */
static shash_node_t *make_shash_node(const char *key, const char *value)
{
	shash_node_t *node;
	char *kdup, *vdup;

	if (key == NULL || *key == '\0' || value == NULL)
		return (NULL);

	node = (shash_node_t *)malloc(sizeof(shash_node_t));
	if (node == NULL)
		return (NULL);

	kdup = strdup(key);
	if (kdup == NULL)
	{
		free(node);
		return (NULL);
	}

	vdup = strdup(value);
	if (vdup == NULL)
	{
		free(kdup);
		free(node);
		return (NULL);
	}

	node->key = kdup;
	node->value = vdup;
	node->next = NULL;
	node->sprev = NULL;
	node->snext = NULL;

	return (node);
}

/**
 * insert_sorted - Insert node into the table's sorted doubly linked list
 * @ht: Sorted hash table
 * @node: Node to insert (not present anywhere yet)
 *
 * Description: Maintains ascending ASCII order by key using strcmp.
 * Return: Nothing
 */
static void insert_sorted(shash_table_t *ht, shash_node_t *node)
{
	shash_node_t *curr;

	if (ht->shead == NULL) /* first element */
	{
		ht->shead = node;
		ht->stail = node;
		return;
	}

	curr = ht->shead;
	while (curr && strcmp(curr->key, node->key) < 0)
		curr = curr->snext;

	if (curr == ht->shead) /* insert at head (node <= first) */
	{
		node->snext = curr;
		node->sprev = NULL;
		curr->sprev = node;
		ht->shead = node;
	}
	else if (curr == NULL) /* insert at tail (node > last) */
	{
		node->sprev = ht->stail;
		ht->stail->snext = node;
		ht->stail = node;
	}
	else /* insert in the middle: ... prev < node <= curr ... */
	{
		node->sprev = curr->sprev;
		node->snext = curr;
		curr->sprev->snext = node;
		curr->sprev = node;
	}
}

/* ========================== Public API functions ========================== */

/**
 * shash_table_create - Create a sorted hash table
 * @size: Array size
 *
 * Return: Pointer to table on success, NULL on failure
 */
shash_table_t *shash_table_create(unsigned long int size)
{
	shash_table_t *ht;
	unsigned long int i;

	if (size == 0)
		return (NULL);

	ht = (shash_table_t *)malloc(sizeof(shash_table_t));
	if (ht == NULL)
		return (NULL);

	ht->size = size;
	ht->array = (shash_node_t **)calloc(size, sizeof(shash_node_t *));
	if (ht->array == NULL)
	{
		free(ht);
		return (NULL);
	}

	for (i = 0; i < size; i++)
		ht->array[i] = NULL;

	ht->shead = NULL;
	ht->stail = NULL;

	return (ht);
}

/**
 * shash_table_set - Add or update an element in a sorted hash table
 * @ht: Sorted hash table
 * @key: Key (non-NULL, not empty)
 * @value: Value (non-NULL)
 *
 * Return: 1 on success, 0 on failure
 *
 * Description:
 * - If key already exists, replace its value (keep position in sorted list).
 * - Otherwise, insert into bucket chain (head) and into sorted list by key.
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
	unsigned long int idx;
	shash_node_t *node, *head, *iter;
	char *vdup;

	if (ht == NULL || key == NULL || *key == '\0' || value == NULL)
		return (0);

	idx = key_index((const unsigned char *)key, ht->size);
	head = ht->array[idx];
	iter = head;

	/* Update if key exists in this bucket */
	while (iter != NULL)
	{
		if (strcmp(iter->key, key) == 0)
		{
			vdup = strdup(value);
			if (vdup == NULL)
				return (0);
			free(iter->value);
			iter->value = vdup;
			return (1);
		}
		iter = iter->next;
	}

	/* Not found: create new node */
	node = make_shash_node(key, value);
	if (node == NULL)
		return (0);

	/* Insert into bucket chain (head insertion) */
	node->next = head;
	ht->array[idx] = node;

	/* Insert into sorted doubly linked list */
	insert_sorted(ht, node);

	return (1);
}

/**
 * shash_table_get - Retrieve a value by key from a sorted hash table
 * @ht: Sorted hash table
 * @key: Key to find
 *
 * Return: Value string if found, or NULL
 */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
	unsigned long int idx;
	shash_node_t *node;

	if (ht == NULL || key == NULL || *key == '\0')
		return (NULL);

	idx = key_index((const unsigned char *)key, ht->size);
	node = ht->array[idx];

	while (node != NULL)
	{
		if (strcmp(node->key, key) == 0)
			return (node->value);
		node = node->next;
	}

	return (NULL);
}

/**
 * shash_table_print - Print the table in sorted key order
 * @ht: Sorted hash table
 *
 * Return: Nothing
 */
void shash_table_print(const shash_table_t *ht)
{
	shash_node_t *node;
	int printed;

	if (ht == NULL)
		return;

	printf("{");
	printed = 0;
	node = ht->shead;

	while (node != NULL)
	{
		if (printed)
			printf(", ");
		printf("'%s': '%s'", node->key, node->value);
		printed = 1;
		node = node->snext;
	}
	printf("}\n");
}

/**
 * shash_table_print_rev - Print the table in reverse sorted key order
 * @ht: Sorted hash table
 *
 * Return: Nothing
 */
void shash_table_print_rev(const shash_table_t *ht)
{
	shash_node_t *node;
	int printed;

	if (ht == NULL)
		return;

	printf("{");
	printed = 0;
	node = ht->stail;

	while (node != NULL)
	{
		if (printed)
			printf(", ");
		printf("'%s': '%s'", node->key, node->value);
		printed = 1;
		node = node->sprev;
	}
	printf("}\n");
}

/**
 * shash_table_delete - Free all memory used by a sorted hash table
 * @ht: Sorted hash table
 *
 * Return: Nothing
 *
 * Description: Frees nodes by walking the sorted list (each node once),
 * then frees the bucket array and the table itself.
 */
void shash_table_delete(shash_table_t *ht)
{
	shash_node_t *node, *tmp;

	if (ht == NULL)
		return;

	node = ht->shead;
	while (node != NULL)
	{
		tmp = node->snext;
		free(node->key);
		free(node->value);
		free(node);
		node = tmp;
	}

	free(ht->array);
	free(ht);
}

