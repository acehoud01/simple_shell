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
extern char **environ;

char *read_line(void);
void me_printf(const char *output);
char **strtkn(char *line);
int _execute(char **command, char **argv, int idx);
void array_tools(char **arr);
char *get_env(char *name);
char *_getpath(char *command);


char *_strdup(const char *str);
int _strcmp(char *s1, char *s2);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
int _strlen(char *s);

void print_error(char *name, char *cmd, int idx);
char *_itoa(int n);
void reverse_str(char *str, int len);


#endif
