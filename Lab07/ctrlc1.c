#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void ouch(int sig)
{
	//when ctrl+c is entered, this function is called
	printf("OUCH! - I got signal %d\n", sig);
	(void) signal(SIGINT, SIG_DFL);
}

int main()
{
	(void) signal(SIGINT, ouch);

	while(1){
		printf("Hello World!\n");
		sleep(1);
	}
}
