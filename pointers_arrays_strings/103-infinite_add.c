/*
 * File: 103-infinite_add.c
 * Desc: Add two non-negative integer strings into buffer r.
 */

#include "main.h"

/**
 * infinite_add - Adds two non-negative numbers given as strings.
 * @n1: First number string.
 * @n2: Second number string.
 * @r:  Result buffer.
 * @size_r: Size of result buffer.
 *
 * Return: Pointer to result within r, or 0 if it won't fit.
 */
char *infinite_add(char *n1, char *n2, char *r, int size_r)
{
	int i = 0, j = 0, k, carry = 0, d1, d2, sum;

	while (n1[i] != '\0')
		i++;
	while (n2[j] != '\0')
		j++;

	k = size_r - 1;
	if (k < 1) /* need at least space for '\0' */
		return (0);
	r[k] = '\0';
	i--;
	j--;

	while (i >= 0 || j >= 0 || carry)
	{
		if (k == 0)
			return (0);
		d1 = (i >= 0) ? (n1[i] - '0') : 0;
		d2 = (j >= 0) ? (n2[j] - '0') : 0;
		sum = d1 + d2 + carry;
		carry = sum / 10;
		r[--k] = (sum % 10) + '0';
		i--;
		j--;
	}
	return (r + k);
}

