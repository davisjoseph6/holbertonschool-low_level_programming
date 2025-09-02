#include <stdio.h>
#include <stdlib.h>

/**
 * main - Prints the minimum number of coins to make change for an amount.
 * @argc: Argument count.
 * @argv: Argument vector (expects exactly one argument: cents).
 *
 * Return: 0 on success, 1 if incorrect number of arguments.
 *
 * Usage: ./change cents
 * Notes:
 * - Uses atoi to parse the cents.
 * - If cents is negative, prints 0.
 * - Allowed coins: 25, 10, 5, 2, 1 (unlimited supply).
 */
int main(int argc, char *argv[])
{
	int cents, i, count;
	int coins[5] = {25, 10, 5, 2, 1};

	if (argc != 2)
	{
		printf("Error\n");
		return (1);
	}

	cents = atoi(argv[1]);
	if (cents <= 0)
	{
		printf("0\n");
		return (0);
	}

	count = 0;
	for (i = 0; i < 5; i++)
	{
		count += cents / coins[i];
		cents %= coins[i];
	}

	printf("%d\n", count);
	return (0);
}

