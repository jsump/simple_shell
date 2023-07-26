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
		printf("%s\n", env_vars[i]);
	}
	free(env_vars);
}
/**
 * compare_env_vars - sorting env variables in alph order
 * @a: first element
 * @b: second element
 */
int compare_env_vars(const void *a, const void *b)
{
    return strcmp(*(const char **)b, *(const char **)a);
}
