/*
 * File: 101-keygen.c
 * Description: Generate a random valid password for the 101-crackme binary.
 * The crackme accepts passwords whose ASCII sum equals 2772.
 * Strategy:
 *   - Randomly pick printable ASCII characters (33..126) until we reach/exceed 2772.
 *   - If we overshoot, redistribute the excess by decreasing one or two characters
 *     while keeping them printable, so the final sum is exactly 2772.
 *
 * Allowed: standard library (srand, rand, time, printf/putchar)
 * Build: gcc -Wall -Werror -Wextra -pedantic 101-keygen.c -o 101-keygen
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * main - Entry point. Prints a valid random key to stdout.
 *
 * Return: 0 on success.
 */
int main(void)
{
	char pwd[128];          /* 84 is the theoretical max count (2772/33), 128 is safe */
	int i = 0, sum = 0;
	int excess, d1, d2;

	srand((unsigned int)time(NULL));

	/* Fill with random printable chars until we reach or exceed 2772 */
	while (sum < 2772 && i < (int)(sizeof(pwd) - 1))
	{
		int c = (rand() % 94) + 33; /* printable ASCII: 33..126 */
		pwd[i++] = (char)c;
		sum += c;
	}

	pwd[i] = '\0';

	/* If we overshot, bring the sum back down while keeping chars printable */
	if (sum != 2772)
	{
		excess = sum - 2772;

		/*
		 * Split the excess across up to two characters so each adjustment
		 * stays within the printable range.
		 */
		d1 = excess / 2;
		d2 = excess - d1;

		/* Decrease first character that can absorb d1 */
		for (int k = 0; k < i && d1 > 0; k++)
		{
			if ((pwd[k] - d1) >= 33)
			{
				pwd[k] = (char)(pwd[k] - d1);
				sum -= d1;
				d1 = 0;
				break;
			}
		}

		/* Decrease first (possibly same or next) character that can absorb d2 */
		for (int k = 0; k < i && d2 > 0; k++)
		{
			if ((pwd[k] - d2) >= 33)
			{
				pwd[k] = (char)(pwd[k] - d2);
				sum -= d2;
				d2 = 0;
				break;
			}
		}

		/*
		 * As a safety net (shouldn’t trigger with the above logic),
		 * if sum still isn't 2772, tweak single characters by ±1 as needed.
		 */
		while (sum > 2772)
		{
			for (int k = 0; k < i && sum > 2772; k++)
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
			for (int k = 0; k < i && sum < 2772; k++)
			{
				if (pwd[k] < 126)
				{
					pwd[k]++;
					sum++;
				}
			}
		}
	}

	/* Print the key (no trailing newline required, but harmless if present) */
	printf("%s", pwd);
	return (0);
}

