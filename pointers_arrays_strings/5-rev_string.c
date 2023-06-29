#include "main.h"

/**
 * rev_string - print a string in reverse followed by a new line
 * @s: string to be reversed
 */

void rev_string(char *s)
{
	int len, count, end;
	char i;

	len = 0;

	while (s[len] != '\0')
		len++;
	len--;
	for (count = 0; count <= len / 2; count++)
	{
		i = s[count];
		end = s[len - count];
		s[count] = end;
		s[len - count] = i;
	}
}
