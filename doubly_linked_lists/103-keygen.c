#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * main - key generator for crackme5
 * @argc: number of arguments
 * @argv: argument vector (expects username as argv[1])
 *
 * Return: 0 on success, 1 on usage error
 *
 * Usage: ./keygen5 username
 * Prints the key (no newline).
 */
int main(int argc, char *argv[])
{
	char *user;
	char key[7];
	const char *cs = "A-CHRDw87lNS0E9B2TibgpnMJefF36";
	size_t len;
	unsigned long tmp;
	size_t i;

	if (argc != 2)
	{
		printf("Usage: %s username\n", argv[0]);
		return (1);
	}

	user = argv[1];
	len = strlen(user);

	/* key[0] */
	key[0] = cs[(len ^ 59UL) & 63UL];

	/* key[1] */
	tmp = 0UL;
	for (i = 0; i < len; i++)
		tmp += (unsigned char)user[i];
	key[1] = cs[(tmp ^ 79UL) & 63UL];

	/* key[2] */
	tmp = 1UL;
	for (i = 0; i < len; i++)
		tmp *= (unsigned char)user[i];
	key[2] = cs[(tmp ^ 85UL) & 63UL];

	/* key[3] */
	tmp = 0UL;
	for (i = 0; i < len; i++)
		if ((unsigned char)user[i] > (unsigned char)tmp)
			tmp = (unsigned char)user[i];
	srand((unsigned int)((tmp ^ 14UL) & 0xFFFFFFFFUL));
	key[3] = cs[rand() & 63];

	/* key[4] */
	tmp = 0UL;
	for (i = 0; i < len; i++)
	{
		unsigned long c = (unsigned char)user[i];
		tmp += c * c;
	}
	key[4] = cs[(tmp ^ 239UL) & 63UL];

	/* key[5] */
	for (i = 0, tmp = 0UL; i < (size_t)(unsigned char)user[0]; i++)
		tmp = (unsigned long)rand();
	key[5] = cs[(tmp ^ 229UL) & 63UL];

	key[6] = '\0';
	printf("%s", key);
	return (0);
}

