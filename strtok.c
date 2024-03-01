#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	char *str =  malloc(12);

	if (str == NULL)
		return (-1);

	strcpy(str, "Hello Wolrd");
	
	for (int i = 0; i != 12; ++i)
	{
		printf("%d  |  ", str[i]);
	}
	printf("\n");
	strtok(str, " ");
	        for (int i = 0; i != 12; ++i)
        {
                printf("%d  |  ", str[i]);
        }
	return 0;
}
