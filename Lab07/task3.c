#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	pid_t pid;
	int fd0, fd1; //making the file descriptors for foo
	char buffer;

	pid = fork();
	umask(0);
	if(pid == 0) //child process
	{
		fd0 = open("foo", O_CREAT | O_TRUNC | O_WRONLY, 0666);
		char msg[] = "Hi, Mom";
		write(fd0, &msg, 7);
	}
	else //parent process
	{
		wait(&pid);
		fd1 = open("foo", O_RDONLY);
		printf("My son said ");
		while(read(fd1, &buffer, 1) > 0)
			printf("%c", buffer);
		printf("\n");
	}
	exit(0);
}
