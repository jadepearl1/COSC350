#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	char buffer;
	while(read(0, &buffer, 1) > 0)
		if(write(1, &buffer, 1) < 0)
		{
			printf("Write error!");
			exit(1);
		}
	exit (0);
}
