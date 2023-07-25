#include "shell.h"

void exec_function(char **args);
void execute_setenv(char **args);
void execute_unsetenv(char **args);

/**
 * main - entry point
 * @argc: number of arguments
 * @argv: array of strings containing the arguments
 * Return: Always 0
 */
int main(int argc, char *argv[])
{
	char *buffer, *token, *args[MAX_LENGTH / 2 + 1];
	int status, should_run = 1, i;
	pid_t pid;

	FILE *input_stream = stdin;

	if (argc > 1)
	{
		input_stream = fopen(argv[1], "r");
		if (!input_stream)
		{
			perror("Error opening inout file");
			exit(EXIT_FAILURE);
		}
	}

	buffer = malloc(sizeof(char) * MAX_LENGTH);
	if (!buffer)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	while (should_run)
	{



		buffer = read_input(input_stream);
		if (buffer == NULL);
		{
			should_run = 0;
			break;
		}
		if (strcmp(buffer, "exit") == 0)
		{
			should_run = 0;
			free(buffer);
			break;
		}
		if (strcmp(buffer, "") == 0)
		{
			break;
		}
		if (buffer[0] == '#')
		{
			continue;
		}
		token = strtok(buffer, " \n");
		i = 0;

		while (token != NULL)
		{
			args[i] = malloc(strlen(token) + 1);
			if (!args[i])
			{
				perror("malloc failes");
				exit(EXIT_FAILURE);
			}
			strcpy(args[i], token);
			token = strtok(NULL, " \n");
			i++;
		}
		args[i] = NULL;

		pid = fork();
		if (pid == -1)
		{
			perror("fork failed");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			exec_function(args);
			exit(EXIT_SUCCESS);
		}
		else
		{
			waitpid(pid, &status, 0);
		}

		i = 0;
		while (args[i] != NULL)
		{
			free(args[i]);
			i++;
		}
		free(buffer);
		if (buffer[0] != '\0')
		{
			execute_logical_operations(args);
		}
	}
	if (argc > 1)
	{
		if (fclose(input_stream) != 0)
		{
			perror("Error closing file");
			exit(EXIT_FAILURE);
		}
	}
	free(buffer);
	return (0);
}
/**
 * exec_function - handle arguemnts
 * @args: arrayof commands
 */
void exec_function(char **args)
{
	if (strcmp(args[0], "cd") == 0)
	{
		if (args[1] != NULL)
		{
			execute_cd(args[1]);
		}
		else
		{
			fprintf(stderr, "cd: missing srgument\n");
			exit(EXIT_FAILURE);
		}
	}
	else if (strcmp(args[0], "setenv") == 0)
	{
		execute_setenv(args);
	}
	else if (strcmp(args[0], "unsetenv") == 0)
	{
		execute_unsetenv(args);
	}
	else if (strcmp(args[0], "pwd") == 0)
	{
		execute_pwd();
		exit(EXIT_SUCCESS);
	}
	else
	{
		if (execvp(args[0], args) == -1)
		{
			perror("execvp failed");
			exit(EXIT_FAILURE);
		}
	}
}

/**
 * execute_setenv - execute setenv command
 * @args: number of arguments
 */
void execute_setenv(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		return;
	}
	if (setenv(args[1], args[2], 1) == -1)
		perror("setenv failed");
}

/**
 * execute_unsetenv - execute unsetenv command
 * @args: number of arguments
 */
void execute_unsetenv(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
		return;
	}
	if (unsetenv(args[1]) == -1)
		perror("unsetenv failed");
}
