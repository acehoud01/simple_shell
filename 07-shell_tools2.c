#include "shell.h"

/**
 * sanitize_input - sanitizes input from the command line
 * @old_buffer: buffer to be sanitized
 * @old_size: size of old buffer
 *
 * Return: the new, sanitized buffer
 */
char *sanitize_input(char *old_buffer, size_t *old_size)
{
    char *new_buffer = malloc(*old_size * 3);
    char *new_ptr = new_buffer;
    char *old_ptr = old_buffer;

    while (*old_ptr != '\0')
    {
        while (*old_ptr == ' ')
            old_ptr++;
        while (*old_ptr != ' ' && *old_ptr != ';' && *old_ptr != '|' && *old_ptr != '&' && *old_ptr != '\0')
        {
            *new_ptr = *old_ptr;
            new_ptr++;
            old_ptr++;
        }
        while (*old_ptr == ' ')
            old_ptr++;
        if (new_ptr != new_buffer && *old_ptr != '\0')
        {
            *new_ptr = ' ';
            new_ptr++;
        }

        if (*old_ptr == ';' || *old_ptr == '|' || *old_ptr == '&')
        {
            if (input_error_check(old_ptr) == FALSE)
            {
                *old_size = 0;
                break;
            }
            *new_ptr = *old_ptr;
            if (*old_ptr == ';')
            {
                new_ptr++;
                *new_ptr = ' ';
            }
            else if (*(old_ptr + 1) == *old_ptr)
            {
                if (new_ptr == new_buffer)
                {
                    error_message(old_ptr, NULL);
                    *old_size = 0;
                    break;
                }
                new_ptr++;
                *new_ptr = *old_ptr;
                new_ptr++;
                *new_ptr = ' ';
                old_ptr++;
            }
            new_ptr++;
            old_ptr++;
        }
    }
    *new_ptr = '\0';
    free(old_buffer);
    return new_buffer;
}

/**
 * input_error_check - helper function for sanitizer, check for unexpected char
 * @pointer: pointer to area that needs to be checked
 *
 * Return: TRUE if no error, FALSE if error
 */
int input_error_check(char *pointer)
{
    char *iter = pointer;

    iter++;
    if (*pointer == ';' && *iter == *pointer)
    {
        error_message(pointer, NULL);
        return FALSE;
    }
    if (*iter == *pointer)
        iter++;

    while (*iter == ' ')
        iter++;

    if (*iter == ';' || *iter == '|' || *iter == '&')
    {
        error_message(iter, NULL);
        return FALSE;
    }

    return TRUE;
}

/**
 * error_message - prints error messages and sets status
 * @arg0: command that is causing error
 * @arg1: first argument to command
 */
void error_message(char *arg0, char *arg1)
{
    char *err_str_num = int_to_string(line_num);

    write(STDERR_FILENO, shell_name, str_length(shell_name));
    write(STDERR_FILENO, ": ", 2);
    write(STDERR_FILENO, err_str_num, str_length(err_str_num));
    free(err_str_num);

    if (string_compare("cd", arg0) == TRUE)
    {
        status = 2;
        write(STDERR_FILENO, ": cd: can't cd to", 17);
        write(STDERR_FILENO, arg1, str_length(arg1));
        write(STDERR_FILENO, "\n", 1);
        return;
    }

    if (string_compare("exit", arg0) == TRUE)
    {
        write(STDERR_FILENO, ": exit: Illegal number: ", 24);
        write(STDERR_FILENO, arg1, str_length(arg1));
        write(STDERR_FILENO, "\n", 1);
        return;
    }
    if (*arg0 == ';' || *arg0 == '|' || *arg0 == '&')
    {
        status = 2;
        write(STDERR_FILENO, ": Syntax error: \"", 17);
        write(STDERR_FILENO, arg0, 1);
        if (*arg0 == *(arg0 + 1))
            write(STDERR_FILENO, arg0, 1);
        write(STDERR_FILENO, "\" unexpected\n", 14);
        return;
    }

    status = 127;
    write(STDERR_FILENO, ": ", 2);
    write(STDERR_FILENO, arg0, str_length(arg0));
    write(STDERR_FILENO, ": not found\n", 12);
}

/**
 * check_for_variables - checks an argument to see if it is a variable and if so,
 * replaces it with its value
 * @arg: argument to be checked
 *
 * Return: a pointer to the evaluated argument (either new or an altered clone)
 */
char *check_for_variables(char *arg)
{
    char *clone = NULL;
    char *ptr = arg;
    char *next;
    char *tmp;
    int is_variable;
    int i;

    while (*ptr != '\0')
    {
        if (*ptr == '$')
        {
            if (clone == NULL)
            {
                clone = string_duplicate(arg);
                i = ptr - arg;
                ptr = clone + i;
            }
            next = ptr + 1;
            while (*next != '\0' && *next != '$' && *next != '#')
                next++;
            if (*next == '$' && next > ptr + 1)
                is_variable = TRUE;
            else if (*next == '#')
                is_variable = NEITHER;
            else
                is_variable = FALSE;

            *next = '\0';

            if (string_compare("$?", ptr) == TRUE)
                tmp = int_to_string(status);
            else if (string_compare("$0", ptr) == TRUE)
                tmp = string_duplicate(shell_name);
            else if (get_array_element(environ, ptr + 1) != NULL)
                tmp = string_duplicate(get_array_element(environ, ptr + 1) + str_length(ptr));
            else
                tmp = string_duplicate("");

            *ptr = '\0';
            ptr = string_concatenate(clone, tmp);
            free(tmp);
            if (is_variable == FALSE)
            {
                free(clone);
                clone = ptr;
                break;
            }
            if (is_variable == TRUE)
                *next = '$';
            else if (is_variable == NEITHER)
                *next = '#';
            tmp = string_concatenate(ptr, next);
            free(ptr);
            ptr = tmp;
            free(clone);
            clone = ptr;
            if (is_variable == NEITHER)
            {
                while (*ptr != '#')
                    ptr++;
            }
        }
        ptr++;
    }
    if (clone != NULL)
        return clone;

    return arg;
}

