#include "shell.h"

/**
 * main - entry point
 *
 * @argc: argument count
 * @argv: passed arguments
 * Return: 0
 */

int main(int argc, char **argv)
{
	char *input = NULL;
	char **prompt = NULL;
	int status = 0;
	(void)argc;

	while (1)
	{
		input = read_line();
		if (input == NULL)
		{
			if (isatty(STDIN_FILENO))
				me_printf("\n");
			return (status);
		}
		prompt = strtkn(input);

		if (!prompt)
			continue;
		status = _execute(prompt, argv);
	}

	return (0);
}
