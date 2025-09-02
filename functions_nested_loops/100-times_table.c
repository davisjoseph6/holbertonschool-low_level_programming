#include "main.h"

/**
 * print_times_table - prints the n times table, starting with 0
 * @n: table size (must be between 0 and 15 inclusive)
 *
 * Description: Prints rows and columns from 0 to n. If n is outside
 * the range [0, 15], the function prints nothing.
 */
void print_times_table(int n)
{
	int i, j, p;

	if (n < 0 || n > 15)
		return;

	for (i = 0; i <= n; i++)
	{
		for (j = 0; j <= n; j++)
		{
			p = i * j;

			if (j == 0)
			{
				_putchar('0');
			}
			else
			{
				_putchar(',');
				_putchar(' ');
				if (p < 10)
				{
					_putchar(' ');
					_putchar(' ');
					_putchar(p + '0');
				}
				else if (p < 100)
				{
					_putchar(' ');
					_putchar((p / 10) + '0');
					_putchar((p % 10) + '0');
				}
				else
				{
					_putchar((p / 100) + '0');
					_putchar(((p / 10) % 10) + '0');
					_putchar((p % 10) + '0');
				}
			}
		}
		_putchar('\n');
	}
}

