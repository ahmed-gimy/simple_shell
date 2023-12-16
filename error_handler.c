#include "shell.h"

/**
 * custom_perror - function
 * @msg: char*
 */
void custom_perror(char *msg)
{
	char n[10];

	int_to_str(cmd_count, n, _intlen(cmd_count, 10), 0);
	handled_write(STDERR_FILENO, program_name, _strlen(program_name));
	handled_write(STDERR_FILENO, ": ", 2);
	handled_write(STDERR_FILENO, n, _intlen(cmd_count, 10));
	handled_write(STDERR_FILENO, ": ", 2);
	handled_write(STDERR_FILENO, gArgs[0], _strlen(gArgs[0]));
	handled_write(STDERR_FILENO, ": ", 2);
	handled_write(STDERR_FILENO, msg, _strlen(msg));
	handled_write(STDERR_FILENO, "\n", 1);
}


/**
 * process_args - function
 */
void process_args(void)
{
	int i, pid;
	char *var;

	for (i = 0; gArgs && gArgs[i]; i++)
	{
		if (_strcmp(gArgs[i], "$$") == 0)
		{
			pid = getpid();
			gArgs[i] = _realloc(gArgs[i], 0, _intlen(pid, 10) + 1);
			int_to_str(pid, gArgs[i], _intlen(pid, 10), 0);
		}
		else if (_strcmp(gArgs[i], "$?") == 0)
		{
			pid = getpid();
			gArgs[i] = _realloc(gArgs[i], 0, _intlen(status, 10) + 1);
			int_to_str(status, gArgs[i], _intlen(status, 10), 0);
		}
		else if (gArgs[i][0] == '$' && _strlen(gArgs[i]) > 1)
		{
			var = _getenv(gArgs[i] + 1, 1);
			if (!var)
			{
				gArgs[i][0] = '\0';
				continue;
			}
			gArgs[i] = _realloc(gArgs[i], 0, _strlen(var) + 1);
			str_append(var, gArgs[i], 0);
		}
	}
}
