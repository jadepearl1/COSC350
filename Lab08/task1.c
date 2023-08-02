#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *sumThread(void *arg)
{
	int sum = 0;
	int num = atoi(arg);
	for(int i = 1; i <= num; i++)
		sum += i;
	printf("The sum is %d\n", sum);
	pthread_exit(NULL);
}

void *factThread(void *arg)
{
	int fact = 1;
	int num = atoi(arg);
	for(int i = 1; i <= num; i++)
		fact = fact * i;
	printf("The factorial is %d\n", fact);
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Please provide one integer argument.\n");
		exit(1);
	}

	pthread_t sum, fact;

	pthread_create(&sum, NULL, sumThread, (void*) argv[1]); //create a sum and factorial thread
	pthread_create(&fact, NULL, factThread, (void*) argv[1]);

	pthread_exit(NULL);

	exit(0);
}
