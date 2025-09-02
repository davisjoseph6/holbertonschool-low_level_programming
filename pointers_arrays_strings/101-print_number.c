/*
 * File: 101-print_number.c
 * Desc: Print an integer using only _putchar (handles INT_MIN safely).
 */

#include "main.h"

/**
 * print_number - Prints an integer using only _putchar.
 * @n: The integer to print.
 *
 * Return: void.
 */
void print_number(int n)
{
	unsigned int m;

	/* If negative, print sign and convert to unsigned magnitude safely */
	if (n < 0)
	{
		_putchar('-');
		/* Cast to unsigned first, then negate in unsigned to avoid UB on INT_MIN */
		m = (unsigned int)n;
		m = (unsigned int)(-m);
	}
	else
	{
		m = (unsigned int)n;
	}

	/* Print higher-order digits first (recursively) */
	if (m / 10)
		print_number((int)(m / 10));

	/* Print last digit */
	_putchar((char)('0' + (m % 10)));
}

