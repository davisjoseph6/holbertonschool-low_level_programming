#include "main.h"
#include <stdlib.h>

/**
 * argstostr - Concatenates all program arguments into a new string.
 * @ac: Argument count.
 * @av: Argument vector.
 *
 * Return: Pointer to newly allocated string with each argument followed by '\n',
 *         or NULL if ac == 0, av == NULL, or allocation fails.
 */
char *argstostr(int ac, char **av)
{
	int i, j, k, total;
	char *s;

	if (ac == 0 || av == NULL)
		return (NULL);

	total = 0;
	for (i = 0; i < ac; i++)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			total++;
			j++;
		}
	}
	/* + ac for '\n' after each arg, + 1 for final '\0' */
	s = (char *)malloc((total + ac + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);

	k = 0;
	for (i = 0; i < ac; i++)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			s[k++] = av[i][j];
			j++;
		}
		s[k++] = '\n';
	}
	s[k] = '\0';

	return (s);
}

