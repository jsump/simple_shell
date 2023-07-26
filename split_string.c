#include "shell.h"

#define MAX_TOKENS 64
void free_tokens(char **tokens);
/**
 * split_input - Splits a string into tokens
 * @str: String to be split
 *
 * Return: Array of tokens
 */
char **split_input(char *str)
{
	int position = 0;
	char **tokens = malloc(MAX_LENGTH * sizeof(char *));
	char *token;

	if (!tokens)
	{
		perror("Error allocating memory\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(str, " \t\n");
	while (token != NULL)
	{
		tokens[position] = strdup(token);
		if (!tokens[position])
		{
			perror("Error allocating memory\n");
			free_tokens(tokens);
			exit(EXIT_FAILURE);
		}
		position++;

		if (position >= MAX_TOKENS)
		{
			fprintf(stderr, "too many arguments\n");
			free_tokens(tokens);
			break;
		}
		token = strtok(NULL, " \t\n");
	}
	tokens[position] = NULL;
	return (tokens);
}
/**
 * free_tokens - free tokens
 * @tokens - tokens to be freed
 */
void free_tokens(char **tokens)
{
	int i;
	
	for (i = 0; tokens[i] != NULL; i++)
	{
		free(tokens[i]);
	}
	free(tokens);
}
