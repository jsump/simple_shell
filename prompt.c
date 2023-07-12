#include "shell.h"

/**
 * display_prompt - display a promt and wait for user to type a command,
 * a command line always ends with a new line.
 */
void display_prompt(void)
{
	printf("$ ");
	fflush(stdout);
}
