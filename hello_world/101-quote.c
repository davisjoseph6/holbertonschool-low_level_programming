/*
 * File: 101-quote.c
 * Auth: Davis Joseph
 */

#include <unistd.h>

/**
 * main - Prints a specific quote to standard error.
 *
 * Return: Always 1.
 */
int main(void)
{
	const char msg[] =
		"and that piece of art is useful\" - Dora Korpar, 2015-10-19\n";

	write(2, msg, sizeof(msg) - 1);
	return (1);
}

