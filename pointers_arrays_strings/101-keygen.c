/*
 * File: 101-keygen.c
 * Description: Generate a random valid password for the 101-crackme binary.
 * The crackme accepts passwords whose ASCII sum equals 2772.
 *
 * Strategy:
 *  - Randomly pick printable ASCII chars (33..126) until sum >= 2772.
 *  - If we overshoot, reduce one/two characters by the excess while
 *    keeping them printable; then fine-tune by ±1 if needed.
 *
 * Allowed: standard library (srand, rand, time, printf)
 * Build: gcc -Wall -Werror -Wextra -pedantic -std=gnu89 101-keygen.c -o 101-keygen
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * main - Entry point. Prints a valid random key to stdout.
 * Return: 0 on success.
 */
int main(void)
{
	char pwd[128];
	int i = 0;
	int sum = 0;
	int c;
	int excess, d1, d2;
	int k;

	srand((unsigned int)time(NULL));

	/* Fill with random printable chars until sum >= 2772 */
	while (sum < 2772 && i < (int)(sizeof(pwd) - 1))
	{
		c = (rand() % 94) + 33; /* printable ASCII: 33..126 */
		pwd[i++] = (char)c;
		sum += c;
	}
	pwd[i] = '\0';

	if (sum != 2772)
	{
		excess = sum - 2772;

		/* If we overshot, try to absorb excess across up to two chars */
		if (excess > 0)
		{
			d1 = excess / 2;
			d2 = excess - d1;

			/* First adjustment */
			for (k = 0; k < i && d1 > 0; k++)
			{
				if ((pwd[k] - d1) >= 33)
				{
					pwd[k] = (char)(pwd[k] - d1);
					sum -= d1;
					d1 = 0;
				}
			}
			/* Second adjustment */
			for (k = 0; k < i && d2 > 0; k++)
			{
				if ((pwd[k] - d2) >= 33)
				{
					pwd[k] = (char)(pwd[k] - d2);
					sum -= d2;
					d2 = 0;
				}
			}
		}

		/* Safety net: tweak by ±1 while keeping chars printable */
		while (sum > 2772)
		{
			for (k = 0; k < i && sum > 2772; k++)
			{
				if (pwd[k] > 33)
				{
					pwd[k]--;
					sum--;
				}
			}
		}
		while (sum < 2772)
		{
			for (k = 0; k < i && sum < 2772; k++)
			{
				if (pwd[k] < 126)
				{
					pwd[k]++;
					sum++;
				}
			}
		}
	}

	printf("%s", pwd);
	return (0);
}

