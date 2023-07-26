#include "shell.h"
/**
 * read_input - reads input from user
 * @input_stream: stream on input characters
 * Return: pointer to the string input
 */
char *read_input(FILE *input_stream)
{
	char *input = NULL;
	ssize_t bytes_read;
	size_t buf_size = 0;

	bytes_read = getline(&input, &buf_size, input_stream);

	if (bytes_read == -1)
	{
		if (feof(input_stream))
		{
			free(input);
			return (NULL);
		}
		else
		{
			perror("Error reading input\n");
			exit(EXIT_FAILURE);
		}
	}
	return (input);
}
