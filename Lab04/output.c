//task1.c accepts four file names as command line arguments (the first is input file
 //and the others are output files). Read byte by byte from the input file and write to the
 //proper output file. Alphabetical characters/letters write to a file called alpha, numerical
 //characters write to a file called num and other characters go to a file called other
 
 #include <unistd.h>
 #include <fcntl.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <sys/stat.h>
 #include <sys/types.h>
 
 //create an error function for ease of writing in the main function
 void err_sys(char *str)
 {
  printf("%s\n", str);
  exit(1);
 }
 
 int main(int argc, char *argv[])
 {
  umask(0);
  char buffer;
  if(argc!=5)
   err_sys("Name exactly 4 files!");
 
  //create file descriptors
  int in, a, n, o; //input, alpha, num, other
  if((in = open(argv[1], O_RDONLY)) < 0)
   err_sys("Error opening input file.");
  if((a = open(argv[2], O_RDWR | O_CREAT, 0777)) < 0) //file mode rwxrwxrwx
   err_sys("Error opening alpha file.");
  if((n = open(argv[3], O_RDWR | O_CREAT, 0777)) < 0)
   err_sys("Error opening num file.");
  if((o = open(argv[4], O_RDWR | O_CREAT, 0777)) < 0)
   err_sys("Error opening other file.");
 
  //read input file byte by byte
  while((read(in, &buffer, 1)) > 0)
  {
   if(buffer == '\n') //put the new lines in the files
   {
    write(a, &buffer, 1);
    write(n, &buffer, 1);
    write(o, &buffer, 1);
   }
   //the input file is an ASCII file, so we can convert the 2-3 digit
   //ASCII numbers into characters
   //which makes it easier to define a range of characters
 
   //detect if the character is a letter and write to alpha
   if((buffer >= 'a' && buffer <= 'z') || (buffer >= 'A' && buffer <= 'Z'))
    write(a, &buffer, 1);
   else //put a space in alpha if not a letter
    write(a, " ", 1);
   //detect if the character is a number and write to num
   if(buffer >= '0' && buffer <= '9')
    write(n, &buffer, 1);
   else
    write(n, " ", 1);
   //detect if the character is neither a letter or number and output to other
   if((int)buffer >= 33 && (int)buffer <= 47 || (int)buffer >= 58 && (int)buffer <= 64)
    write(o, &buffer, 1);
   else if((int)buffer >= 91 && (int)buffer <= 96 || (int) buffer >= 123 && (int)buffer <= 127)
    write(o, &buffer, 1);
   else //if not special character, put a space
    write(o, " ", 1);
  }
 
  //close the files once done
  close(in);
  close(a);
  close(n);
  close(o);
 
  return 0;
 }
 