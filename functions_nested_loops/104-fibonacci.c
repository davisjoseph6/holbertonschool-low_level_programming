#include <stdio.h>

/**
 * main - prints the first 98 Fibonacci numbers, starting with 1 and 2
 *
 * Description: Numbers are separated by ", " and followed by a newline.
 * Uses two-part arithmetic (hi/lo with base 10^9) to avoid overflow
 * while respecting the constraint of not using long long or GMP.
 *
 * Return: Always 0.
 */
int main(void)
{
	unsigned long a_hi, a_lo, b_hi, b_lo;
	unsigned long n_hi, n_lo, carry;
	int i;

	/* Start with 1 and 2 */
	a_hi = 0;
	a_lo = 1;
	b_hi = 0;
	b_lo = 2;

	printf("%lu, %lu", a_lo, b_lo);

	for (i = 3; i <= 98; i++)
	{
		/* next = a + b, split into hi/lo using base 10^9 */
		n_lo = a_lo + b_lo;
		carry = n_lo / 1000000000UL;
		n_lo = n_lo % 1000000000UL;
		n_hi = a_hi + b_hi + carry;

		if (n_hi != 0)
			printf(", %lu%09lu", n_hi, n_lo);
		else
			printf(", %lu", n_lo);

		/* shift: a <- b, b <- next */
		a_hi = b_hi;
		a_lo = b_lo;
		b_hi = n_hi;
		b_lo = n_lo;
	}

	printf("\n");
	return (0);
}

