#ifndef SHELL_H
#define SHELL_H

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define DELIM " \t\n"
#define PROMPT "$ "
extern char **environ;

char *read_line(void);
void me_printf(const char *output);
char **strtkn(char *line);
int _execute(char **command, char **argv, int idx);
void array_tools(char **arr);
char *get_env(char *name);
char *get_path(char *command);
void print_error(char *name, int idx, char *cmd);

char *_strdup(const char *str);
int _strcmp(char *s1, char *s2);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
int _strlen(char *s);


int is_builtin(char *command);
void handle_builtin(char **command, char **argv, int *status, int idx);
void exit_shell(char **command, int *status);
void print_env(char **command, int *status);
char *_itoa(int n);
void reverse_string(char *str, int len);

#endif
