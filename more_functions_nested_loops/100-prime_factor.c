#include <stdio.h>

/**
 * main - Prints the largest prime factor of 612852475143
 *
 * Return: 0 on success
 */
int main(void)
{
	unsigned long n = 612852475143UL;
	unsigned long largest = 0UL;
	unsigned long i;

	/* Strip factors of 2 */
	while (n % 2UL == 0UL)
	{
		largest = 2UL;
		n /= 2UL;
	}

	/* Check odd factors; use i <= n / i to avoid i*i overflow */
	for (i = 3UL; i <= n / i; i += 2UL)
	{
		while (n % i == 0UL)
		{
			largest = i;
			n /= i;
		}
	}

	if (n > 1UL)
		largest = n;

	printf("%lu\n", largest);
	return (0);
}

