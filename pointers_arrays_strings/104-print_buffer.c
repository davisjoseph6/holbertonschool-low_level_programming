/*
 * File: 104-print_buffer.c
 * Desc: Print the content of a buffer in hex + ASCII, 10 bytes per line.
 */

#include "main.h"
#include <stdio.h>

/**
 * print_buffer - Prints size bytes from buffer b as hex and ASCII.
 * @b:    Pointer to buffer.
 * @size: Number of bytes to print.
 *
 * Return: void.
 */
void print_buffer(char *b, int size)
{
	int off, i, j;

	if (size <= 0)
	{
		printf("\n");
		return;
	}

	for (off = 0; off < size; off += 10)
	{
		printf("%08x: ", off);

		/* hex area: 5 groups, each group is 2 bytes (4 hex chars) */
		for (j = 0; j < 5; j++)
		{
			int idx = off + j * 2;

			if (idx < size)
				printf("%02x", (unsigned char)b[idx]);
			else
				printf("  ");
			if (idx + 1 < size)
				printf("%02x", (unsigned char)b[idx + 1]);
			else
				printf("  ");

			if (j < 4)
				printf(" ");
		}

		/* ASCII area: printable chars or '.' */
		for (i = 0; i < 10 && (off + i) < size; i++)
		{
			unsigned char c = (unsigned char)b[off + i];

			if (c >= 32 && c <= 126)
				printf("%c", c);
			else
				printf(".");
		}
		printf("\n");
	}
}

