#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
	int foo, foo1, foo12;
	int offset
	char b1; //buffers for both files
	char b2;

	if((foo = open("foo", O_RDWR)) < 0)
	{
		printf("Error opening input file\n");
		exit(1);
	}
	if((foo1 = open("foo1", O_RDWR)) < 0)
        {
                printf("Error opening input file\n");
                exit(1);
        }

	umask(0); //clear mask
	if((fd1 = open("foo12", O_RDWR | O_CREAT | O_TRUNC, 0760)) < 0)
	{
		printf("Error opening output file\n");
		exit(1);
	}

	if(foo != -1 && foo1 != -1)
	{
		while((read(foo, &b1, 1)) > 0)
			write(foo12, &b1, 1);
		if((offset = lseek(foo12, 0, SEEK_CUR)) < 0)
		{
			printf("Offset error\n");
			exit(1);
		}
		while((read(foo1, &b2, 1)) > 0)
			write(foo12, &b2, 1);
		if((offset = lseek(foo12, 0, SEEK_CUR)) < 0)
		{
			printf("Offset error\n");
			exit(1);
		}
	}
	else
	{
		printf("Error appending file\n");
		exit(1);
	}
	
	close(foo);
	close(foo1);
	close(foo12);

	return 0;
}
