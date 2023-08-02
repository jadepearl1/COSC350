#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
	int fd0, fd1;
	int offset;
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

	if((offset = lseek(fd0, 0, SEEK_END)) < 0)
	{
		printf("Offset error\n");
		exit(1);
	}
	for(int i=offset-1; i>=0; i--)
	{
		if((lseek(fd0, i, SEEK_SET)) < 0)
		{
			printf("Offset error\n");
			exit(1);
		}
		if((read(fd0, &buffer, 1)) < 0)
		{
			printf("Read error\n");
			exit(1);
		}
		if((write(fd1, &buffer, 1)) < 0)
		{
			printf("Write error\n");
			exit(1);
		}
	}
	
	close(fd0);
	close(fd1);

	return 0;
}
