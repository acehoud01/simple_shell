#include "shell.h"

/**
 * _execute - prototype to execute the shell system
 *
 * @command: cmd coommands
 * @argv: strings passed
 * Return: 0
 */

int _execute(char **command, char **argv, int idx)
{
	pid_t id;
	int status;
	char *cmd;

	cmd = get_path(command[0]);

	if (!cmd)
	{
		print_error(argv[0], idx, command[0]);
		array_tools(command);
		return (127);
	}

	id = fork();
	if (id == 0)
	{
		if (execve(command[0], command, environ) == -1)
		{
			array_tools(command);
			free(cmd), cmd = NULL;
		}
	}
	else
	{
		waitpid(id, &status, 0);
		array_tools(command);
		free(cmd), cmd = NULL;
	}
	return (WEXITSTATUS(status));
}
