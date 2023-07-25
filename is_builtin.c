#include "shell.h"

/**
 * is_builtin - Checks if a command is a built-in shell command
 * @args: Array of command and arguments
 *
 * Return: 1 if the command is built-in, 0 otherwise
 */
int is_builtin(char **args)
{
	if (strcmp(args[0], "cd") == 0 || strcmp(args[0], "exit") == 0 ||
		strcmp(args[0], "env") == 0)
	{
		return (1);
	}

	return (0);
}
