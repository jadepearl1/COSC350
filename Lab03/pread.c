#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
	int fd0, fd1;
	int nread;
	int rOffset;
	int wOffset = 0;
	char buffer; //buffers for both files

	if((fd0 = open("foo", O_RDWR)) < 0)
	{
		printf("Error opening input file\n");
		exit(1);
	}

	umask(0); //clear mask
	if((fd1 = open("foorev", O_RDWR | O_CREAT | O_TRUNC, 0760)) < 0)
	{
		printf("Error opening output file\n");
		exit(1);
	}

	if((rOffset = lseek(fd0, 0, SEEK_END)) < 0) //sets offset to length of file
	{
		printf("Offset error\n");
		exit(1);
	}
	while(rOffset > 0)
	{
		if((nread = pread(fd0, &buffer, 1, rOffset-1)) < 0)
		{
			printf("Pread error\n");
			exit(1);
		}
		if((nread = pwrite(fd1, &buffer, 1, wOffset)) < 0)
		{
			printf("Pwrite error\n");
			exit(1);
		}
		rOffset--;
		wOffset++;
	}
	
	close(fd0);
	close(fd1);

	return 0;
}
