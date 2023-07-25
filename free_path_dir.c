#include "shell.h"
/**
 * free_path_directories - free mempru allocated for path directories
 * @directories: directory
 */
void free_path_directories(char **directories)
{
	int i = 0;

	while (directories[i] != NULL)
	{
		free(directories[i]);
		i++;
	}
	free(directories);
}
