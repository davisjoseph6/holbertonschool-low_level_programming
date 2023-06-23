/*
 * File: 5-more_numbers.c
 * Auth: Davis Joseph
 */

#include "main.h"
#include <stdio.h>


/**
 * more_numbers - Prints the numbers 0-14 ten times.
 */
void more_numbers(void)
{
	int num, count;

	for (count = 0; count <= 9; count++)
	{
		for (num = 0; num <= 14; num++)
		{
			if (num > 9)
				putchar((num / 10) + '0');
			putchar((num % 10) + '0');
		}
		putchar('\n');
	}
}
