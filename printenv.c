#include "shell.h"

int compare_env_vars(const void *a, const void *b);

/**
 * print_environment - print current environment
 */
void print_environment(void)
{
	int i, count = 0;
	char **envp;
	char **env_vars;

	for (envp = environ; *envp != NULL; envp++)
	{
		count++;
	}

	env_vars = malloc(count * sizeof(char *));
	if (!env_vars)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}

	for (i = 0, envp = environ; *envp != NULL; envp++, i++)
	{
		env_vars[i] = *envp;
	}

	qsort(env_vars, count, sizeof(char *), compare_env_vars);

	for (i = 0; i < count; i++)
	{
		write(STDOUT_FILENO, env_vars[i], strlen(env_vars[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
	free(env_vars);
}

/**
 * compare_env_vars - sorting env variables in alphabetical order
 * @a: first element
 * @b: second element
 *
 * Return: negative value if a < b, positive value if a > b, 0 if a == b
 */
int compare_env_vars(const void *a, const void *b)
{
	return (strcmp(*(const char **)a, *(const char **)b));
}
