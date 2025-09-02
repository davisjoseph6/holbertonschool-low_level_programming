#include "main.h"
#include <stdlib.h>

/**
 * _strlen - Returns length of a string.
 * @s: String.
 * Return: Length.
 */
int _strlen(char *s)
{
	int n = 0;

	while (s && s[n] != '\0')
		n++;
	return (n);
}

/**
 * is_digits - Checks if a string contains only decimal digits.
 * @s: String.
 * Return: 1 if only digits and not empty, 0 otherwise.
 */
int is_digits(char *s)
{
	int i = 0;

	if (s == NULL || s[0] == '\0')
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

/**
 * print_str - Prints a C-string using _putchar.
 * @s: String to print.
 */
void print_str(char *s)
{
	int i = 0;

	while (s[i] != '\0')
	{
		_putchar(s[i]);
		i++;
	}
}

/**
 * print_error_exit - Prints "Error" and exits with status 98.
 */
void print_error_exit(void)
{
	print_str("Error\n");
	exit(98);
}

/**
 * print_number_array - Prints an array of digit ints as a number.
 * @a: Array of digits (0..9).
 * @len: Length of array.
 */
void print_number_array(int *a, int len)
{
	int i = 0;

	/* Skip leading zeros, but ensure we print at least one digit */
	while (i < (len - 1) && a[i] == 0)
		i++;

	for (; i < len; i++)
		_putchar((char)(a[i] + '0'));
	_putchar('\n');
}

/**
 * main - Multiplies two positive numbers given as strings.
 * @argc: Argument count.
 * @argv: Argument vector.
 *
 * Usage: mul num1 num2
 * Return: 0 on success, exits 98 on any error.
 */
int main(int argc, char *argv[])
{
	char *s1, *s2;
	int len1, len2, size, i, j;
	int *res;

	if (argc != 3)
		print_error_exit();

	s1 = argv[1];
	s2 = argv[2];

	if (!is_digits(s1) || !is_digits(s2))
		print_error_exit();

	len1 = _strlen(s1);
	len2 = _strlen(s2);
	size = len1 + len2;

	res = (int *)malloc(sizeof(int) * size);
	if (res == NULL)
		print_error_exit();

	for (i = 0; i < size; i++)
		res[i] = 0;

	/* Grade-school multiplication from right to left */
	for (i = len1 - 1; i >= 0; i--)
	{
		int d1 = s1[i] - '0';
		int carry = 0;

		for (j = len2 - 1; j >= 0; j--)
		{
			int d2 = s2[j] - '0';
			int pos_low = i + j + 1;
			int sum = d1 * d2 + res[pos_low] + carry;

			res[pos_low] = sum % 10;
			carry = sum / 10;
		}
		res[i + j + 1] += carry; /* here j == -1 */
	}

	print_number_array(res, size);
	free(res);
	return (0);
}

