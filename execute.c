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
	char *fl_cmd;
	pid_t id;
	int status = 0;

	fl_cmd = _getpath(command[0]);

	if(!fl_cmd)
	{
		print_error(argv[0], command[0], idx);
		array_tools(command);
		return(127);
	}

	id = fork();
	if (id == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (id == 0)
	{
		perror("execve");
		exit(EXIT_FAILURE);
		/*if (execve(fl_cmd, command, environ) == -1)
		{
			free(fl_cmd), fl_cmd = NULL;
			array_tools(command);
		}*/
	}
	else
	{
		waitpid(id, &status, 0);
		array_tools(command);
		free(fl_cmd), fl_cmd = NULL;
		return (WEXITSTATUS(status));
	}
	/*return (WEXITSTATUS(status));*/
	return (1);
}
