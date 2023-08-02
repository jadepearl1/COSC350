//This program takes a string of up to 80 characters, finds any embedded numbers,
//converts that part of the string into an integer, adds 10 to that integer, and
//converts it back into a string without use of library functions
//use system call to write to standard output (file descriptor 1)
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

//function to convert string to integer
int atoInt(char *str)
{
	int result = 0;
	int i; //loop iterator
	for(i = 0; str[i] != '\0'; i++)
		result = (result*10) + (str[i] - 48);
	return result;
}

//function to convert integer into string
int intToStr(char *str, int n)
{
	sprintf(str, "%d", n);
	return (strlen(str));
}

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("Need EXACTLY one command argument.\n");
		exit(1);
	}

	int fd0 = open(argv[1], O_RDONLY);
	char c[80];
	char buffer;
	int num = 0; //holds the number found in the string
	int i; //loop iterator and index counter for c

	//lseek to end of file
	int offset = lseek(fd0, 0, SEEK_END);
	//lseek to beginning of file
	lseek(fd0, 0, SEEK_SET);
	while(read(fd0, &buffer, 1) > 0)
	{
		if((int)buffer >= 48 && (int)buffer <= 57)
		{
			c[i] = buffer;
			i++;
		}
	}
	num = atoInt(c);
	num += 10;
	intToStr(c, num);
	write(1, c, i);
	return 0;
}
