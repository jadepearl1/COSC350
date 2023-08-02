#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>

void par(int sig)
{
	if(sig == SIGUSR1)
		printf("Hi Honey! Anything wrong?\n");
	else if(sig == SIGUSR2)
		printf("Do you make trouble again?\n");
}

int main()
{
	pid_t pid, pid1;
	pid = fork();
	
	if(pid == 0)
	{
		kill(getppid(), SIGUSR1); //sends the signal flag to parent 
		_exit(0);
	}
	else
	{
		pid1 = fork(); //makes a second child
		if(pid1 == 0)
		{
			kill(getppid(), SIGUSR2); //second child sends flag to parent
			exit(0);
		}
		else
		{
			signal(SIGUSR1, par);
			pause(); //suspends calling process until signal is caught
			signal(SIGUSR2, par);
			pause();
		}
	}
	return 0;
}

