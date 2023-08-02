#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
	if(argc != 5)
	{
		printf("Please provide 4 integer arguments!\n");
		exit(1);
	}

	pid_t pid; //process ID
	char *message; //stores a message that will be printed by the child and parent processes
	int n, st; //counter variables for number of times messages will print (n) and sleep time value (st)

	//make variables holding iterations for child and parent process as well as sleep time
	int Nc = atoi(argv[1]);
	int Np = atoi(argv[2]);
	int Tc = atoi(argv[3]);
	int Tp = atoi(argv[4]);

	printf("fork program starting\n");
	pid = fork();

	switch(pid)
	{
		case -1:
		//fork system call is unsuccessful
		perror("fork failed");
		exit(1);
	case 0: //child process
		message = "This is the child";
		n = Nc;
		st = Tc;
		break;
	default: //parent process
		message = "This is the parent";
		n = Np;
		st = Tp;
		break;
	}
	
	for(; n > 0; n--)
	{
		puts(message);
		sleep(st);
	}
	exit(0);
}
