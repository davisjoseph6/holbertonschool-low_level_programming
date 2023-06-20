#include "main.h"

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
    char text[] = "_putchar\n";
    int i;

    for (i = 0; text[i] != '\0'; i++)
        _putchar(text[i]);

    return 0;
}

/**
 * _putchar - Writes a character to the standard output (stdout)
 * @c: The character to be written
 *
 * Return: On success 1
 * On error, -1 is returned, and errno is set appropriately
 */
int _putchar(char c)
{
    return (write(1, &c, 1));
}
