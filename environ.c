#include "shell.h"

/**
 * get_env - function prototype
 *
 * @name: my environments
 * Return: 0
 */

char *get_env(char *name)
{
        char *key, *tmp, *env;
	int i;

	for (i = 0; environ[i]; i++)
	{
		tmp = _strdup(environ[i]);
		key = strtok(tmp, "=");
		if (_strcmp(key, name) == 0)
		{
			env = _strdup(strtok(NULL, "\n"));
			free(tmp);
			return (env);
		}
		free(tmp);
	}

	return (NULL);
} 
