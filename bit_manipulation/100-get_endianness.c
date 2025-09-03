/* 100-get_endianness.c */
#include "main.h"

/**
 * get_endianness - Checks the endianness of the machine.
 *
 * Return: 1 if little endian, 0 if big endian.
 */
int get_endianness(void)
{
	unsigned int x = 1;
	char *b = (char *)&x;

	return ((int)(*b));
}

