#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAXLINE 256

int main(void)
{
	int n, fd[2]; //file descriptors and loop counters
	char line[MAXLINE];
	pid_t pid;
	//pipe
	if(pipe(fd) < 0)
	{
		perror("Pipe error");
		exit(1);
	}
	if((pid = fork()) < 0)
	{
		perror("fork error");
		exit(1);
	}
	if(pid == 0)
	{
		close(fd[1]);
		int num1, num2; //variables to hold two integers from the parent process
		while((n = read(fd[0], line, MAXLINE)) > 0)
		{
			//read in a string from the command line
			if(sscanf(line, "%d%d", &num1, &num2) == 2)
			{
				//find the sum of the integers within the string
				sprintf(line, "The sum of integers is: %d\n", num1+num2);
				n = strlen(line);
				if(write(0, line, n) != n)
				{
					perror("write error");
					exit(1);
				}
			}
			else
			{
				//argument input validation
				if(write(0, "invalid arguments\n", 18) != 18)
				{
					perror("write error");
					exit(1);
				}
			}
		}
	}
	else //parent process
	{
		close(fd[0]);
		int i;
		printf("Enter two integers\n");
		//scan for input from the keyboard
		while(fgets(line, MAXLINE, stdin) != NULL)
		{
			n = strlen(line); //buffer comes from the strlen of the command line

			if(write(fd[1], line, n) != n)
			{
				perror("write error");
				exit(1);
			}
		}
	}
	exit(0);
}
