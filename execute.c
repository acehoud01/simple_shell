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
	char *cmd;
	(void)idx;

	cmd = get_path(command[0]);

	if (!cmd)
	{
		perror("Command does not exist");
		array_tools(command);
		exit(EXIT_FAILURE);
	}

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
