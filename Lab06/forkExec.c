#include <sys/types.h>
#include <sys/wait.h>
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
	int exit_code;

	//make variables holding iterations for child and parent process as well as sleep time
	int Nc = atoi(argv[1]); //must use atoi since the variables are integers, not characters
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
		execlp("./child", "This is the child", argv[1], argv[3]); //need to pass arguments for the child process to work properly
		perror("exec failed.");
		break;
	default: //parent process
		message = "This is the parent | ID: ";
		n = Np;
		st = Tp;
		exit_code = 0;
		break;
	}
	
	for(; n > 0; n--)
	{
		puts(message);
		sleep(st);
	}

	if(pid != 0)
	{
		int stat_val;
		pid_t child_pid;

		child_pid = wait(&stat_val);

		printf("Child has finished: PID = %d\n", child_pid);
		if(WIFEXITED(stat_val))
			printf("Child exited with code %d\n", WEXITSTATUS(stat_val));
		else
			printf("Child terminated abnormally\n");
	}
	exit(exit_code);
}
