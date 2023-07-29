#ifndef shell_h
#define shell_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <limits.h>
#include <signal.h>

#define BUFFER_SIZE 1024
#define MAX_LENGTH 1024
#define DELIMITERS " \t\r\n\a"
#define MAX_INPUT_LENGTH 1024
#define MAX_PATH_DIRS 64

extern char **environ;

int _putchar(char c);

void display_prompt(void);
void print_environment(void);
int execute(char **command, char **path_directories);
char **split_string(char *str);

void execute_command(char *command);
void exit_shell(char **args);

char *read_input(FILE *input_stream);
char **split_input(char *input);
int is_builtin(char **args);
void execute_builtin(char **args, char **env);
void handle_error(char *msg);
void print_env(char **env);

void execute_cd(char *arg);
void execute_pwd(void);
void my_fork(void);

void exec_function(char **args);
void fork_handle(char **args, int status);

ssize_t own_getline(char **lp, size_t *n, FILE *stream);

char **get_path_directories(void);
void free_path_directories(char **directories);
void execute_logical_operations(char **commands);


int execute(char **command, char **path_directories);
int execute_single_command(char **command);
int execute_path_commands(char **command, char **path_directories);
char *create_full_path(const char *directory, const char *command);

char **get_path_directories(void);
char *get_full_path(const char *command);

#endif
