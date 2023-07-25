#include "shell.h"

#include <limits.h>


void get_curr_working_dir(char *cwd);
void set_env_variables(char *prev_dir, char *cwd);

/**
 * execute_cd - execute cd command
 * @arg: number of arguments
 * Return: exit status
 */
void execute_cd(char *arg)
{
	char prev_dir[PATH_MAX];
	char cwd[PATH_MAX];
	char *token;

	token = strtok(arg, "\n");
	while (token != NULL)
	{
		if (strcmp(token, "-") == 0)
		{
			char *oldpwd = getenv("OLDPWD");

			if (oldpwd == NULL)
			{
				fprintf(stderr, "cd: OLDPWD not set\n");
				return;
			}
			if (chdir(oldpwd) == -1)
			{
				fprintf(stderr, "cd failed: %s\n", oldpwd);
				return;
			}
			strcpy(prev_dir, oldpwd);
		}
		else
		{
			if (getcwd(prev_dir, sizeof(prev_dir)) == NULL)
			{
				perror("getcwd failed");
				return;
			}
			if (chdir(token) == -1)
			{
				perror("cd failed");
				return;
			}
			strcpy(prev_dir, token);
		}
		token = strtok(NULL, "\n");
	}
	get_curr_working_dir(cwd);
	set_env_variables(prev_dir, cwd);
}
/**
 * get_curr_working_dir - function to get current working directory
 * @cwd: variable to store working directory
 */
void get_curr_working_dir(char *cwd)
{
	if (getcwd(cwd, PATH_MAX - 1) == NULL)
	{
		perror("getcwd failed");
		exit(EXIT_FAILURE);
	}
	cwd[strlen(cwd)] = '\0';
}
/**
 * set_env_variables - function to set environment variables for previous dir
 * @prev_dir: variable to store previous directory
 * @cwd: variable to store current working directory
 */
void set_env_variables(char *prev_dir, char *cwd)
{
	if (setenv("OLDPWD", prev_dir, 1) == -1)
	{
		perror("setenv failed");
		exit(EXIT_FAILURE);
	}
	if (setenv("PWD", cwd, 1) == -1)
	{
		perror("setenv failed");
		exit(EXIT_FAILURE);
	}
}
