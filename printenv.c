#include "shell.h"
/**
 * print_environment - print current environment
 */
void print_environment(void)
{
	int i =0;

	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}

}
