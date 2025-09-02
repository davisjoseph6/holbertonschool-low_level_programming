#include "main.h"

/**
 * pal_strlen - Recursively computes the length of a string.
 * @s: Pointer to a null-terminated string (may be NULL).
 *
 * Return: Length of @s; 0 if @s is NULL or empty.
 */
int pal_strlen(const char *s)
{
	if (s == 0 || *s == '\0')
		return (0);
	return (1 + pal_strlen(s + 1));
}

/**
 * pal_check - Recursively checks if a string is a palindrome.
 * @s: Pointer to string (assumed non-NULL when called).
 * @l: Left index.
 * @r: Right index.
 *
 * Return: 1 if palindrome in the range [l, r], otherwise 0.
 */
int pal_check(const char *s, int l, int r)
{
	if (l >= r)
		return (1);
	if (s[l] != s[r])
		return (0);
	return (pal_check(s, l + 1, r - 1));
}

/**
 * is_palindrome - Returns 1 if a string is a palindrome, 0 if not.
 * @s: Pointer to string. An empty string is a palindrome.
 *
 * Return: 1 if @s is a palindrome, otherwise 0.
 */
int is_palindrome(char *s)
{
	int len;

	if (s == 0)
		return (1);
	len = pal_strlen(s);
	return (pal_check(s, 0, len - 1));
}

