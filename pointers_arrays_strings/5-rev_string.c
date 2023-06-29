#include <stddef.h>  /* Include for NULL definition */
#include "main.h"

/**
 * rev_string - Reverses a string.
 * @s: The string to be reversed.
 */
void rev_string(char *s)
{
    if (s == NULL)
        return;

    char *start = s;
    char *end = s;
    char temp;

    int length = 0;  /* Variable declaration */

    /* Find the length of the string */
    while (*end != '\0') {
        length++;
        end++;
    }

    /* Reverse the string by swapping characters */
    end--;

    while (start < end) {
        temp = *start;
        *start = *end;
        *end = temp;

        start++;
        end--;
    }
}
