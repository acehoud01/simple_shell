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
 * printerror - function to print error
 *
 * Return: nothing
 */

void print_error(char *name, char *cmd, int idx)
{
	char *index, message[] = ": not found\n";

	index = _itoa(idx);
	
	me_printf(name);
	me_printf(": ");
	me_printf(index);
	me_printf(": ");
	me_printf(cmd);
	me_printf(message);

	free(index);
}

/**
 * _itoa - function
 *
 * @n: number
 * Return: 0;
 */

char *_itoa(int n)
{
	char buffer[20];
	int i = 0;

	if (n == 0)
		buffer[i++] = '0';
	else
	{
		while (n > 0)
		{
			buffer[i++] = (n % 10) + '0';
			n /= 10;
		}
	}

	buffer[i] = '\0';
	reverse_str(buffer, i);

	return (_strdup(buffer));
}

/**
 * reverse_str - function reverse a string
 *
 * @str: actual string
 * @len: string length
 * Return: nothing
 */

void reverse_str(char *str, int len)
{
	char tmp;
	int start = 0;
	int end = len - 1;

	while (start < end)
	{
		tmp = str[start];
		str[start] = str[end];
		str[end] = tmp;
		start++;
		end--;
	}
}
