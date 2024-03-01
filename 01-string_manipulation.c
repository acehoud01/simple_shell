#include "shell.h"

/**
 * str_length - calculates the length of a string
 * @str: the string to calculate its length
 *
 * Return: the length of the string
 */
int str_length(char *str)
{
    int length = 0;

    while (str[length] != '\0')
    {
        length++;
    }

    return length;
}

/**
 * string_concatenate - concatenates two strings
 * @str1: the first string
 * @str2: the second string
 *
 * Return: a newly allocated string containing the concatenation
 *         of str1 and str2, or NULL if memory allocation fails
 */
char *string_concatenate(char *str1, char *str2)
{
    int len1 = str_length(str1);
    int len2 = str_length(str2);
    int total_len = len1 + len2 + 1;
    char *result = malloc(total_len);
    int i, j;

    if (result == NULL)
    {
        return NULL;
    }

    for (i = 0; i < len1; i++)
    {
        result[i] = str1[i];
    }

    for (j = 0; j < len2; j++)
    {
        result[i + j] = str2[j];
    }

    result[i + j] = '\0';

    return result;
}

/**
 * string_compare - compares two strings
 * @str1: the first string
 * @str2: the second string
 *
 * Return: 1 if the strings are equal, 0 otherwise
 */
int string_compare(char *str1, char *str2)
{
    while (*str1 && *str2)
    {
        if (*str1 != *str2)
        {
            return 0;
        }
        str1++;
        str2++;
    }

    return (*str1 == '\0' && *str2 == '\0');
}

