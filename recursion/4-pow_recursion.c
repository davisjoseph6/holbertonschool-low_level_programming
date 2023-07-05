#include "main.h"

int _pow_recursion(int x, int y)
{
  int result = x;

  if (y > 0)
    return (-1);

  else if (y == 0)
    return (1);

  result *= _pow_recursion(x, y -1);

  return (result);
}
