#include <stdio.h>
#include <stdlib.h>

int main()
{
        char *lineptr = NULL;
        size_t len = 0;
	ssize_t nread;

	printf("$ ");
	while ((nread = getline(&lineptr, &len, stdin)) != -1)
	{
		printf("%s", lineptr);
		printf("$ ");
	}

        return 0;
}

