#include "shell.h"

/**
 * read_line - reads a line of input from the standard input
 *
 * Return: a pointer to the input line, or NULL on failure or EOF
 */
char *read_line(void)
{
    char *line = NULL;
    size_t bufsize = 0;
    ssize_t bytes_read;

    bytes_read = getline(&line, &bufsize, stdin);

    if (bytes_read == -1)
    {
        if (feof(stdin))
        {
            return NULL;
        }
        perror("getline");
        exit(EXIT_FAILURE);
    }

    if (bytes_read > 0 && line[bytes_read - 1] == '\n')
    {
        line[bytes_read - 1] = '\0';
    }

    return line;
}

/**
 * tokenize_line - tokenizes a line of input into an array of strings
 * @line: the input line to tokenize
 *
 * Return: an array of strings representing the tokens, or NULL on failure
 */
char **tokenize_line(char *line)
{
    const char *delimiters = " \t\r\n\a";
    int bufsize = TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, delimiters);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, delimiters);
    }
    tokens[position] = NULL;
    return tokens;
}
