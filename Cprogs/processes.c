//parent process creates a child process and tries to run forever concurrently
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

void handler(int sig){
    if(sig == SIGUSR1){
        printf("I am terminated by my parent\n");
        _exit(0);
    }else if(sig == SIGCHLD){
        printf("My child is gone so I am now\n");
        _exit(0);
    }
}

int main(int argc, char** argv){

    pid_t pid;
    char* message;
    int sleepTime = 1;

    pid = fork();
    if(pid == -1){
        printf("Fork failed parent\n");
        exit(1);
    }else if(pid == 0){
        message = "I am your child";
        signal(SIGUSR1, handler);
        while(1){
            puts(message);
            sleep(sleepTime);
        }
        _exit(0);
    }else{
        message = "I am your parent";
        int i = 0;
        signal(SIGCHLD, handler);
        while(1){
            if(i>9){
                kill(pid, SIGUSR1);
            }
            puts(message);
            sleep(sleepTime);
            i++;
        }
        _exit(0);
    }
    exit(0);
}
