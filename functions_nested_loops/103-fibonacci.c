#include <stdio.h>

/**
 * main - sums even-valued Fibonacci terms not exceeding 4,000,000
 *
 * Description: Starting from 1 and 2, iterates through Fibonacci numbers,
 * accumulating only the even terms whose values are <= 4000000, then prints
 * the sum followed by a newline.
 *
 * Return: Always 0.
 */
int main(void)
{
	unsigned long int a, b, next, sum;

	a = 1;
	b = 2;
	sum = 0;

	while (b <= 4000000)
	{
		if ((b % 2) == 0)
			sum += b;

		next = a + b;
		a = b;
		b = next;
	}

	printf("%lu\n", sum);
	return (0);
}

