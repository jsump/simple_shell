#include "shell.h"
/**
 * get_full_path - search for the full path of a command,
 * in the directories listed in the PATH
 * @command: the command to search for
 * Return: the full path of the command if found, otherwise NULL
 */
char *get_full_path(const char *command)
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *dir = strtok(path_copy, ":");

	if (path_copy == NULL)
	{
		perror("strdup failed");
		exit(EXIT_FAILURE);
	}

	while (dir != NULL)
	{
		char *full_path = malloc(strlen(dir) + strlen(command) + 2);

		if (full_path == NULL)
		{
			perror("malloc failed");
			exit(EXIT_FAILURE);
		}

		strcpy(full_path, dir);
		strcat(full_path, "/");
		strcat(full_path, command);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
