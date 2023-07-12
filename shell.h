#ifndef shell_h
#define shell_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

#define BUFFER_SIZE 1024
#define MAX_LENGTH 1024
#define DELIMITERS " \t\r\n\a"
#define MAX_INPUT_LENGTH 1024

extern char **environ;

int _putchar(char c);

void display_prompt(void);
void print_environment(void);
int execute(char **command);
char **split_string(char *str);

void execute_command(char *command);
void exit_shell(void);

char *read_inout(void);
char **split_input(char *input);
int is_builtin(char **args);
void execute_builtin(char **args, char **env);
void handle_error(char *msg);
void print_env(char **env);

#endif

