#include "shell.h"

/**
 * array_tools - function prototype
 *
 * @arr: array
 * Return: nothing
 */

void array_tools(char **arr)
{
	int i;

	if (!arr)
		return;

	for (i = 0; arr[i]; i++)
	{
		free(arr[i]);
		arr[i] = NULL;
	}

	free(arr), arr = NULL;
}

/**
 * print_error - function that print error
 *
 * @name: the name of shell
 * @idx: command index
 * @cmd: command
 * Return: nothing
 */

void print_error(char *name, int idx, char *cmd)
{
	char *index, msg[] = ": not found\n";

	index = _itoa(idx);

	me_printf(name);
	me_printf(": ");
	me_printf(index);
	me_printf(": ");
	me_printf(cmd);
	me_printf(msg);
	free(index);
}
