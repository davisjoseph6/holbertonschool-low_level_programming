#include "main.h"

/**
 * skip_stars - Recursively advances over consecutive '*' characters.
 * @p: Pattern pointer positioned at a '*'.
 *
 * Return: Pointer to the last '*' in a consecutive run (or @p if single '*').
 */
char *skip_stars(char *p)
{
	if (p && *p == '*' && *(p + 1) == '*')
		return (skip_stars(p + 1));
	return (p);
}

/**
 * wildcmp - Compares two strings where s2 may contain the wildcard '*'.
 * @s1: String to test.
 * @s2: Pattern that may include '*' (matches any string, even empty).
 *
 * Return: 1 if the strings can be considered identical, otherwise 0.
 */
int wildcmp(char *s1, char *s2)
{
	if (*s2 == '\0')
		return (*s1 == '\0');

	if (*s2 == '*')
	{
		s2 = skip_stars(s2);
		if (*(s2 + 1) == '\0')
			return (1); /* trailing '*' matches rest of s1 */
		if (*s1 == '\0')
			return (wildcmp(s1, s2 + 1)); /* '*' matches empty only */
		/* Try: '*' matches empty OR consumes one char from s1 */
		if (wildcmp(s1, s2 + 1))
			return (1);
		return (wildcmp(s1 + 1, s2));
	}

	if (*s1 == '\0')
		return (0);

	if (*s1 == *s2)
		return (wildcmp(s1 + 1, s2 + 1));

	return (0);
}

