#include "shell.h"

/**
 * read_line - function to read line from stdin
 *
 * Return: line
 */

char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t size;

	if (isatty(STDIN_FILENO))
		me_printf("$ ");
	size = getline(&line, &len, stdin);

	if (size == -1)
	{
		free(line);
		return (NULL);
	}

	return (line);
}
