#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>
#include <signal.h>

#define FALSE 0
#define TRUE 1
#define NEITHER 2
#define MATCH 3
#define PREFIX 4
#define EXIT_SHELL 5
#define SKIP_FORK 6
#define DO_EXECVE 7

/**
 * struct Alias - singly linked list
 * @name: name of alias
 * @value: command that alias calls
 * @next: points to next node
 */
typedef struct Alias
{
    char *name;
    char *value;
    struct Alias *next;
} Alias;

extern char **environ;
extern int status;
extern int line_num;
extern char *shell_name;

int command_manager(char **args);
int built_ins(char **args);
int logical_operation(char **args, char operator, int last_compare);
char *check_command(char **args);
int execute_command(char **args);
char *sanitize_input(char *old_buffer, size_t *old_size);
int input_error_check(char *ptr);
void error_message(char *arg0, char *arg1);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int get_line(char **line_ptr, size_t *n, int file);
char *check_for_variables(char *arg);
int str_length(char *str);
char *string_duplicate(char *src);
char *string_concatenate(char *s1, char *s2);
int string_compare(const char *s1, const  char *s2);
char *get_array_element(char **array, char *element_name);
char **split_string(char *str, char delim, char **if_sep);
int array_length(char **array);
char **array_copy(char **old_array);
void free_array(char **args);
int set_environment_variable(const char *name, const char *value);
int unset_environment_variable(const char *name);
int change_directory(char *name);
int alias_function(char **args, int free);
int free_aliases(Alias *alias_ptr);
int check_if_alias(char **args, Alias *alias_ptr);
int print_aliases(Alias *alias_ptr);
int print_alias_value(char *arg, Alias *alias_ptr);
int set_alias_value(char *arg, Alias *alias_ptr, char *new_value);
int print_environment(void);
char *int_to_string(int n);
int string_to_int(char *s);

#endif

