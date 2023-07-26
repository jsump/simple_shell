#include "shell.h"
/**
 * exit_shell - exits the shell
 */
void exit_shell(char **args)
{
	if (args[1] == NULL)
	{
		printf("Exiting the shell...\n");
		exit(EXIT_SUCCESS);
	}
	else
	{
		char *endptr;
		int status = strtol(args[1], &endptr, 10);

		if (*endptr == '\0')
		{
			printf("Exiting the shell with status code: %d\n", status);
			exit(status);
		}

		else
		{
			printf("Invalid argument for exit: %s\n", args[1]);
		}
	}
}

