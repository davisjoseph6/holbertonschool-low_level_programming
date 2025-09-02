#include "main.h"
#include <stdlib.h>

/**
 * _realloc - Reallocates a memory block using malloc and free.
 * @ptr: Pointer to the previously allocated memory (via malloc(old_size)).
 * @old_size: Size in bytes of the allocated space for @ptr.
 * @new_size: New size in bytes of the new memory block.
 *
 * Return: Pointer to the newly allocated memory, or NULL on failure.
 *
 * Notes:
 * - If new_size == old_size: returns @ptr unchanged.
 * - If ptr == NULL: behaves like malloc(new_size).
 * - If new_size == 0 and ptr != NULL: frees @ptr and returns NULL.
 * - Contents are copied up to the minimum of old_size and new_size.
 * - Added memory (if any) is left uninitialized.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	unsigned int i, limit;
	char *new_ptr, *src, *dst;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	new_ptr = (char *)malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);

	/* Copy the lesser of old_size and new_size bytes */
	src = (char *)ptr;
	dst = new_ptr;
	limit = (old_size < new_size) ? old_size : new_size;

	for (i = 0; i < limit; i++)
		dst[i] = src[i];

	free(ptr);
	return ((void *)new_ptr);
}

