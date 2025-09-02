/* 
 * File: 100-rot13.c
 * Desc: Encode a string using ROT13 without stdlib.
 */

#include "main.h"

/**
 * rot13 - Encodes a string using ROT13.
 * @s: Pointer to the string to encode.
 *
 * Return: Pointer to the modified string.
 */
char *rot13(char *s)
{
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";
	int i = 0, j;

	while (s[i] != '\0')
	{
		for (j = 0; j < 52; j++)
		{
			if (s[i] == in[j])
			{
				s[i] = out[j];
				break;
			}
		}
		i++;
	}
	return (s);
}

