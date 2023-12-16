#include "shell.h"


/**
 * free_args - free
 */
void free_args(void)
{
	int i;

	if (!gArgs)
		return;
	for (i = 0; gArgs[i]; i++)
		free(gArgs[i]);
	free(gArgs);
	gArgs = NULL;
}


/**
 * free_cmds - free
 */
void free_cmds(void)
{
	int i;

	if (!cmds)
		return;
	for (i = 0; cmds[i]; i++)
		free(cmds[i]);
	free(cmds);
	cmds = NULL;
}


/**
 * free_env - free
 */
void free_env(void)
{
	int i;

	for (i = 0; i < 100 && env_vars[i] != NULL; i++)
		free(env_vars[i]);
}


/**
 * free_all - free
 */
void free_all(void)
{
	free_args(), free_env(), free_cmds();
}
