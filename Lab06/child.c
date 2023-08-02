#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		printf("Please provide two integer arguments.\n");
		exit(1);
	}

	int Nc = atoi(argv[1]);
	int Tc = atoi(argv[2]);
	int n = Nc;

	pid_t pid = getpid();
	char *message = argv[0];

	for(; n > 0; n--)
	{
		puts(message);
		sleep(Tc);
	}
	exit(37);
}
