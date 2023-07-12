#include "shell.h"
/**
 * execute - executes a command
 * @command: array of tokens containing the command
 * Return: 1 if successful, 0 if an error occurs
 */
int execute(char **command)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (command[0] || execve(command[0], command, environ) == -1)
		{
			perror("Error executing command\n");
			exit(EXIT_FAILURE);
		}
		return (1);
	}
	else if (pid < 0)
	{
		perro("Error forking\n");
		return (0);
	}
	else
	{
		do {
			waitpid(pis, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		if (feof(stdin))
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}
	}
	return (1);
}
