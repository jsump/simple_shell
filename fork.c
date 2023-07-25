#include "shell.h"
/**
 * my_fork - function to create a new process
 * Return: nothing
 */
void my_fork(void)
{
	pid_t my_pid;
	pid_t pid;
	char pid_str[20];

	write(STDOUT_FILENO, "Before fork\n", 12);
	pid = fork();
	if (pid == -1)
	{
		write(STDERR_FILENO, "Error:", 6);
		return;
	}
	write(STDOUT_FILENO, "After fork\n", 11);
	my_pid = getpid();
	snprintf(pid_str, sizeof(pid_str), "%d", my_pid);
	write(STDOUT_FILENO, "My pid is ", 10);
	write(STDOUT_FILENO, pid_str, strlen(pid_str));
	write(STDOUT_FILENO, "\n", 1);
}

