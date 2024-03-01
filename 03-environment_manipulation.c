#include "shell.h"

/**
 * get_env_variable - retrieves the value of an environment variable
 * @name: the name of the environment variable
 *
 * Return: the value of the environment variable, or NULL if not found
 */
char *get_env_variable(const char *name)
{
    char **ptr = environ;
    char *env_value = NULL;

    while (*ptr != NULL)
    {
        if (string_compare(*ptr, name))
        {
            env_value = *ptr + str_length(name) + 1;
            break;
        }
        ptr++;
    }

    return env_value;
}

/**
 * set_env_variable - sets the value of an environment variable
 * @name: the name of the environment variable
 * @value: the value to set
 *
 * Return: 0 on success, -1 on failure
 */
int set_env_variable(const char *name, const char *value)
{
    int i;
    int len = array_length(environ);
    char **new_environ = malloc((len + 2) * sizeof(char *));
    char *env_entry;

    if (new_environ == NULL)
    {
        return -1;
    }

    for (i = 0; i < len; i++)
    {
        new_environ[i] = strdup(environ[i]);
        if (new_environ[i] == NULL)
        {
            free_env_array(new_environ);
            return -1;
        }
    }

    env_entry = string_concatenate((char *)name, "=");
    new_environ[i] = string_concatenate(env_entry, (char *)value);
    new_environ[i + 1] = NULL;

    free(env_entry);
    free_env_array(environ);

    environ = new_environ;

    return 0;
}

/**
 * unset_env_variable - removes an environment variable
 * @name: the name of the environment variable to remove
 *
 * Return: 0 on success, -1 if variable not found
 */
int unset_env_variable(const char *name)
{
    int i, j;
    int found = 0;
    int len = array_length(environ);
    char **new_environ = malloc(len * sizeof(char *));

    if (new_environ == NULL)
    {
        return -1;
    }

    for (i = 0, j = 0; i < len; i++)
    {
        if (string_compare(environ[i], name))
        {
            found = 1;
            continue;
        }

        new_environ[j] = strdup(environ[i]);
        if (new_environ[j] == NULL)
        {
            free_env_array(new_environ);
            return -1;
        }

        j++;
    }

    new_environ[j] = NULL;

    free_env_array(environ);

    if (!found)
    {
        free_env_array(new_environ);
        return -1;
    }

    environ = new_environ;

    return 0;
}
