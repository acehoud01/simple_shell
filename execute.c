#include "shell.h"

/**
 * _execute - prototype to execute the shell system
 *
 * @command: cmd coommands
 * @argv: strings passed
 * Return: 0
 */

int _execute(char **command, char **argv)
{
	pid_t id;
	int status;

	id = fork();
	if (id == 0)
	{
		if (execve(command[0], command, environ) == -1)
		{
			perror(argv[0]);
			array_tools(command);
		}
	}
	else
	{
		waitpid(id, &status, 0);
		array_tools(command);
	}
	return (WEXITSTATUS(status));
}
