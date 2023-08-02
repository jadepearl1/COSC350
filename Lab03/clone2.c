#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
	int fd0, fd1;
	char buffer;

	if((fd0 = open("foo", O_RDWR)) < 0)
	{
		printf("Error opening input file\n");
		exit(1);
	}

	umask(0);
	if((fd1 = open("clone1", O_RDWR | O_CREAT | O_EXCL, 0666)) < 0)
	{
		printf("Error opening output file\n");
		exit(1);
	}

	if(fd1 != -1)
	{
		while((read(fd0, &buffer, 1)) > 0)
			write(fd1, &buffer, 1);
	}
	
	close(fd0);
	close(fd1);

	return 0;
}
