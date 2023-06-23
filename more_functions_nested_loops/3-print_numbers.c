/*
0;10;1c * File: 3-print_numbers.c
 * Auth: Davis Joseph
 */

#include "main.h"

/**
  * print_numbers - Print the numbers since 0 up to 9
  *
  * Return: The numbers since 0 up to 9
  */
void print_numbers(void)
{
	int x;

	for (x = 0; x <= 9; x++)
	{
		putchar(x + '0');
	}

	_putchar('\n');
}
