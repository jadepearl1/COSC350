//This task is meant to take the output files from task 1 and use them as input files
//to reverse what was done in task 1. Using the contents of each file to write a file called origin

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//error message function
void err_sys(char *str)
{
	printf("%s", str);
	exit(1);
}

int main(int argc, char *argv[])
{
	//argument validation
	if(argc != 5)
		err_sys("Include exactly 4 file names!");

	umask(0); //clear mask
	int a, n, o, r; //file descriptors for alpha, num, other, and origin

	//open the files and create the output file if it does not exist
	if((a = open(argv[1], O_RDWR)) < 0)
		err_sys("Error opening alpha file.");
	if((n = open(argv[2], O_RDWR)) < 0)
		err_sys("Error opening num file.");
	if((o = open(argv[3], O_RDWR)) < 0)
		err_sys("Error opening other file.");
	if((r = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0777)) < 0) //rwxrwxrwx
		err_sys("Error opening origin file.");

	char aBuffer, nBuffer, oBuffer; //make a buffer for each file
	//all files from last task should be same size so lseek one of them
	int offset = lseek(a, 0, SEEK_END);
	//move lseek back to beginning of alpha file or it will not read/write input properly
	lseek(a, 0, SEEK_SET);
	//read input files and write to output file
	int i; //loop iterator
	while(i < offset)
	{
		read(a, &aBuffer, 1);
		read(n, &nBuffer, 1);
		read(o, &oBuffer, 1);

		//write all whitespaces and new lines to the output file
		if(aBuffer == ' ' && nBuffer == ' ' && oBuffer == ' ')
			write(r, " ", 1);
		else if(aBuffer == '\n' && nBuffer == '\n' && oBuffer == '\n')
			write(r, "\n", 1);
		else
		{
			if(aBuffer != ' ')
				write(r, &aBuffer, 1);
			if(nBuffer != ' ')
				write(r, &nBuffer, 1);
			if(oBuffer != ' ')
				write(r, &oBuffer, 1);
		}
		i++;
	}

	//close the files!
	close(a);
	close(n);
	close(o);
	close(r);

	return 0;
}

