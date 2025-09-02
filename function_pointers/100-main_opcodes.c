#include <stdio.h>
#include <stdlib.h>

/**
 * main - Prints the opcodes of its own main function.
 * @argc: Argument count.
 * @argv: Argument vector. Expects argv[1] = number of bytes.
 *
 * Usage: ./main number_of_bytes
 * Return: 0 on success; exits with 1 or 2 on specified errors.
 */
int main(int argc, char **argv)
{
	int n, i;
	unsigned char *p;
	int (*fptr)(int, char **) = main;

	if (argc != 2)
	{
		printf("Error\n");
		exit(1);
	}

	n = atoi(argv[1]);
	if (n < 0)
	{
		printf("Error\n");
		exit(2);
	}

	p = (unsigned char *)((void *)fptr);

	for (i = 0; i < n; i++)
	{
		printf("%02x", p[i]);
		if (i == n - 1)
			printf("\n");
		else
			printf(" ");
	}

	return (0);
}

