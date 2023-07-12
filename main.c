#include "shell.h"

/**
 * main - simple shell entry point
 * Return: 0
 */
int main(void)
{
	char *buffer, *token, input[MAX_INPUT_LENGTH], *args[MAX_LENGTH / 2 + 1];
	int status, should_run = 1, i;
	pid_t pid;

	buffer = malloc(sizeof(char) * MAX_LENGTH);
	if (!buffer)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	while (should_run)
	{
		display_prompt();

		if (!fgets(input, MAX_INPUT_LENGTH, stdin))
		{
			should_run = 0;
			break;
		}
		if (strcmp(input, "exit\n") == 0)
			exit_shell();
		token = strtok(input, " \n");
		i = 0;

		while (token)
		{
			args[i] = token;
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
			if (execvp(args[0], args) == -1)
			{
				perror("execvp failed");
				exit(EXIT_FAILURE);
			}
		}
		else
			waitpid(pid, &status, 0);
	}
	free(buffer);
	return (0);
}
