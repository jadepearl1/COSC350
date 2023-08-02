#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char *command;
	int size = 0; //size of the argument
	
	for(int i = 0; i < argc; i++)
		size += strlen(argv[i]);

	command = malloc(size*sizeof(char));

	//concatenate the arguments
	for(int i = 1; i < argc; i++)
		sprintf(command, "%s %s", command, argv[i]);

	FILE *ptr; //file pointer for popen
	char buffer[BUFSIZ];
	if((ptr = popen(command, "r")) != NULL)
	{
		while(fgets(buffer, BUFSIZ, ptr) != NULL)
			(void) printf("%s", buffer);
	}

	pclose(ptr);
	exit(0);
}
