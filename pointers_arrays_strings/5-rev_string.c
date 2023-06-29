#include <stdio.h>

void rev_string(char *s)
{
    if (s == NULL)
        return;

    int length = 0;
    char *end = s;
    char temp;

    /* Find the length of the string */
    while (*end != '\0') {
        length++;
        end++;
    }

    /* Reverse the string by swapping characters */
    end--;
    while (s < end) {
        temp = *s;
        *s = *end;
        *end = temp;
        s++;
        end--;
    }
}

int main(void)
{
    char s[10] = "My School";

    printf("%s\n", s);
    rev_string(s);
    printf("%s\n", s);
    return 0;
}
