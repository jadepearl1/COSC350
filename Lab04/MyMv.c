#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[])
{
	struct stat buffer; //stat buffer
	stat(argv[2], &buffer);
	char pathway[(strlen(argv[1])) + (strlen(argv[2]))]; //create a variable that will hold the string of the directory
	if(S_ISDIR(buffer.st_mode)) //checks if the input is a directory
	{
		sprintf(pathway, "%s", argv[2]);
		sprintf(pathway, "%s/%s", pathway, argv[1]); //moves the file to the directory if the second argument is a directory
		link(argv[1], pathway);
		unlink(argv[1]);
	}
	else
    	{   
		sprintf(pathway, "%s", argv[2]);
                sprintf(pathway, "%s/%s", pathway, argv[1]); //moves the file to the directory if the second argument is a directory
		mkdir(argv[2], 0777); //creates a directory if the second argument is not a directory
                link(argv[1], pathway);
                unlink(argv[1]);
 	}
    return 0;
}
