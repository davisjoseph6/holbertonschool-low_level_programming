/*
 * File: 100-set_string.c
 * Desc: Set the value of a pointer to a char.
 */

#include "main.h"

/**
 * set_string - Sets the value of a pointer to a char.
 * @s: Address of the pointer to set.
 * @to: Char pointer to assign.
 *
 * Return: void.
 */
void set_string(char **s, char *to)
{
	*s = to;
}

