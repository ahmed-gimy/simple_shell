#include "shell.h"


/**
 * _strlen - len of str
 * @s: str
 * Return: len
 */
int _strlen(char *s)
{
	int len;

	for (len = 0; s && s[len] != '\0';)
		len++;
	return (len);
}

/**
 * str_append - take from to and start point
 * @from: to take from
 * @to: to copy to
 * @start: the starting position
 */
void str_append(char *from, char *to, int start)
{
	int i, l;

	for (i = start, l = 0; from[l] != '\0'; i++, l++)
		to[i] = from[l];
	to[i] = '\0';
}

/**
 * _strcmp - take from to and start point
 * @s1: to take from
 * @s2: to copy to
 * Return: 0 if identical
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] != '\0' || s2[i] != '\0'; i++)
		if (s1[i] != s2[i])
			return (1);
	return (0);
}

/**
 * nonexact_strcmp - take from to and start point
 * @s1: to take from
 * @s2: to copy to
 * Return: 0 if identical
 */
int nonexact_strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] != '\0' && s2[i] != '\0'; i++)
		if (s1[i] != s2[i])
			return (1);
	return (0);
}

/**
 * contains - take from to and start point
 * @s: str
 * @c: char
 * Return: 0 if exist
 */
int contains(char *s, char c)
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
		if (s[i] == c)
			return (0);
	return (1);
}
