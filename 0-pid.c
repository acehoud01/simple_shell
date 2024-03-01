#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t id = getpid();
	printf("\nProcess ID (%d)\n", id);

	return 0;
}
