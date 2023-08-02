//Write a C program in which a child process writes "Hi, Mom" to a file named foo. Parent process
//reads message from file and prints it to stdout "my son said hi mom"; Send a msg "what do you want"
//to the child through a pipe. Once child recieve a msg from the parent, display on stdout. "my mom
//"said what do you want" assume that all system calls succeed(no error checks). make sure child 
//process runs first to write msg in file. Use SIGUSR1 signal for synchronization. File must only be
//opened once before child is created. DON'T use vfork(), sleep(), alarm(), wait(), or waitpid()
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>// open
#include<string.h>
#include<sys/wait.h>// wait
#include<sys/stat.h>// umask
#include<sys/types.h>

#define BUF 7
#define BUF2 16

void parrent(int SIG){
    return;
}
int main(){
    //Create pipe
    int fd[2];
    pipe(fd);

    //
    pid_t pid;
    pid = fork();
    if(pid == 0){//child 1
        int out = open("foo", O_WRONLY|O_CREAT,"0777");
        write(out, "Hi, Mom", BUF);
        kill(getppid(), SIGUSR1);
        char buff[BUF2+1];
        buff[BUF2] = '\0';
        read(fd[0], buff, BUF2);
        printf("My mom said, %s\n", buff);
        close(out);
        close(fd[0]);
        kill(getppid(), SIGUSR1);
        _exit(0);
    }else{//parrent
        signal(SIGUSR1, parrent);
        pause();
        int in = open("foo", O_RDONLY);
        char buf[BUF+1];
        buf[BUF] = '\0';
        read(in, buf, BUF);
        printf("My son said, %s\n", buf);
        char buf2[BUF2] = "What do you want";
        write(fd[1], buf2, BUF2);
        signal(SIGUSR1, parrent);
        pause();
        close(in);
        close(fd[1]);
        _exit(0);
    }
    exit(0);
    return(0);
}

