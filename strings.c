#include "shell.h"

/**
 * _strdup - function to
 *
 * @str: pointer to char
 * Return: 0
 */

char *_strdup(const char *str)
{
	char *ptr;
	int i, len = 0;

	if (str == NULL)
		return (NULL);
	while (*str != '\0')
	{
		len++;
		str++;
	}
	str = str - len;
	ptr = malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	for (i = 0; i <= len; i++)
		ptr[i] = str[i];
	return (ptr);
}

/**
 * _strcmp - function to compare strings
 *
 * @s1: string to compare
 * @s2: second argument to compare
 * Return: 0
 */

int _strcmp(char *s1, char *s2)
{
	int comp;

	comp = (int)*s1 - (int)*s2;
	while (*s1)
	{
		if (*s1 != *s2)
			break;
		s1++;
		s2++;
		comp = (int)*s1 - (int)*s2;
	}
	return (comp);
}

/**
 * _strlen - function for string length
 *
 * @s: string
 * Return: 0
 */

int _strlen(char *s)
{
	int len = 0;

	while (s[len])
		len++;
	return (len);
}

/**
 * _strcat - func to conta strings
 *
 * @dest: destination
 * @src: source
 * Return: 0
 */

char *_strcat(char *dest, char *src)
{
	char *ptr = dest;

	while (*ptr)
		ptr++;

	while (*src)
	{
		*ptr = *src;
		ptr++;
		src++;
	}
	*ptr = *src;
	return (dest);
}

/**
 * _strcpy - function to copy a string
 *
 * @dest: destination
 * @src: source
 * Return: 0
 */

char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
