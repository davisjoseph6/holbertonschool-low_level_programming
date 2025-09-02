#include <stdio.h>

/**
 * main - computes and prints the sum of all multiples of 3 or 5 below 1024
 *
 * Description: Iterates from 0 to 1023 (excluded 1024) and accumulates
 * all numbers divisible by 3 or 5, then prints the sum followed by a
 * newline.
 *
 * Return: Always 0.
 */
int main(void)
{
	int i;
	int sum;

	sum = 0;
	for (i = 0; i < 1024; i++)
	{
		if ((i % 3 == 0) || (i % 5 == 0))
			sum += i;
	}
	printf("%d\n", sum);
	return (0);
}

