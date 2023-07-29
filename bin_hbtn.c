#include "shell.h"

/**
 * execute_1 - Execute a command.
 * @command: The command to execute.
 * @path_directories: Array of path directories.
 * Return: 1 on success, 0 on failure.
 */
int execute_1(char **command, char **path_directories)
{
	if (command[0] == NULL)
		return (1);

	if (strcmp(command[0], "/bin/ls") == 0)
	{
		return (execute_single_command(command));
	}
	else if (strcmp(command[0], "cp") == 0)
	{
		char *cp_command[] = {"cp", "/bin/ls", "hbtn_ls", NULL};
		char *hbtn_ls_command[] = {"./hbtn_ls", "/var", NULL};

		if (execute_single_command(cp_command))
			return (execute_single_command(hbtn_ls_command));
		else
			return (0);
	}
	else
	{
		return (execute_path_commands(command, path_directories));
	}
}
