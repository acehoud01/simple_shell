#include <stdio.h>
#include <unistd.h>

int main(int ac, char *av[])
{
	for (int i = 1; av[i] != NULL; i++)
	{
		printf("%s\n", av[i]);
	}
	return 0;
}
