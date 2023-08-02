//This program includes a function int palind(int fd1, int fd2) that takes two
//files already opened in the same file and uses lseek to scan the file, returning
//1 if there is a palindrome. Also contains a main function taht tests the
//palindrome function

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int palind(int fd1, int fd2)
{
	//make a buffer for each file
	char fd1Buff[1];
	char fd2Buff[1];
	//create offsets for lseek
	int off1 = lseek(fd1, 0, SEEK_SET);
	int off2 = lseek(fd2, -2, SEEK_END);
	int mid = (off2/2)+1;
	//make a loop to read while the offset is not in the middle position
	while(off1 != mid)
	{
		if(read(fd1, &fd1Buff, 1) < 0)
		{
			printf("Read error!\n");
			exit(1);
		}
		if(read(fd2, &fd2Buff, 1) < 0)
		{
			printf("Read error!\n");
			exit(1);
		}
		//compare the buffers. If not equal the file is not a palindrome
		if(fd1Buff[0] != fd2Buff[0])
			return 0; //not a palindrome
		lseek(fd2, -2, SEEK_CUR);
		off1++;
	}
	return 1; //file is a palindrome
}

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Must pass exactly one file argument.\n");
		exit(1);
	}

	int fd1, fd2; //file descriptors
	if((fd1 = open(argv[1], O_RDONLY)) < 0)
	{
		printf("Error opening file.\n");
		exit(1);
	}
	//open same file with different file descriptor
	if((fd2 = open(argv[1], O_RDONLY)) < 0)
	{
		printf("Error opening file.\n");
		exit(1);
	}
	int isPalind = palind(fd1, fd2);
	if(isPalind == 1)
		printf("File is a palindrome!\n");
	else if (isPalind == 0)
		printf("File is not a palindrome!\n");
	//close file
	close(fd1);
	close(fd2);
	return 0;
}
