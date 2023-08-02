#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void par(int sig)
{
	signal(SIGQUIT, SIG_DFL); //catches SIGQUIT
}

int main()
{
	sigset_t mask1, ogMask1;
	sigset_t mask2, ogMask2; //masks and their originals to use sigprocmask call

	sigemptyset(&mask1);
	sigaddset(&mask1, SIGINT); //ties the first mask to SIGINT
	sigemptyset(&mask2);
	sigaddset(&mask2, SIGQUIT); //ties the second mask to SIGQUIT

	//block SIGINT and SIGQUIT for the first loop
	sigprocmask(SIG_BLOCK, &mask1, &ogMask1);
	sigprocmask(SIG_BLOCK, &mask2, &ogMask2);

	//for loop that prints 1-5 in one second intervals
	for(int i=0; i<5; i++)
	{
		printf("%d\n", i+1);
		sleep(1);
	}

	signal (SIGQUIT, par); //catch signals if passing through
	signal (SIGINT, par);

	sigprocmask(SIG_UNBLOCK, &mask2, &ogMask2); //unblock SIGQUIT for second loop

	sigemptyset(&mask1); //empty the signal sets, repeat what was done before first loop just blocking SIGINT
	sigaddset(&mask1, SIGINT);
	sigemptyset(&mask2);
	sigaddset(&mask2, SIGQUIT);

	sigprocmask(SIG_BLOCK, &mask1, &ogMask1); // block SIGINT only for second loop
	for(int i=0; i<5; i++) //print 1-5 in one second intervals again
	{
		printf("%d\n", i+1);
		sleep(1);
	}

	exit(0);
}


