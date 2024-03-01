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
