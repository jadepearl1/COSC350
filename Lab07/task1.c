#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int alarm_fired = 0;

//signal handler for SIGALRM
void ding(int sig)
{
	alarm_fired = 1;
}

int main()
{
	pid_t pid;

	printf("alarm application starting\n");
	
	struct sigaction act;
	act.sa_handler = ding;

	pid = fork();
	switch(pid){
		case -1: //failure
			perror("fork failed");
			exit(1);
		case 0: //child
			sleep(5);
			kill(getppid(), SIGALRM);
			_exit(0);
	}

	//if we get here we are the parent process
	printf("waiting for alarm to go off\n");
	sigaction(SIGALRM, &act, NULL); //the alarm is picked up by the handler

	pause(); //pauses until signal is caught

	if(alarm_fired)
		printf("Ding!\n");

	printf("Done\n");
	exit(0);
}
