#include "main.h"

/**
 *void print_alphabet_x10 to print alphabet 10 times
 *10 x alphabet
 *return: void
 */

void print_alphabet_x10(void)
{
  int num = 0;
  char alpha;

  while (num <= 9)
    {
      for (alpha = 'a'; alpha <= 'z'; alpha++)
	{
	  _putchar(alpha);
	  _putchar('\n');
	}
   num++;
    }
}
