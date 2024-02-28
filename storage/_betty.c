#include <stdio.h>
#include <stdlib.h>

/**
 * main - entry point
 *
 * @argc: argument count
 * @argv: arguments entered
 * Return: 0
 */

int main(int argc, char *argv[])
{
	for (int i = 0; argv[i] != NULL; i++)
		printf("%s\n", argv[i]);
	return (0);
}
