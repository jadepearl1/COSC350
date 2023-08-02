//This program is a home made version of the getenv() function called mygetenv()
//which has the same syntax and semantics
//The main function is to show how well the mygetenv() function works

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

char *mygetenv(const char *name)
{
	int i; //loop iterator
	char *p; //pointer to environment variable value

        // Get the length of the environment variable name.
        int len = strlen(name);

        // Loop through each environment variable.
        for (i = 0; environ[i] != NULL; i++)
	{
            // Compare the strings
            if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
	    {
                // If the names match, allocate memory for a new string to hold the value.
                p = (char *) malloc(strlen(environ[i]) - len);
                // Copy the value of the environment variable to the new string.
                strcpy(p, &environ[i][len+1]);
                return p;
            }
        }
    //No matching string = return null value
    return NULL;
}


//main function to test the mygetenv function
int main()
{
	//print HOME, PATH, ROOTPATH
	printf("HOME=%s\n", mygetenv("HOME"));
	printf("PATH=%s\n", mygetenv("PATH"));
	printf("ROOTPATH=%s\n", mygetenv("ROOTPATH"));
	return 0;
}
