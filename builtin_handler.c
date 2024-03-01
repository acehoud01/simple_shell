#include "shell.h"

/**
 * is_builtin - function to check the built ins
 *
 * @command: comand to check
 * Return: 0
 */

int is_builtin(char *command)
{
	char *builtin[] = {
		"env", "setevn", "cd", "exit",
		"pwd", NULL
	};

	int i;

	for (i = 0; builtin[i]; i++)
	{
		if (_strcmp(command, builtin[i]) == 0)
		{
			return (1);
		}
	}
	return (0);
}

/**
 * handle_builtin - funtion to handle built in
 *
 * @command: command passed
 * Return: nothing
 */

void handle_builtin(char **command, char **argv, int *status, int idx)
{
	(void)argv;
	(void)idx;

	if (_strcmp(command[0], "exit") == 0)
		exit_shell(command, status);
	else if (_strcmp(command[0], "env") == 0)
		print_env(command, status);
}

/**
 * exit_shell - function to exit the shell
 *
 * @command: command passed
 * @status: current status
 * Return: nothing
 */

void exit_shell(char **command, int *status)
{
	array_tools(command);
	exit(*status);
}

/**
 * print_env - function prototype
 *
 * @command: cmd
 * @status: cmd status
 * Return: nothing
 */

void print_env(char **command, int *status)
{
	int i;

	for (i = 0; environ[i]; i++)
	{
		me_printf(environ[i]);
		me_printf("\n");
	}
	array_tools(command);
	(*status) = 0;
}
