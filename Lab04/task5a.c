//This program creates directories Dir1, Dir2, Dir21 (under Dir2)
//And takes an executable file hello, using system calls to copy it under Dir2/Dir21
//this program also demonstrates the use of symbolic links

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
	//make directories Dir1, Dir2, Dir21
	int d1 = mkdir("/mnt/c/Users/jpmd1/Desktop/COSC350/Labs/Lab04/Dir1", 0755);
	int d2 = mkdir("/mnt/c/Users/jpmd1/Desktop/COSC350/Labs/Lab04/Dir2", 0755);
	int d21 = mkdir("/mnt/c/Users/jpmd1/Desktop/COSC350/Labs/Lab04/Dir2/Dir21", 0755);

	int fd0, fd1; //input and output file descriptors
	char buffer;
	//open the files
	if((fd0 = open("hello", O_RDONLY, S_IRUSR)) < 0)
	{
		printf("Error opening hello executable file.\n");
		exit(1);
	}
	umask(0);
	if((fd1 = open("/mnt/c/Users/jpmd1/Desktop/COSC350/Labs/Lab04/Dir2/Dir21/hello", O_CREAT | O_WRONLY, 0777)) < 0)
	{
		printf("Error opening hello file under Dir21.\n");
		exit(1);
	}
	//copy the contents of hello to the directory Dir2/Dir21
	while((read(fd0, &buffer, 1)) > 0)
		write(fd1, &buffer, 0);

	//create symbolic links
	symlink("/mnt/c/Users/jpmd1/Desktop/COSC350/Labs/Lab04/Dir2/Dir21","/mnt/c/Users/jpmd1/Desktop/COSC350/Labs/Lab04/Dir1/toDir21");
	symlink("/mnt/c/Users/jpmd1/Desktop/COSC350/Labs/Lab04/Dir2/Dir21/hello","/mnt/c/Users/jpmd1/Desktop/COSC350/Labs/Lab04/Dir1/toHello");

	//close files
	close(fd0);
	close(fd1);
	return 0;
}

