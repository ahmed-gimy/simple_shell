#include "shell.h"



/**
 * interrupt_handler - handle signals
 */
void interrupt_handler(void)
{
	free_all();
	_exit(0);
}

/**
 * handle_exit - handle signals
 */
void handle_exit(void)
{
	int tmp_status;

	if (gArgs[1])
		tmp_status = str_to_int(gArgs[1]);
	if (gArgs[1] && !gArgs[2])
		tmp_status = handle_status(tmp_status), free_all(), _exit(tmp_status);

	status = handle_status(status), free_all(), _exit(status);
}

/**
 * handle_env - handle signals
 */
void handle_env(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		handled_write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		handled_write(STDOUT_FILENO, "\n", 1);
	}
}

/**
 * handle_setenv - handle signals
 */
void handle_setenv(void)
{
	if (!gArgs[0] || !gArgs[1] || !gArgs[2])
		handled_write(STDERR_FILENO,
			"Usage: setenv [VARIABLE_NAME] [VARIABLE_VALUE]\n", 48);
	else
		_setenv(gArgs[1], gArgs[2]);
}

/**
 * handle_unsetenv - handle signals
 */
void handle_unsetenv(void)
{
	if (!gArgs[0] || !gArgs[1])
		handled_write(STDERR_FILENO, "Usage: unsetenv [VARIABLE_NAME]\n", 33);
	else if (_getenv(gArgs[1], 1) == NULL)
		handled_write(STDERR_FILENO, "variable doesn't exist\n", 24);
	else
		realloc_environ(gArgs[1], 0);
}
