#include "shell.h"

/**
 * str_to_int - handle signals
 * @s: str
 * Return: int
 */
int str_to_int(char *s)
{
	int result, sign, i;

	result = 0, sign = 1, i = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (s[i] == '-')
		sign = -1, i++;
	while (s[i] != '\0')
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1);
		result *= 10;
		result += s[i] - '0';
		i++;
	}
	return (result * sign);
}

/**
 * count_words - get words count
 * @s: str
 * Return: int
 */
int count_words(char *s)
	{
	int count, in_word, i;

	in_word = 0, count = 0, i = 0;
	for (i = 0; s[i] != '\0' && s[i] != '\n'; i++)
	{
		if (s[i] == ' ' || s[i] == '\t')
		{
			if (in_word)
			count++;
			in_word = 0;
		}
		else
			in_word = 1;
	}
	if (in_word)
		count++;
	return (count);
}

/**
 * remove_char - get words count
 * @buff: str
 * @index: int
 */
void remove_char(char *buff, int index)
{
	int i;

	for (i = 0; buff[i] != '\0'; i++)
		if (i >= index)
			buff[i] = buff[i + 1];
}

/**
 * cp_line - get words count
 * @buff: str
 * @line: char
 * Return: int
 */
int cp_line(char *buff, char *line)
{
	int i, q, dq;

	q = 0, dq = 0;
	for (i = 0; (buff[i] != '\n' || q + dq != 0) && buff[i] != '\0'; i++)
		line[i] = buff[i];
	line[i] = '\0';
	return (i + 1);
}

/**
 * _realloc - allocate memory and set to 0
 * @ptr: unsigned int
 * @old_size: unsigned int
 * @new_size: unsigned int
 * Return: void*
 */
void *_realloc(void *ptr, int old_size, int new_size)
{
	char *newptr;
	int i;

	if (new_size == old_size)
		return (ptr);
	if (ptr == NULL)
	{
		newptr = malloc(new_size);
			if (newptr == NULL)
				return (NULL);
		return (newptr);
	}
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);
	if (ptr == NULL)
		return (newptr);
	for (i = 0; i < old_size && i < new_size; i++)
		newptr[i] = ((char *)ptr)[i];
	free(ptr);
	return (newptr);
}
