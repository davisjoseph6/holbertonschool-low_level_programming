#include <stdio.h>

/**
 * tortoise - Prints two lines before main executes.
 */
void __attribute__ ((constructor)) tortoise(void)
{
	printf("You're beat! and yet, you must allow,\n");
	printf("I bore my house upon my back!\n");
}

