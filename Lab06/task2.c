#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <utmp.h>

//function to open utmp file
int openUtmpFile()
{
	//utmp file descriptor is defined for return
	int ufd;
	//open utmp file
	//I am using WSL (Window's Subsystem for Linux) so the utmp file was not located in the default
	//var/run/utmp directory but the /usr/include/utmp.h directory
	if((ufd = open("/usr/include/utmp.h", O_RDONLY)) == -1)
	{
		printf("Error opening utmp file.\n");
		exit(1);
	}

	//return the file descriptor
	return ufd;
}

//check if the openUtmpFile works
int main()
{
	int ufd; //utmp file descriptor
	//call the function
	ufd = openUtmpFile();
	printf("File descriptor for utmp file is %d\n", ufd);

	//Read each record in the utmp file. Do this by first declaring a buffer to help read through the file
	struct utmp buffer;
	//loop through the file and print out the user name for each record
	int numLogs = 0; //counts the number of logged-in users/USER_PROCESS found
	while(read(ufd, &buffer, sizeof(buffer)) > 0)
	{
		//print the user name of each record
		printf("User: %s\n", buffer.ut_user);
		//if the type is USER_PROCESS increase the counter for logged-in users
		if(buffer.ut_type == USER_PROCESS)
			numLogs++;
	}
	printf("The number of USER_PROCESS records found is %d\n", numLogs);
	//close the utmp file when finished with the program
	close(ufd);
	return 0;
}
