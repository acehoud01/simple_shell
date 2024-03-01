#include "shell.h"

int status = 0;

int line_num = 1;

char *shell_name = NULL;

/**
 * main - executes commands from the terminal
 * @argc: number of inputs from main
 * @argv: array of inputs from main
 *
 * Return: 0, or another number if desired
 */
int main(__attribute__((unused))int argc, char **argv)
{
    int bytes_read;
    int is_separated = FALSE;
    int i;
    size_t buf_size = 1;
    char *buf = NULL;
    char *buf_ptr;
    char *buf_tmp;
    char **args = NULL;

    shell_name = string_duplicate(*argv);

    environ = array_copy(environ);

    signal(SIGINT, SIG_IGN);

    buf = malloc(1);
    if (buf == NULL)
        exit(EXIT_FAILURE);

    while (TRUE)
    {
        if (is_separated == FALSE)
        {
            if (isatty(STDIN_FILENO) == 1)
                write(STDOUT_FILENO, "my_shell$ ", 10);

            bytes_read = get_line(&buf, &buf_size, stdin);

            if (bytes_read == -1)
                break;
            if (bytes_read == 1)
            {
                line_num++;
                continue;
            }
            buf[bytes_read - 1] = '\0';
            buf = sanitize_input(buf, &buf_size);
            if (buf_size == 0)
            {
                line_num++;
                continue;
            }
            buf_ptr = buf;
        }
        else
            buf_ptr = buf_tmp;

        buf_tmp = NULL;
        args = split_string(buf_ptr, ' ', &buf_tmp);
        if (buf_tmp != NULL)
            is_separated = TRUE;
        else
            is_separated = FALSE;

        i = command_manager(args);

        free(args);

        if (is_separated == FALSE)
            line_num++;

        if (i == EXIT_SHELL)
            break;
    }
    free(buf);
    alias_function(NULL, TRUE);
    free_array(environ);
    free(shell_name);

    return (status % 256);
}

