#include "shell.h"

/**
 * _intlen - print strings
 * @num: - char to sperate ints
 * @base: - char to sperate ints
 * Return: int
 */
int _intlen(long int num, int base)
{
	int i;

	for (i = 0; num != 0; i++)
		num /= base;
	return (i > 0 ? i : 1);
}

/**
 * int_to_str - print strings
 * @num: - char to sperate ints
 * @new_num: - char to sperate ints
 * @len: - char to sperate ints
 * @sign: - char to sperate ints
 */
void int_to_str(long int num, char *new_num, int len, int sign)
{
	int i;

	if (sign == 1)
		new_num[0] = num < 0 ? '-' : '+';
	if (num < 0)
		num *= -1;
	for (i = len - 1; i >= sign; i--)
	{
		new_num[i] = (num % 10) + '0';
		num /= 10;
	}
}


/**
 * _getenvIndex - malloc err handler
 * @name: char
 * Return: int
 */
int _getenvIndex(char *name)
{
	int i, name_len;

	name_len = _strlen(name);
	for (i = 0; environ[i] != NULL && environ[i][1] != '\0'; i++)
		if (nonexact_strcmp(name, environ[i]) == 0 && environ[i][name_len] == '=')
			return (i);
	return (-1);
}
