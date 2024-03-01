#include "shell.h"

/**
 * me_printf - simply printf function
 *
 * @output: std output
 * Return: nothing
 */

void me_printf(const char *output)
{
	write(STDOUT_FILENO, output, strlen(output));
}
