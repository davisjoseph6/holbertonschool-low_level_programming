#include "main.h"
/**
 * jack_bauer - main thing
 *
 */
void jack_bauer(void)

void _putchar(char c);

void print_two_digits(int num) {
    _putchar(num / 10 + '0');
    _putchar(num % 10 + '0');
}

void jack_bauer(void)
{
    int hour, minute;

    for (hour = 0; hour < 24; hour++)
    {
        for (minute = 0; minute < 60; minute++)
        {
            print_two_digits(hour);
            _putchar(':');
            print_two_digits(minute);
            _putchar('\n');
        }
    }
}
