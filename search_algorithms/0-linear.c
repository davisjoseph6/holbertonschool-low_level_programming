#include <stdio.h>
#include "search_algos.h"

/**
 * linear_search - Searches for a value in in an array of integers
 * using the Linear search algorithm
 * @array: a pointer to the first element of the array to search in
 * @size: the number of elements in array
 * @value:  the value to search for
 * Return: If value is not present in array or if array is NULL, 
 * your function must return -1
 * else return 0
 */
int linear_search(int *array, size_t size, int value)
{
	size_t i;

	if (array == NULL)
		return (-1);

	for (i = 0; i < size; i++)
	{
		printf("Value checked array[%lu] = [%d]\n", i, array[i]);
		if (array[i] == value)
			return (i);
	}

	return (-1);
}
