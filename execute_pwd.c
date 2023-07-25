#include "shell.h"
/**
 * execute_pwd - execute pwd function (show location)
 */
void execute_pwd(void)
{
	char cwd[MAX_INPUT_LENGTH];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("pwd failed");
		return;
	}
	else
	{
		printf("%s\n", cwd);
	}
}
