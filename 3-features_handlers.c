#include "shell.h"


/**
 * alloc_err - malloc err handler
 */
void alloc_err(void)
{
	status = 1;
	perror("Memory Allocation Error");
}

/**
 * handle_status - malloc err handler
 * @val: int
 * Return: int
 */
int handle_status(int val)
{
	char n[10];

	int_to_str(cmd_count, n, _intlen(cmd_count, 10), 0);
	if (val < 0)
	{
		handled_write(STDERR_FILENO, program_name, _strlen(program_name));
		handled_write(STDERR_FILENO, ": ", 2);
		handled_write(STDERR_FILENO, n, _strlen(n));
		handled_write(STDERR_FILENO, ": ", 2);
		handled_write(STDERR_FILENO, "exit: Illegal number: ", 22);
		handled_write(STDERR_FILENO, gArgs[1], _strlen(gArgs[1]));
		handled_write(STDERR_FILENO, "\n", 1);
	}
	val = val > 255 ? 1000 % 256 : val < 0 ? 2 : val;
	return (val);
}

/**
 * get_path - malloc err handler
 * @paths: int
 * @path: int
 * Return: int
 */
int get_path(char *paths, char *path)
{
	int i;

	for (i = 0; *paths != ':' && *paths != '\0'; paths++, i++)
		path[i] = *paths;
	path[i] = '\0';
	return (i);
}

/**
 * fill_args - malloc err handler
 * @count: int
 * @buffer: int
 * Return: int
 */
int fill_args(int count, char *buffer)
{
	int i, l, word_len, q, dq;

	q = 0, dq = 0;
	gArgs = malloc(sizeof(char *) * (count + 1));
	if (!gArgs)
	{
		alloc_err();
		return (-1);
	}
	for (i = 0; i < count + 1; i++)
		gArgs[i] = NULL;
	for (i = 0; i < count; i++)
	{
		word_len = 0;
		while ((*buffer && *buffer == ' ') || *buffer == '\t')
			buffer++;
		for (l = 0; ((buffer[l] != '\t' && buffer[l] != ' ')
			|| (dq || q)) && buffer[l] != '\0'; l++)
		{
			if (handle_quote(buffer[l], &q, &dq) > 0)
			remove_char(buffer, l), l--;
		}
		word_len = l;
		gArgs[i] = malloc(sizeof(char) * (word_len + 1));
		if (!gArgs[i])
		{
			free_args(), alloc_err();
			return (-1);
		}
		for (l = 0; l < word_len; l++)
			gArgs[i][l] = *buffer, buffer++;
		gArgs[i][l] = '\0';
	}
	gArgs[count] = NULL;
	return (0);
}

/**
 * fill_cmds - malloc err handler
 * @buff: int
 * Return: int
 */
int fill_cmds(char *buff)
{
	int i, l, cmds_count, cmd_len, q, dq;

	cmds_count = 0, q = 0, dq = 0;
	for (i = 0; buff[i] != '\0'; i++)
		if (handle_quote(buff[i], &q, &dq) == 0 && buff[i] == ';' && q + dq == 0)
			cmds_count++;
	cmds_count++;
	cmds = malloc(sizeof(char *) * (cmds_count + 1));
	if (!cmds)
	{
		alloc_err();
		return (-1);
	}
	for (i = 0; i < cmds_count + 1; i++)
		cmds[i] = NULL;
	for (i = 0; i < cmds_count; i++)
	{
		for (l = 0; buff[l] != '\0' && (buff[l] != ';' || q + dq != 0);)
		{
			if (dq + q == 0 && buff[l] == '#' && (l == 0 || buff[l - 1] == ' '))
				break;
			handle_quote(buff[l], &q, &dq), l++;
		}
		if (l <= 0)
			continue;
		cmds[i] = malloc(sizeof(char) * (l + 1)), cmds[i][l] = '\0';
		if (!cmds[i])
		{
			free_cmds(), alloc_err();
			return (-1);
		}
		cmd_len = l;
		for (l = 0; l < cmd_len; buff++, l++)
			handle_quote(*buff, &q, &dq), cmds[i][l] = *buff;
		buff++;
	}
	return (0);
}
