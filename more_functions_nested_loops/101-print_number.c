#include "main.h"

/**
 * print_number - Prints an integer using only _putchar
 * @n: The integer to print
 *
 * Description: No long, no arrays/pointers. Handles negatives (incl. INT_MIN)
 * using unsigned arithmetic. Works under GNU89.
 */
void print_number(int n)
{
	unsigned int num, div;

	if (n < 0)
	{
		_putchar('-');
		num = (unsigned int)(- (unsigned int)n);
	}
	else
	{
		num = (unsigned int)n;
	}

	div = 1U;
	while (num / div >= 10U)
		div *= 10U;

	while (div != 0U)
	{
		_putchar('0' + (num / div));
		num %= div;
		div /= 10U;
	}
}

