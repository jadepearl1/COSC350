#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

//function for testing if a character is a number or not. Returns 1 if numeric and 0 if not
int isNum(char str)
{
	if(str >= '0' && str <= '9')
		return 1;
	else
		return 0;
}

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Please include the name of an input file.\n");
		exit(0);
	}

	int input; //file descriptor for the input file
	//open input file
	if((input = open(argv[1], O_RDONLY)) < 0)
	{
		perror("Error opening input file");
		exit(1);
	}
	//create the output files
	int parent, child; //file descriptors for parent and child processes
	char buffer; //create the buffer
	int pOffset = 0;
	int cOffset = 0;
	int exit_code;

	if((parent = open("parent.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777)) < 0)
	{
		perror("Error creating or opening parent output");
		exit(1);
	}
	if((child = open("child.txt", O_WRONLY | O_CREAT | O_APPEND, 0777)) < 0)
	{
		perror("Error creating or opening child output");
		exit(1);
	}

	//create the child process
	pid_t pid = fork();

	switch(pid)
	{
		case -1:
			perror("fork error.");
			exit(1);
		case 0:
			exit_code = 37;
			while(pread(input, &buffer, 1, cOffset) == 1)
			{
				if(isNum(buffer) == 0)
					write(child, &buffer, 1);
				cOffset++;
			}
			break;
		default:
			exit_code = 0;
			while(pread(input, &buffer, 1, pOffset) == 1)
			{
				if(isNum(buffer) == 1)
					write(parent, &buffer, 1);
				pOffset++;
			}
			break;
	}
	close(input);
	exit(exit_code);
}
