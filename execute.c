#include "shell.h"
/**
* execute_single_command - Execute a single command(absolute or relative)
* @command: The command to execute.
* Return: 1 on success, 0 on failure.
*/
int execute_single_command(char **command)
{
	int status;
	pid_t pid = fork();

	if (pid == 0)
	{
		if (execve(command[0], command, environ) == -1)
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
		return (1);
	}
}

/**
* execute_path_commands - Execute a command by searching through path dirs.
* @command: The command to execute.
* @path_directris: Array of path directories.
* Return: 1 on success, 0 on failure.
*/
int execute_path_commands(char **command, char **path_directris)
{
	int j, status;
	char *full_path;
	pid_t pid = fork();

	for (j = 0; path_directris[j] != NULL; j++)
	{
		full_path = create_full_path(path_directris[j], command[0]);
		
		if (!full_path)
		{
			perror("malloc failed");
			exit(EXIT_FAILURE);
		}
		sprintf(full_path, "%s/%s", path_directris[j], command[0]);

		if (pid == 0)
		{
			if (execve(full_path, command, environ) == -1)
			{
				free(full_path);
				exit(EXIT_FAILURE);;
			}
			return (1);
		}
		else if (pid < 0)
		{
			perror("Error forking\n");
			free(full_path);
			exit(EXIT_FAILURE);
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
	fprintf(stderr, "Command no found\n");
	return (0);
}

/**
* execute - Execute a command.
* @command: The command to execute.
* @path_directories: Array of path directories.
* Return: 1 on success, 0 on failure.
*/
int execute(char **command, char **path_directories)
{
	int i = 0;

	while (command[i] != NULL)
	{
		if (strcmp(command[i], "") != 0)
		{
			i++;
			continue;
		}
		
	}

	if (command[i] == NULL)
	{
		return (1);
	}

	if (command[i][0] == '/' || command[i][0] == '.')
	{
		return (execute_single_command(command + i));
	}
	else
	{
		return (execute_path_commands(command + i, path_directories));
	}
}
/**
* create_full_path - Create the full path for a given command and directory.
* @directory: The directory to append.
* @command: The command to append to the directory.
* Return: The full path as a string.
*/
char *create_full_path(const char *directory, const char *command)
{
	size_t len_dir, len_cmd;
	char *full_path;

	if (!directory || !command)
		return (NULL);

	len_dir = strlen(directory);
	len_cmd = strlen(command);

	full_path = malloc(len_dir + len_cmd + 2);
	if (!full_path)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}

	strcpy(full_path, directory);
	if (full_path[len_dir - 1] != '/')
		strcat(full_path, "/");
	strcat(full_path, command);

	return (full_path);
}
