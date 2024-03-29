#include "shell.h"

/**
 * _execute - prototype to execute the shell system
 *
 * @command: cmd coommands
 * @argv: strings passed
 * @idx: index
 * Return: 0
 */

int _execute(char **command, char **argv, int idx)
{
	pid_t id;
	int status;
	(void)idx;

	id = fork();
	if (id == 0)
	{
		if (execve(command[0], command, environ) == -1)
		{
			perror(argv[0]);
			array_tools(command);
			exit(0);
		}
	}
	else
	{
		waitpid(id, &status, 0);
		array_tools(command);
	}
	return (WEXITSTATUS(status));
}
