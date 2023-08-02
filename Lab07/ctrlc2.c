#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

void ouch(int sig)
{
	printf("OUCH! - I got signal %d\n", sig);
}

int main()
{
	pid_t pid;
	pid = fork();
	struct sigaction act;
	
	act.sa_handler = ouch;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESETHAND;

	sigaction(SIGINT, &act, 0);

	while(1){
		printf("Hello World!\n");
		sleep(1);
	}
}