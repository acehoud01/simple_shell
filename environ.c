#include "shell.h"

/**
 * get_env - function prototype
 *
 * @name: my environments
 * Return: 0
 */

char *get_env(char *name)
{
	int i;
	char *tmp, *var, *value, *env;
	
	for (i = 0; environ[i]; i++)
	{
		tmp = _strdup(environ[i]);
		var = strtok(tmp, "=");
		if (_strcmp(var, name) == 0)
		{
			value = strtok(NULL, "\n");
			env = _strdup(value);
			free(tmp);
			return (env);
		}
		free(tmp), tmp = NULL;
	}
	return (NULL);
}
