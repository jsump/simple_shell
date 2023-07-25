#include "shell.h"
/**
 * execute - executes a command
 * @command: array of tokens containing the command
 * Return: 1 if successful, 0 if an error occurs
 */
int execute(char **command, char **path_directories)
{
	int i = 0;
	int status, j;
	pid_t pid;

	while (command[i] != NULL)
	{
		if (strcmp(command[i], "") != 0)
		{
			break;
		}
		i++;
	}
	if (command[i] == NULL)
	{
		return (1);
	}

	if (command[i][0] == '/' || command[i][0] == '.')
	{
		pid = fork();
		if (pid == 0)
		{
			if (execve(command[i], command + i, environ) == -1)
			{
				perror("Error executing command\n");
				exit(EXIT_FAILURE);
			}
			return (1);
		}
		else if (pid < 0)
		{
			perror("Error forking\n");
			return (0);
		}
		else
		{
			do {
				waitpid(pid, &status, WUNTRACED);
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
			if (feof(stdin))
			{
				printf("\n");
				exit(EXIT_SUCCESS);
			}
		}
	}
	else
	{
		for (j = 0; path_directories[j] != NULL; j++)
		{
			char *full_path = malloc(strlen(path_directories[j]) + strlen(command[i]) + 2);
			if (!full_path)
			{
				perror("malloc failed");
				exit(EXIT_FAILURE);
			}
			sprintf(full_path, "%s/%s", path_directories[j], command[i]);
			pid = fork();
			if (pid == 0)
			{
				if (execve(full_path, command + i, environ) == -1)
				{
					free(full_path);
					continue;
				}
				return (1);
			}
			else if (pid < 0)
			{
				perror("Error forking\n");
				free(full_path);
				return (0);
			}
			else
			{
				do {
					waitpid(pid, &status, WUNTRACED);
				} while (!WIFEXITED(status) && !WIFSIGNALED(status));
				free(full_path);
				if (feof(stdin))
				{
					printf("\n");
					exit(EXIT_SUCCESS);
				}
				return (1);
			}
		}
		perror("Command not found");
	}
	return (1);
}
