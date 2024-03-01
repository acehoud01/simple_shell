#include "shell.h"

/**
 * manage_command - manages the execution of a command
 * @args: an array of strings containing the command and its arguments
 *
 * Return: TRUE if successful, FALSE otherwise
 */
int manage_command(char **args)
{
    char **args_ptr = args;
    int prev_eval = NEITHER;
    int no_err = TRUE;
    char prev_op = 'c';
    char next_op = 'c';
    int what_do;

    while (*args != NULL && prev_eval != EXIT_SHELL)
    {
        while (*args_ptr != NULL && **args_ptr != '&' && **args_ptr != '|')
        {
            args_ptr++;
        }

        if (string_compare(*args_ptr, "||") == TRUE)
        {
            *args_ptr = NULL;
            args_ptr++;
            next_op = '|';
        }
        if (string_compare(*args_ptr, "&&") == TRUE)
        {
            *args_ptr = NULL;
            args_ptr++;
            next_op = '&';
        }
        if (next_op == 'c')
        {
            break;
        }

        prev_eval = logical_operation(args, prev_op, prev_eval);
        if (prev_eval == FALSE)
        {
            no_err = FALSE;
        }
        prev_op = next_op;
        args = args_ptr;
    }

    if (next_op == 'c')
    {
        what_do = execute_command(args);

        if (what_do == EXIT_SHELL)
        {
            return EXIT_SHELL;
        }
    }

    if (no_err == FALSE || what_do == FALSE)
    {
        return FALSE;
    }

    return TRUE;
}

/**
 * check_built_ins - checks if a command is a built-in function
 * @args: an array of strings containing the command and its arguments
 *
 * Return: SKIP_FORK if it's a built-in, DO_EXECVE if not a built-in,
 *         EXIT_SHELL if exit shell, EXIT_SHELL_CODE if exiting with a particular code
 */
int check_built_ins(char **args)
{
    char **args_ptr = args;
    int i;

    while (*args_ptr != NULL)
    {
        if (**args_ptr == '#')
        {
            *args_ptr = NULL;
            break;
        }
        *args_ptr = check_variables(*args_ptr);

        args_ptr++;
    }
    if (*args == NULL)
    {
        return SKIP_FORK;
    }

    i = alias_function(args, FALSE);
    if (i == DO_EXECVE || i == SKIP_FORK)
    {
        return i;
    }

    if (string_compare("exit", *args) == TRUE && args[1] != NULL)
    {
        status = string_to_int(args[1]);
        if (status < 0)
        {
            status = 2;
            error_message(args[0], args[1]);
            return SKIP_FORK;
        }
    }
    if (string_compare("exit", *args) == TRUE)
    {
        return EXIT_SHELL;
    }
    else if (string_compare("setenv", *args) == TRUE && args[1] != NULL)
    {
        return set_environment_variable(args[1], args[2]);
    }
    else if (string_compare("unsetenv", *args) == TRUE && args[1] != NULL)
    {
        return unset_environment_variable(args[1]);
    }
    else if (string_compare("cd", *args) == TRUE)
    {
        return change_directory(args[1]);
    }
    else if (string_compare("env", *args) == TRUE)
    {
        return print_environment();
    }

    return DO_EXECVE;
}

/**
 * logical_operation - handles logical operators in command line
 * @args: an array of strings containing the command and its arguments
 * @operator: the first character of the logical operator
 * @last_compare: the result of the last command evaluation
 *
 * Return: the result of the current command evaluation
 */
int logical_operation(char **args, char operator, int last_compare)
{
    int i;

    if (last_compare == NEITHER)
    {
        i = execute_command(args);
        if (i == EXIT_SHELL)
        {
            return EXIT_SHELL;
        }
        if (i == TRUE)
        {
            return TRUE;
        }

        return FALSE;
    }
    if (last_compare == TRUE && operator == '&')
    {
        i = execute_command(args);
        if (i == EXIT_SHELL)
        {
            return EXIT_SHELL;
        }
        if (i == TRUE)
        {
            return TRUE;
        }

        return FALSE;
    }

    if (last_compare == FALSE && operator == '|')
    {
        i = execute_command(args);
        if (i == EXIT_SHELL)
        {
            return EXIT_SHELL;
        }
        if (i == TRUE)
        {
            return TRUE;
        }

        return FALSE;
    }

    if (last_compare == TRUE && operator == '|')
    {
        return TRUE;
    }

    return FALSE;
}

