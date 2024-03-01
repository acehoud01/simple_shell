#include "shell.h"

/**
 * strtkn - function prototype
 *
 * @line: string to slip
 * Return: 0
 */

char **strtkn(char *line)
{
	char *tkn = NULL, *tmp = NULL;
	char **cmd = NULL;
	int counter = 0, i = 0;

	if (!line)
		return (NULL);
	tmp = _strdup(line);

	tkn = strtok(tmp, DELIM);

	if (tkn == NULL)
	{
		free(line), line = NULL;
		free(tmp), tmp = NULL;
		return (NULL);
	}

	while (tkn)
	{
		counter++;
		tkn = strtok(NULL, DELIM);
	}
	free(tmp), tmp = NULL;

	cmd = malloc(sizeof(char *) * (counter + 1));
	if (cmd == NULL)
	{
		free(line), line = NULL;
		return (NULL);
	}
	tkn = strtok(line, DELIM);
	while (tkn)
	{
		cmd[i] = _strdup(tkn);
		tkn = strtok(NULL, DELIM);
		i++;
	}
	free(line), line = NULL;
	cmd[i] = NULL;
	return (cmd);
}
