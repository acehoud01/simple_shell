#include "shell.h"

/**
 * get_path - function to get path
 *
 * @command: environments
 * Return: 0
 */

char *_getpath(char *command)
{
	char *env, *dir, *fl_cmd;
	struct stat state;
	int i;
	
	for (i  = 0; command[i]; i++)
	{
		if (command[i] == '/')
		{
			if (stat(command, &state) == 0)
				return (_strdup(command));
			
			return (NULL);
		}
	}

	env = get_env("PATH");
	if (!env)
		return (NULL);

	dir = strtok(env, ":");

	while (dir)
	{
		fl_cmd = malloc(_strlen(dir) + _strlen(command) + 2);

		if (fl_cmd)
		{
			_strcpy(fl_cmd, dir);
			_strcat(fl_cmd, "/");
			_strcat(fl_cmd, command);

			if (stat(fl_cmd, &state) == 0)
			{
				free(env);
				return (fl_cmd);
			}
			free(fl_cmd), fl_cmd = NULL;

			dir = strtok(NULL, ":");
		}
	}
	free(env);
	return (NULL);

}
