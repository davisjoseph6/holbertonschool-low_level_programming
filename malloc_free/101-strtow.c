#include "main.h"
#include <stdlib.h>

/**
 * word_count - Counts words separated by single spaces.
 * @str: Input string.
 *
 * Return: Number of words (0 if none or str is NULL).
 */
int word_count(char *str)
{
	int i = 0, in_word = 0, count = 0;

	if (str == NULL)
		return (0);

	while (str[i] != '\0')
	{
		if (str[i] != ' ' && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (str[i] == ' ')
		{
			in_word = 0;
		}
		i++;
	}
	return (count);
}

/**
 * free_words - Frees a partially built array of strings.
 * @arr: Array of strings to free.
 * @n:   Number of allocated strings inside arr.
 */
void free_words(char **arr, int n)
{
	int i;

	for (i = 0; i < n; i++)
		free(arr[i]);
	free(arr);
}

/**
 * strtow - Splits a string into words (space-delimited).
 * @str: String to split. Words are separated by spaces.
 *
 * Return: Pointer to an array of strings (each word null-terminated),
 *         last element is NULL; or NULL if str is NULL/"" or on failure.
 */
char **strtow(char *str)
{
	int words, i = 0, idx = 0, start, end, len, j;
	char **tab;

	if (str == NULL || *str == '\0')
		return (NULL);

	words = word_count(str);
	if (words == 0)
		return (NULL);

	tab = (char **)malloc(sizeof(char *) * (words + 1));
	if (tab == NULL)
		return (NULL);

	while (str[i] != '\0')
	{
		while (str[i] == ' ')
			i++;
		if (str[i] == '\0')
			break;

		start = i;
		while (str[i] != '\0' && str[i] != ' ')
			i++;
		end = i;

		len = end - start;
		tab[idx] = (char *)malloc(sizeof(char) * (len + 1));
		if (tab[idx] == NULL)
		{
			free_words(tab, idx);
			return (NULL);
		}

		for (j = 0; j < len; j++)
			tab[idx][j] = str[start + j];
		tab[idx][len] = '\0';
		idx++;
	}
	tab[idx] = NULL;

	return (tab);
}

