#include "shell.h"
/**
 * getline - get line
 * lp: pointer to char pointer that will store output string
 * @n: pointer to size_t variable to store the length of output stream
 * Return: 1 on success, -1 if error occurred, 0 on end of input
 */
int _getline(char **lp, size_t *n)
{
	static char buffer[BUFSIZ];
	static int fd;
	static int position;
	static int length;
	static int initialized = 0;
	int i;

	if (!initialized)
	{
		fd = 0;
		position = 0;
		length = 0;
		initialized = 1;
	}
	if (lp == NULL || n == NULL)
		return (-1);
	if (*lp == NULL || *n == 0)
	{
		*lp = malloc(BUFSIZ);
		if (*lp == NULL)
			return (-1);
		*n = BUFSIZ;
	}
	size_t len = 0;

	while (1)
	{
		if (position >= length)
		{
			length = read(fs, buffer, BUFSIZ);
			if (length == -1)
			{
				free(*lp);
				return (-1);
			}
			if (length == 0)
			{
				if (len ==0)
				{
					free(*lp);
					return (0);
				}
				break;
			}
			position = 0;
		}
		i = position;
		while (i < length && buffer[i] != '\n')
			i++;
		if (len + i - position + 1 > *n)
		{
			char *tmp = realloc(*lp, len + i - position + BUFSIZ);
			if (tmp == NULL)
			{
				free(*lp);
				return (-1);
			}
			*lp = tmp;
			*n = len + i - position + BUFSIZ;
		}
		memcpy(*lp + len, buffer + position, i - position);
		len += i - position;
		position = i + 1;
		if ( i < length || buffer[i] == '\n')
			break;
	}
	(*lp)[len] = '\0';
	return (1);
}
