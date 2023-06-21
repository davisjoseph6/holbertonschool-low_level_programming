#include "main.h"

/**
 *void print_alphabet_x10 to print alphabet 10 times
 *10 x alphabet
 *return: void
 */

void print_alphabet_x10(void)
{
  int num = 0;
  char i;

  for (i = 'a'; i <= 'z'; i++)
    {
      _putchar(i);
      for (num = 0; num <= 9; num ++)
	{
	_putchar(num);
        _putchar('\n');
	}
    }
}
