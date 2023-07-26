#include "shell.h"

/**
 * split_input - Splits a string into tokens
 * @str: String to be split
 *
 * Return: Array of tokens
 */
char **split_input(char *str)
{
	int i, position = 0;
	char **tokens = malloc(MAX_LENGTH * sizeof(char *));
	char *token;

	if (!tokens)
	{
		perror("Error allocating memory");
		exit(EXIT_FAILURE);
	}

	token = strtok(str, DELIMITERS);
	while (token != NULL)
	{
		tokens[position] = malloc(strlen(token) + 1);
		if (!tokens[position])
		{
			perror("Error allocating memory\n");
			exit(EXIT_FAILURE);
		}
		if (strcpy(tokens[position], token) == NULL)
		{
			perror("Error copying token'n");
			exit(EXIT_FAILURE);
		}
		position++;

		token = strtok(NULL, DELIMITERS);
	}
	tokens[position] = NULL;
	for (i = 0; i < position; i ++)
	{
		free(tokens[i]);
	}
	return (tokens);
}
