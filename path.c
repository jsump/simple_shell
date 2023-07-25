#include "shell.h"
/**
* get_path_directories - function to get path directories
*/
char **get_path_directories(void)
{
	char *path = getenv("PATH");
	char **directories = malloc(MAX_LENGTH * sizeof(char *));
	char *token;
	int i = 0;

	if (!directories)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}

	token = strtok(path, ":");
	while (token != NULL)
	{
		directories[i] = malloc(strlen(token) + 1);
		if (!directories[i])
		{
			perror("malloc failed");
			exit(EXIT_FAILURE);
		}
		strcpy(directories[i], token);
		token = strtok(NULL, ":");
		i++;
	}
	directories[i] = NULL;

	return directories;
}
