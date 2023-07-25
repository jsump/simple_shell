#include "shell.h"
/**
* execute_logical_operations -function to execute logical operations
* @commands: commands to be input
*/
void execute_logical_operations(char **commands)
{
	int i = 0;

	while (commands[i] != NULL)
	{
		int result;
		char **args = split_input(commands[i]);
		pid_t pid = fork();

		if (pid == -1)
		{
			perror("fork failed");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			exec_function(args);
			exit(EXIT_SUCCESS);
		}
		else
		{
			waitpid(pid, &result, 0);
			if (strcmp(commands[i], "&&") == 0 && result != 0)
			{
				break;
			}
			else if (strcmp(commands[i], "||") == 0 && result == 0)
			{
				break;
			}
		}
		i++;
	}
}
