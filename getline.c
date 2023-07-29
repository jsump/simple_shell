#include "shell.h"

/**
 * own_getline - Read a line from input stream.
 * @lp: Pointer to the buffer storing the line.
 * @n: Pointer to the size of the buffer.
 * @stream: Input stream to read from.
 * Return: Number of characters read, or -1 on failure.
 */
ssize_t own_getline(char **lp, size_t *n, FILE *stream)
{
	char *buffer = NULL;
	size_t len = 0;
	ssize_t read;

	if (lp == NULL || n == NULL || stream == NULL)
		return (-1);

	if (*lp == NULL || *n == 0)
	{
		*lp = malloc(128);
		if (*lp == NULL)
			return (-1);
		*n = 128;
	}

	buffer = *lp;
	len = *n;

	read = getline(&buffer, &len, stream);
	if (read == -1)
		return (-1);

	*lp = buffer;
	*n = len;

	return (read);
}
