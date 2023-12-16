#include "shell.h"


/**
 * _getline - malloc err handler
 * @buffer: char
 * Return: int
 */
int _getline(char *buffer)
{
	int bytes_read, q, dq;

	q = 0, dq = 0;
	bytes_read = read_whole(buffer, 0, &q, &dq, 0);
	if (bytes_read < 0)
	{
		handled_write(STDERR_FILENO,
			"\nshell: unexpected EOF while looking for matching \"\'\n", 54);
		return (1);
	}
	if (buffer[bytes_read - 1] != '\n')
		handled_write(STDOUT_FILENO, "\n", 1);
	else
		buffer[bytes_read - 1] = '\0';
	buffer[bytes_read] = '\0';
	return (0);
}


/**
 * _getenv - malloc err handler
 * @name: char
 * @val_only: char
 * Return: int
 */
char *_getenv(char *name, int val_only)
{
	int i, name_len;

	name_len = _strlen(name);
	for (i = 0; environ[i] != NULL; i++)
		if (nonexact_strcmp(name, environ[i]) == 0 && environ[i][name_len] == '=')
			return (val_only == 1 ? environ[i] + name_len + 1 : environ[i]);
	return (NULL);
}

/**
 * _setenv - malloc err handler
 * @name: char
 * @value: char
 */
void _setenv(char *name, char *value)
{
	size_t name_len, value_len, total_len;
	char *var_pos, *env_var;

	var_pos = _getenv(name, 0);
	name_len = _strlen(name);
	value_len = _strlen(value);
	total_len = name_len + value_len + 1;
	env_var = (char *)malloc(total_len > 1024 ? total_len : 1024);
	if (env_var == NULL)
		alloc_err();
	alloc_new_var(env_var);
	str_append(name, env_var, 0);
	str_append("=", env_var, name_len);
	str_append(value, env_var, name_len + 1);
	if (var_pos)
		environ[_getenvIndex(name)] = env_var;
	else
		realloc_environ(env_var, 1);
}

/**
 * realloc_environ - malloc err handler
 * @var: char
 * @op: char
 */
void realloc_environ(char *var, int op)
{
	int i, j, name_len;

	name_len = _strlen(var);
	for (i = 0; var && op == 0 && environ[i] != NULL; i++)
	{
		if (nonexact_strcmp(var, environ[i]) == 0 && environ[i][name_len] == '=')
		{
			environ[i] = NULL;
			for (j = i; environ[j + 1] != NULL; j++)
				environ[j] = environ[j + 1];
			environ[j] = NULL;
			var = NULL;
		}
	}
	if (var)
	{
		for (i = 0; environ[i] != NULL;)
			i++;
		environ[i] = var;
		environ[i + 1] = NULL;
	}
}

/**
 * command_to_path - malloc err handler
 * @buff: char
 * Return: char
 */
int command_to_path(char *buff)
{
	char *all_paths;
	int len;
	struct stat st;

	all_paths = _getenv("PATH", 1);
	if (all_paths == NULL)
		return (1);
	if (*all_paths == ':' && lstat(*gArgs, &st) == 0)
	{
		str_append(*gArgs, buff, 0);
		return (0);
	}
	while (*all_paths != '\0')
	{
		if (*all_paths != ':')
		{
			len = get_path(all_paths, buff), all_paths += len;
			str_append("/", buff, len);
			str_append(gArgs[0], buff, len + 1);
			if (lstat(buff, &st) == 0)
				return (0);
		}
		else
			all_paths++;
	}
	return (1);
}
