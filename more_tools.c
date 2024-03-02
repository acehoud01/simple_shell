#include "shell.h"

/**
 * reverse_string - a function that reverse string
 *
 * @str: string to reverse
 * @len: the length of the string
 * Return: nothing
*/
void reverse_string(char *str, int len)
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

/**
 * _itoa - convert an integer to string
 *
 * @n: the integer
 * Return: 0
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
	reverse_string(buffer, i);

	return (_strdup(buffer));
}

/**
 * print_error - a function that prints command not found error
 * 
 * @name: shell name
 * @idx: the command index
 * @cmd: the command
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
