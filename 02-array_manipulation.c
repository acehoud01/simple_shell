#include "shell.h"

/**
 * array_length - calculates the length of an array of strings
 * @array: the array of strings
 *
 * Return: the length of the array
 */
int array_length(char **array)
{
    int length = 0;

    while (array[length] != NULL)
    {
        length++;
    }

    return length;
}

/**
 * array_copy - creates a copy of an array of strings
 * @old_array: the array to be copied
 *
 * Return: a newly allocated copy of the array, or NULL if memory allocation fails
 */
char **array_copy(char **old_array)
{
    int length = array_length(old_array);
    char **new_array = malloc((length + 1) * sizeof(char *));
    int i;

    if (new_array == NULL)
    {
        return NULL;
    }

    for (i = 0; i < length; i++)
    {
        new_array[i] = strdup(old_array[i]);
        if (new_array[i] == NULL)
        {
            free(new_array);
            return NULL;
        }
    }

    new_array[length] = NULL;

    return new_array;
}

/**
 * free_array - frees memory allocated for an array of strings
 * @array: the array to be freed
 */
void free_array(char **array)
{
    int i;

    for (i = 0; array[i] != NULL; i++)
    {
        free(array[i]);
    }

    free(array);
}

