#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *lineptr = NULL;
	size_t len = 0;
	ssize_t nread;

	printf("$ ");
	nread = getline(&lineptr, &len, stdin);
	if (nread == -1)
	{
		printf("Reading error\n");
		return (1);
	}
	printf("%s", lineptr);

	return 0;
}
